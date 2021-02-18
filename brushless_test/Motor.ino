void motor(int &stepA,int &stepB,int &stepC,
            int pinA,int pinB,int pinC , int rpm)
{
  int ti;
  ti=timedelay(abs(rpm));
  if (rpm==0)
  {
      analogWrite(pinA, pwmSin[stepA]);
      analogWrite(pinB, pwmSin[stepB]);
      analogWrite(pinC, pwmSin[stepC]);
  }
  if (rpm>2)
  {
    
    stepA++;
    stepB++;
    stepC++;
    
    if (stepA>55){stepA=0;}
    if (stepB>55){stepB=0;}
    if (stepC>55){stepC=0;}
      
  
      analogWrite(pinA, pwmSin[stepA]);
      analogWrite(pinB, pwmSin[stepB]);
      analogWrite(pinC, pwmSin[stepC]);
      delay(ti);
  }
  
  if(rpm<-2)
  {
    
    stepA--;
    stepB--;
    stepC--;
    if (stepA<0){stepA=55;}
    if (stepB<0){stepB=55;}
    if (stepC<0){stepC=55;}
    
      analogWrite(pinA, pwmSin[stepA]);
      analogWrite(pinB, pwmSin[stepB]);
      analogWrite(pinC, pwmSin[stepC]);
      delay(ti);

  }


}


int timedelay(int rpm){
int temp=60000/rpm;
temp=(temp/7)/56;
return temp;

}


void motor_step(int &stepA,int &stepB,int &stepC,
            int pinA,int pinB,int pinC , int Step)
{

  if (Step>0)
  {
    for (int i=0;i>=abs(Step);i++){
    stepA++;
    stepB++;
    stepC++;
    
    if (stepA>55){stepA=0;}
    if (stepB>55){stepB=0;}
    if (stepC>55){stepC=0;}
      
  
      analogWrite(pinA, pwmSin[stepA]);
      analogWrite(pinB, pwmSin[stepB]);
      analogWrite(pinC, pwmSin[stepC]);
      delay(100);
  }}
  
  if(Step<0)
  {
     for (int i=0;i>=abs(Step);i++){
    stepA--;
    stepB--;
    stepC--;
    if (stepA<0){stepA=55;}
    if (stepB<0){stepB=55;}
    if (stepC<0){stepC=55;}
    
      analogWrite(pinA, pwmSin[stepA]);
      analogWrite(pinB, pwmSin[stepB]);
      analogWrite(pinC, pwmSin[stepC]);
      delay(100);
     }
  }


}




