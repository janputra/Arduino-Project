int a=3;
int b=0;
int c=0;

void setup() {
pinMode(0,OUTPUT);
pinMode(1,OUTPUT);
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
}

void loop() {
PORTD=~b;
b=a<<c;
c++;
if(c==8){c=0;}
delay(100); 
}
