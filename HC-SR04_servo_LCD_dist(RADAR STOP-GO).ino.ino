#include <Servo.h>
#include <LiquidCrystal.h>
//Pin RGB
int PR = 6;
int PV = 3;
//Pin Servo
int PSERVO = 10; 
//Pin HCSR04
int PTRIG = 8;
int PECHO = 12;
Servo S1;
int tiempo;
float distcm;
int posicion = 0;
int paso = 3;
//Variables millis()
unsigned long tiemprojo = 0;
unsigned long tiempverde = 0;
const long tiempmax = 4000;
//Variables LCD
int RS = 2;
int E = 13;
int D4 = 5;
int D5 = 4;
int D6 = 7;
int D7 = 11;
LiquidCrystal lcd(RS,E,D4,D5,D6,D7); //VO -> gnd with 2k resistor
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
lcd.begin(16,2);
pinMode(PR,OUTPUT);
pinMode(PV,OUTPUT);
pinMode(PTRIG,OUTPUT);
pinMode(PECHO,INPUT);
S1.attach(PSERVO);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(PTRIG,HIGH);
delayMicroseconds(2);
digitalWrite(PTRIG,LOW);
delayMicroseconds(2);
tiempo = pulseIn(PECHO,HIGH,50000);
if (tiempo>0){
  distcm = (tiempo*0.034)/2;
  if (distcm>15){
    posicion = posicion + paso;
    if (posicion >=90 || posicion <=0){
      paso = -paso;
    }
    S1.write(posicion);
    digitalWrite(PR,LOW);
    digitalWrite(PV,HIGH);
    //We add a 3 sec timer
    if(millis()-tiempverde>=tiempmax){
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Mi dist es: "); 
      lcd.print(">15");
      tiempverde = millis();
    }
    
  }
  if (distcm<=15){
    S1.write(posicion);
    digitalWrite(PR,HIGH);
    digitalWrite(PV,LOW);
    //We add a 3 sec timer
    if (millis()-tiemprojo>=tiempmax){
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Mi dist es: "); 
      lcd.print(distcm);
      tiemprojo = millis();
    }



  }
}




}
