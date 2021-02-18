#include <Wire.h>



/* IMU Data */
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
double errorX, errorY,setpointX,lastY,lastX;
double setpointY =45;
int16_t tempRaw;

double gyroXangle, gyroYangle; // Angle calculate using the gyro only


double compAngleX,compAngleY;
double roll, pitch;
double Xangle,Yangle;
double gyroXrate, gyroYrate;
double dt;
double OUTRoll,OUTPitch;
long lastSentDelayTime = 0;
uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data


///////////////////////////FLC////////////////////////////////////
int NB=0;int NK=1;int Z=2;int PK=3;int PB=4;
double error1,error2,delerror;
double fuzzError[5];
double fuzzDelError[5];

double alpha[5][5];


double defuzz, S_alpha,pwmmotor,setpoint;
double output[5][5];
double CCC=-20;double CCL=-10;double D=0;double CL=10;double CC=20;




//////////////////////////BLDC///////////////////////////////////

const int rollMotor1 = 3;
const int rollMotor2 = 5;
const int rollMotor3 = 6;

const int pitchMotor1 = 9;
const int pitchMotor2 = 10;
const int pitchMotor3 = 11;


// Controls speed of motor updates



int pwmSin[] = {127,113,99,85,72,59,48,37,
                28,19,13,7,3,1,0,1,3,7,13,
                19,28,37,48,59,72,85,99,113,
                127,141,155,169,182,195,206,
                217,226,235,241,247,251,253,
                254,253,251,247,241,235,226,
                217,206,195,182,169,155,141};
                // array of PWM duty values for 8-bit timer - sine function
// Variables for pitch motor
int pitchStepA = 0;
int pitchStepB = 20;
int pitchStepC = 40;

// Variables for roll motor
int rollStepA = 0;
int rollStepB = 20;
int rollStepC = 40;
char rec[3];
void setup() {
  
  Serial.begin(115200);
  Wire.begin();
#if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif

  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode

  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    Serial.print(F("Error reading sensor"));
    while (1);
  }

  delay(50); // Wait for sensor to stabilize

  /* Set kalman and gyro starting angle */
  while (i2cRead(0x3B, i2cData, 6));
  accX = (i2cData[0] << 8) | i2cData[1];
  accY = (i2cData[2] << 8) | i2cData[3];
  accZ = (i2cData[4] << 8) | i2cData[5];

  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
  Xangle=roll;
  Yangle=pitch;

  dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
  timer = micros();

  
//  TCCR0B = TCCR0B & 0b11111000 | 0x01; // set PWM frequency @ 62500 Hz for Pins 5 and 6
  TCCR1B = TCCR1B & 0b11111000 | 0x01; // set PWM frequency @ 31250 Hz for Pins 9 and 10
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // set PWM frequency @ 31250 Hz for Pins 11 and 3 (3 not used)
  ICR1 = 255 ; // 8 bit resolution
  
  pinMode(pitchMotor1, OUTPUT);
  pinMode(pitchMotor2, OUTPUT);
  pinMode(pitchMotor3, OUTPUT);
  pinMode(rollMotor1, OUTPUT);
  pinMode(rollMotor2, OUTPUT);
  pinMode(rollMotor3, OUTPUT);
  
}


void loop() {
   if  (Serial.available()>0){
    for (uint8_t i=0;i<4;i++){
     rec[i] = Serial.read();
       }
    
  
   }
   setpointX= atoi(rec);
   
  update_sensor();
  
  
  //////kalman vs complementary/////

  //Serial.print("Y: ");Serial.print(pitch); Serial.print("\t");
  //Serial.print("X: ");Serial.print(compAngleX); Serial.print("\n");
  Serial.print("Y: ");Serial.print(compAngleY); Serial.print("\n");
  //Serial.print("Output Roll ");Serial.print(OUTRoll); Serial.print("\t");
 // Serial.print("Output Pitch ");Serial.print(OUTPitch); Serial.print("\n");
  //Serial.print("Y comp: ");Serial.print(compAngleY); Serial.print("\n");
  
  errorX=compAngleX-setpointX;
  errorY=compAngleY-setpointY;
//  errorY=kalAngleY-setpointY;
//  //Serial.print("X: ");Serial.print(kalAngleX); Serial.print("\t");
//   //Serial.print(kalAngleY); Serial.print("\n");
//  //Serial.print("Y: ");Serial.print(kalAngleY); Serial.print("\n");  
//   
//    
//
//  //// Proses FLC Roll/////
// 
  while (abs(errorX)>5){
//  //Serial.print("X: ");Serial.print(kalAngleX); Serial.print("\t");
  OUTRoll=FLControl(errorX,lastX);
  OUTRoll=-OUTRoll;
  //Serial.print("DefRoll: ");Serial.print(OUTRoll); Serial.print("\n");
   //Serial.print("X: ");Serial.print(compAngleX); Serial.print("\n");
  Serial.print("Y: ");Serial.print(compAngleY); Serial.print("\n");
  motor(rollStepA,rollStepB,rollStepC,
        rollMotor1,rollMotor2,rollMotor3,
        OUTRoll);
  lastX=errorX;
  update_sensor();
  errorX=compAngleX-setpointX;
 }
  ////proses FLC Pitch/////
  while(abs(errorY)>5){
  //Serial.print("Y: ");Serial.print(kalAngleY); Serial.print("\t");

  //Serial.print("Y: ");Serial.print(pitch); Serial.print("\t");
 // Serial.print("X kal: ");Serial.print(kalAngleX); Serial.print("\t");
 // Serial.print("Y kal: ");Serial.print(kalAngleY); Serial.print("\t");
  //  Serial.print("X: ");Serial.print(compAngleX); Serial.print("\n");
  Serial.print("Y: ");Serial.print(compAngleY); Serial.print("\n");
  OUTPitch=FLControl(errorY,lastY);
  //Serial.print("DefPitch: ");Serial.print(OUTPitch); Serial.print("\n");
  motor(pitchStepA,pitchStepB,pitchStepC,
        pitchMotor1,pitchMotor2,pitchMotor3,
        OUTPitch);
  lastY=errorY;
  update_sensor();
  errorY=compAngleY-setpointY;
  
  //Serial.print(OUTPitch); Serial.print("\n");
  }

}



