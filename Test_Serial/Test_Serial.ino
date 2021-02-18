void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  if  (Serial.available()>0){
  char data= Serial.read();
  
  if (data=='A')
    {
      digitalWrite(13,1);
    }
   if (data=='B')
    {
     
      digitalWrite(13,0);
    }
 
  
  
  
  }
}
