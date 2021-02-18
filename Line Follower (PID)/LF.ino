int s, s1,s2,s3,s4,s5,s6,s7,s8;
float  sp,pv,error,last_error,p,i,d,kp,ki,kd,rate1,rate2;
int f,left,right;
float PV;
int Lmtr = 12;
int Rmtr = 11;
int Lpwm = 10;
int Rpwm = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(13, INPUT);
  Serial.begin(9600);
  pinMode(Lmtr,OUTPUT);
  pinMode(Rmtr,OUTPUT);
  pinMode(Lpwm,OUTPUT);
  pinMode(Rpwm,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  sensor();
  PID();
   roll();
  Serial.print("s=");
  Serial.println(s);
  Serial.print("PV=");
  Serial.println(PV);
   Serial.print("e1=");
  Serial.print(error);
   Serial.print("p=");
  Serial.print(p);
   Serial.print("i=");
  Serial.print(i);
   Serial.print("d=");
  Serial.print(d);
  Serial.print("u=");
  Serial.println(f);
//  
  delay(2);
}

void sensor()
{
  s1 = digitalRead(2)<<7;
  s2 = digitalRead(3)<<6;
  s3 = digitalRead(4)<<5;
  s4 = digitalRead(5)<<4;
  s5 = digitalRead(6)<<3;
  s6 = digitalRead(7)<<2;
  s7 = digitalRead(8)<<1;
  s8 = digitalRead(13);
  
  s = s1|s2|s3|s4|s5|s6|s7|s8;
if (s == 1){ PV=11;}
if (s == 3){ PV=9;}
if (s == 7){ PV=8;}
if (s == 15){ PV=7;}
if (s == 127){ PV=10;}
if (s == 63){ PV=6;}
if (s == 31){ PV=5;}
if (s == 159){ PV=4;}
if (s == 143){ PV=3;}
if (s == 207){ PV=2;}
if (s == 239){ PV=1;}

if (s == 231){ PV=0;}

if (s == 227){ PV=-1;}
if (s == 243){PV =-2;}
if (s == 241){ PV=-3;}
if (s == 249){ PV=-4;}
if (s == 248){ PV=-5;}
if (s == 252){ PV=-6;}
if (s == 254){ PV=-10;}
if (s == 240){ PV=-7;}
if (s == 224){ PV=-8;}
if (s == 192){ PV=-9;}
if (s == 128){ PV=-11;}
}

void PID()
{
    
   kp = 14;   /// nilai proportional 
   ki = 0.1; /// nilai integratif
   kd = 8;  ////nilai derivative
   sp = 0;
   pv = PV;
   last_error = error;
   error = sp - pv;
   p = error * kp;    //// persamaan proportional
   rate1 = error - last_error;
   d = kd * rate1;    /// persamaan derivatif
   rate2 = error + last_error; 
   i = ki * rate2;    ///// persamaan integratif
   f =p+d+i;   ///// persamaan PID 




}

void motor(int left, int right)
{
   if( left >= 0) { digitalWrite (Lmtr,LOW); }
  else { digitalWrite (Lmtr,HIGH); }
  
  if( right >=0) {  digitalWrite (Rmtr,LOW); }
  else {  digitalWrite (Rmtr,HIGH); }
  
  analogWrite (Lpwm,abs(left));
  analogWrite (Rpwm,abs(right));
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

void roll()
{
// left = 5+(200+f);
// right = 5+(200-f);
//
// if (left >= 255)
// { 
//   left =255;
// } 
// if (right  >= 255)
// {
//   right = 255;
// }
 if (PV == 0)
 
 {left = 5+(220+f); // --> Differential drive
 right = 5+(220-f);// --> Differential drive
 motorKiri(left);
 motorKanan(right); 
 }
//  
  if (PV >= 1 && PV <=2)
 { left = 5+(180 +f);
 right = 5+(180-f);
   
  motorKiri(left);
  motorKanan(right);
  } 

  if (PV >= -2 && PV <=-1)
   { left = 5+(180+f);
 right = 5+(180-f); 
 
     motorKiri(left);
 motorKanan(right);
   } 

 if (PV >= 3 && PV <=9)
 { left = 5+(120+f);
 right = 5+(120-f); 
 
   motorKiri(left);
 motorKanan(right);
 }

  if (PV >= -9 && PV <=-3)
  {
   left = 5+(120+f);
 right = 5+(120-f); 
   motorKiri(left);
  motorKanan(right);
 } 


// if (PV >=10 )
//  {
//   left = 5+(100+f);
// right = 5+(100-f*-1);  
//   motorKiri(left);
// motorKanan(right);
//  } 
// if (PV <= -10)
//  { left = 5+(100+f*-1);
// right = 5+(100-f); 
//    motorKiri(left);
// motorKanan(right);
// }


}
