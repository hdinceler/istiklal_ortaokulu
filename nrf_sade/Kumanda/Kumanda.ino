#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(9,10); // CE, CSN
char giden_komut[32]="selam gencler :)";
void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(0xF0F0F0F0E12E);
  radio.setPALevel(RF24_PA_MIN); // en düşük seviye enerji tüketimi , düşük sinyal menzili
  radio.stopListening();//verici  modunda çalış. 
}

void loop() {
  // sprintf( giden_komut , "%d,%d,%d,%d", leftSpeed ,rightSpeed, far_durum , korna_durum );
  radio.write(&giden_komut , sizeof(giden_komut));
}


 