#include <Servo.h>

const int numServo = 4;
Servo myServo[numServo];
int pinServo[numServo]={2,3,4,5};


int inData[4]; // Allocate some space for the string
int last_inData[4];
int inChar; // Where to store the character read
int index = 0;

void setup() {
  for (int x=0; x<numServo;x++)
    {
        myServo[x].attach(pinServo[x]);
        inData[x]=0;
        last_inData[x]=0;
    }

  Serial.begin(9600);// attaches the servo on pin 9 to the servo object
}

void loop() {
if (Serial.available() > 0) {
    // read the incoming byte:
    
    for(index = 0; index < 4; index++)
      {
        inChar = Serial.read();
        delay(10);
        if (inChar>180)inChar=180;
        inData[index] = inChar;
        Serial.write(inData[index]);
      }   
            
}


move_ser(inData,last_inData);
 
 for (int x=0; x<numServo;x++)
    {
       last_inData[x]=inData[x];
    }

}

void move_ser(int j[numServo], int last_j[numServo])
{
    for (int x=0; x<numServo;x++)
    {    
       
       if (j[x]>last_j[x])
       {
        for (int s=last_j[x];s<=j[x];s++)
          {
           myServo[x].write(s);
            delay(10);
          }
        
        }
      if (j[x]<last_j[x]){
         for (int s=last_j[x];s>=j[x];s--)
          {
           myServo[x].write(s);
            delay(10);
          }
         
        }
        }
}
