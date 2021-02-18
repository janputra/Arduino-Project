
#define Lmtr 12
#define Rmtr 11
#define Lpwm 10
#define Rpwm 9
#define trig A3
#define echo A4

int i,j;
double duration, distance;
//--------inisialisasi variable fuzzy-------//
int NB=0;int NK=1;int Z=2;int PK=3;int PB=4;
double error1,error2,delerror;
double fuzzError[5];
double fuzzDelError[5];
double alpha[5][5];


double defuzz, S_alpha,pwmmotor,setpoint;
double output[5][5];

int muC=-210;int muL=-130;int D=0;int maL=130;int maC=210;

void setup() {
  // put your setup code here, to run once:
  pinMode(Lmtr,OUTPUT);
  pinMode(Rmtr,OUTPUT);
  pinMode(Lpwm,OUTPUT);
  pinMode(Rpwm,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
 
  Serial.begin(9600);
}

void loop() {

error2=error1;  
readSensor();
error1=10-distance;
delerror=error1-error2;
  
   
//--------------fuzzifikasi error-----------------//
fuzzError[NB]=FATrapesium1(error1,-5,-3);
fuzzError[NK]=FASegitiga(error1,-5,-3,0);
fuzzError[Z]=FASegitiga(error1,-3,0,3);
fuzzError[PK]=FASegitiga(error1,0,3,5);
fuzzError[PB]=FATrapesium2(error1,3,5);

//--------------fuzzifikasi delta error-----------------//
fuzzDelError[NB]=FATrapesium1(delerror,-5,-3);
fuzzDelError[NK]=FASegitiga(delerror,-5,-3,0);
fuzzDelError[Z]=FASegitiga(delerror,-3,0,3);
fuzzDelError[PK]=FASegitiga(delerror,0,3,5);
fuzzDelError[PB]=FATrapesium2(delerror,3,5);

//---------------------implikasi/rule evaluation----------------//
for (i=0;i<5;i++)
 {
  for (j=0;j<5;j++)
    {
      alpha[i][j]=min(fuzzError[i],fuzzDelError[j]);
    }
 }
 initiallizeRule();

//-----------------defuzzifikasi---------------//
 defuzzy();
 pwmmotor=defuzz;

Serial.print(distance); Serial.print(" ");
Serial.print(error1); Serial.print(" ");
Serial.print(delerror); Serial.print(" ");
Serial.println(pwmmotor);


//printS(); 
 motorKanan(pwmmotor);
 motorKiri(pwmmotor);
// delay(100);
// delay(10);
 
}

void readSensor()
{
  digitalWrite(trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration=pulseIn(echo,HIGH);
  distance=duration/58;

}



void motorKiri(int k)
{
if (k >= 0){ digitalWrite (Lmtr,LOW); }
else { digitalWrite (Lmtr, HIGH);}
analogWrite(Lpwm,abs(k));
}
void motorKanan(int k)
{
if (k >= 0){ digitalWrite (Rmtr,LOW); }
else { digitalWrite (Rmtr, HIGH);}
analogWrite(Rpwm,abs(k));
}
