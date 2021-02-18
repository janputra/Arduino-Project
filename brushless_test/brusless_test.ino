const int rollMotor1 = 3;
const int rollMotor2 = 5;
const int rollMotor3 = 6;

const int pitchMotor1 = 9;
const int pitchMotor2 = 10;
const int pitchMotor3 = 11;
int pwmSin[] = {127,113,99,85,72,59,48,37,28,19,13,7,3,1,0,1,3,7,13,19,28,37,48,59,72,85,99,113,127,141,155,169,182,195,206,217,226,235,241,247,251,253,254,253,251,247,241,235,226,217,206,195,182,169,155,141
}; // array of PWM duty values for 8-bit timer - sine function
bool roll=true;
//uint8_t ti;
//uint8_t c=0;     
int c=0;
int a=20;
int b=40;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
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

  
 motor_step(c,a,b,rollMotor1,rollMotor2,rollMotor3,-20);
 
}
  



