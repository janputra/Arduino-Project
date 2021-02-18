#define DimLamp1 A2
#define DimLamp2 A3
bool l1=false;
bool l2=false;
int dimming1,dimming2;
bool lamp1; false;
char rec[3];
int i,data;

void setup() {
pinMode(5,OUTPUT);
pinMode(DimLamp1,OUTPUT);
pinMode(6,OUTPUT);
pinMode(DimLamp2,OUTPUT);

attachInterrupt(0,zero_crosss_int,RISING);
Serial.begin(9600);
}

void loop() {
  if  (Serial.available()>0){

    for (i=0;i<4;i++){
     rec[i] = Serial.read();
       }

    data = atoi(rec);
   
if (data==10){}
if (data==11){}
if (data==20){}
if (data==21){}
  
  }
 dimming1=data;
 Serial.println(dimming1);
}

//the interrupt function must take no parameters and return nothing
void zero_crosss_int()  //function to be fired at the zero crossing to dim the light
{  
  // Firing angle calculation : 1 full 50Hz wave =1/50=20ms 
  // Every zerocrossing thus: (50Hz)-> 10ms (1/2 Cycle) 
  // For 60Hz => 8.33ms (10.000/120)
  // 10ms=10000us
  // (10000us - 10us) / 128 = 75 (Approx) For 60Hz =>65
//  if  (Serial.available()>0){
//  
//  int data = Serial.read();
//  dimming1=data;}




    if (dimming1 < 1) {
      //Turn TRIAC completely OFF if dim is 0
  digitalWrite(DimLamp1, LOW);
  digitalWrite(DimLamp2,LOW); 
    }

    if (dimming1 > 114) { //Turn TRIAC completely ON if dim is 128
  digitalWrite(DimLamp1, HIGH);
  digitalWrite(DimLamp2,HIGH);
    }

  if (dimming1>1&&dimming1<114){
  int dimtime1 = (75*(128-dimming1));    // For 60Hz =>65    
  delayMicroseconds(dimtime1);    // Wait till firing the TRIAC
  digitalWrite(DimLamp1, HIGH);
  digitalWrite(DimLamp2,HIGH);  // Fire the TRIAC
  delayMicroseconds(10);         // triac On propogation delay (for 60Hz use 8.33)
  digitalWrite(DimLamp1, LOW);
  digitalWrite(DimLamp2,LOW);  // No longer trigger the TRIAC (the next zero crossing will swith it off) TRIACC
  }
}  
  



