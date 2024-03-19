#include <Servo.h>
#define basParmak 3
#define isaretParmagi 4
#define ortaParmak 5
#define yuzukParmagi 6
#define serceParmak 7

#define gecikme 450  //  250 den küçük sayı girmeyin
#define baslamaAcisi 0  //Açı en az 0, en fazla 180 
#define bitisAcisi 180 //Açı en az 0, en fazla 180 

Servo servo;
void setup() {
  Serial.begin(9600);
  Serial.println("Test Başlıyor...");
}

void loop() {
  for(int i =3; i<=7; i++){
    servo.attach(i);
    servo.write(baslamaAcisi);delay(gecikme);
    servo.write(bitisAcisi);delay(gecikme);
  }
  for(int i =6; i>=4; i--){
    servo.attach(i);
    servo.write(baslamaAcisi);delay(gecikme);
    servo.write(bitisAcisi);delay(gecikme);
  }
  
}
