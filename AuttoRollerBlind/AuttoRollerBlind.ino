/// Initialize pins for  Clock Display on LCD/////
int InHour=6;
int InMinute1=5;
int InMinute2=4;
int BSHour;
int BSMin1;
int BSMin2;
int LBSHour;
int LBSMin1;
int LBSMin2;

unsigned int second=0;
unsigned int minute=0;
unsigned int hour=0;
static unsigned long lWaitMillis;
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, A3, A2, A1, A0);

////initialize pins for motor drive
int PWMmotor = 9;
int PinA1 = 3;
int PinA2 = 2;
int SW1 = 0;
int SW2 = 1;
bool Open=false;

void setup() {
  
      pinMode(PWMmotor,OUTPUT);
      pinMode(PinA1,OUTPUT);
      pinMode(PinA2,OUTPUT);
      pinMode(SW1,INPUT);
      pinMode(SW2,INPUT);
      pinMode(InHour,INPUT);
      pinMode(InMinute1,INPUT);
      pinMode(InMinute2,INPUT);


      lcd.begin(16, 2);

      lWaitMillis = millis() + 1000;  // initial setup
}

void loop() {
 

////////////////////////// 
Clock();
inputClock();
displayClock();

//////////////////////////
if (hour==6){if (Open==false){driveMotor(127,"CW");}}
else if(hour==18){if (Open==true){driveMotor(127,"CCW");}}
if(digitalRead(SW1)==1){driveMotor(0,"stop");Open=true;}
if(digitalRead(SW2)==1){driveMotor(0,"stop");Open=false;}
}

//this constructor is made for driving motor with  L293D H-Bridge, speedmotor is represent the PWM value 
// and motorDirection is represent the direction of motor (CW=ClockWise,CCW=CounterClockWise,stop for stopping the motor)
void driveMotor(int speedMotor, String motorDirection){  
analogWrite(PWMmotor,speedMotor);
if( motorDirection=="CW")
{
digitalWrite(PinA1,HIGH);
digitalWrite(PinA2,LOW);
  
} 

if (motorDirection=="CCW")
{
  
digitalWrite(PinA1,LOW);
digitalWrite(PinA2,HIGH);
}
if (motorDirection=="stop")
{
  
digitalWrite(PinA1,HIGH);
digitalWrite(PinA2,HIGH);
}
}

// constructor for generating clock  
void Clock()
{
 if( (long)( millis() - lWaitMillis ) >= 0)
  {
    // millis is now later than my 'next' time

    second++;

    lWaitMillis += 1000;  // do it again 1 second later
  }  


if (second==60){
minute++;
second=0;
}
if (minute==60){
hour++;
minute =0;
}
if(hour==24){
hour=0;
} 
}

///for displaying at LCD display
void displayClock(){
String SHour=String(hour,DEC);
 if (hour<10){
 SHour=  "0"+SHour;}
 lcd.setCursor(0, 0);
 lcd.print(SHour);
 
 lcd.setCursor(3, 0);
 lcd.print(":");
 
 String SMinute=String(minute,DEC);
 if (minute<10){
 SMinute=  "0"+SMinute;}
 lcd.setCursor(4, 0);
 lcd.print(SMinute);
 
 lcd.setCursor(7, 0);
 lcd.print(":");
 
 String SSecond= String(second,DEC);
 if (second<10){
 SSecond=  "0"+SSecond;}
 lcd.setCursor(8, 0);
 lcd.print(SSecond);
}


// constructor for setting clock
void inputClock(){
    BSHour = digitalRead(InHour);
    BSMin1 = digitalRead(InMinute1);
    BSMin2 = digitalRead(InMinute2);
   if (BSHour != LBSHour) 
  {
      if(BSHour == HIGH){  
        hour++;}
    if (hour==24){hour=0;}
  }
  if (BSMin1 != LBSMin1)
  {
    if (BSMin1==HIGH){
      minute= minute+10;}
    if (minute>59){
      minute = minute%10;
    }
  }
   if (BSMin2!=LBSMin2)
  {
      if(BSMin2==HIGH){
      minute++;}
    if (minute>59)
  {
    int a= minute/10;
    minute= a*10;
  }

  }
   LBSHour=BSHour;
   LBSMin1=BSMin1;
   LBSMin2=BSMin2;
}



 
