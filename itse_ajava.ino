#include <Servo.h>
#define in1 2
#define in2 3
#define in3 4
#define in4 5
#define in5 6
#define in6 7
#define kytkin 8 // käynnistys kytkin
#define in8 12 //valot
#define trigPinV A1 //vasen anturi
#define echoPinV A0
#define trigPinO A3 //oikea anturi
#define echoPinO A2
Servo myservo;
int leftDistance=0,rightDistance=0,oikeaKeskiarvo,vasenKeskiarvo;


void setup(){
  Serial.begin(9600); //tämän voi, ehkä poistaa kun ei tarvita enään debuggausta
  myservo.attach(10);
  myservo.write(60); //60 astetta on puolet eli renkaat suoraksi setupin aikana
  pinMode(trigPinV,OUTPUT); // Vasen ultraääni atnuri
  pinMode(echoPinV,INPUT);
  pinMode(trigPinO,OUTPUT); // Oikea ultraääni anturi
  pinMode(echoPinO,INPUT);
  pinMode(in1,OUTPUT); 
  pinMode(in2,OUTPUT); 
  pinMode(in3,OUTPUT); 
  pinMode(in4,OUTPUT); 
  pinMode(in5,OUTPUT); 
  pinMode(in6,OUTPUT); 
  pinMode(kytkin,INPUT_PULLUP); // käynnistys kytkin
  pinMode(in8,OUTPUT); //ajovalot
  delay(3000);
}
void eteenpainAjo(){
  digitalWrite(in1,HIGH); 
  digitalWrite(in2,HIGH);
  digitalWrite(in4,HIGH);
  digitalWrite(in6,HIGH);
}
void oikeaMittaus(){
int durationO,distanceO,i,arvo=0; //oikean anturin mittaus
  for(i=0;i<10;i++){
    digitalWrite(trigPinO,LOW);
    delayMicroseconds(2); //arduinon esimerkki 2 muissa 5
    digitalWrite(trigPinO,HIGH);
    delayMicroseconds(5); //arduinon esimerkki 5 muissa 10
    digitalWrite(trigPinO,LOW);
    durationO = pulseIn(echoPinO,HIGH);
    distanceO = durationO*0.0343/2;
    oikeaKeskiarvo = distanceO;
    arvo = arvo + oikeaKeskiarvo;
    delay(1);
  }
  rightDistance = arvo / 10; //keskiarvo 10stä tuloksesta
}
void vasenMittaus(){  
int durationV,distanceV,i,arvo=0; //vasemman anturin mittaus
  for(i=0;i<10;i++){
    digitalWrite(trigPinV,LOW);
    delayMicroseconds(2); //arduinon esimerkki 2 muissa 5
    digitalWrite(trigPinV,HIGH);
    delayMicroseconds(5); //arduinon esimerkki 5 muissa 10
    digitalWrite(trigPinV,LOW);
    durationV = pulseIn(echoPinV,HIGH);
    distanceV = durationV*0.0343/2;
    vasenKeskiarvo = distanceV;
    arvo = arvo + vasenKeskiarvo;
    delay(1);
  }
  leftDistance = arvo / 10; //keskiarvo 10stä tuloksesta
}
void suuntaVaihto(){ //etäisyyksien vertailu
  if(leftDistance>rightDistance){
   myservo.write(120);
  }else if(rightDistance>leftDistance){
   myservo.write(0);
  }
}
void loop(){ 
    digitalWrite(in8,HIGH);
    oikeaMittaus();
    vasenMittaus();
    eteenpainAjo();
    if(((leftDistance<30)||(rightDistance<30))&&((leftDistance>0)||(rightDistance>0))){
      suuntaVaihto();
    }
}
