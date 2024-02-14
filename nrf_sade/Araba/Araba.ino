#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
RF24 radio(7,8); // CE, CSN pimleri
char gelen_komut[32] = "";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E12E); // Vericinin yazma hattı adresi
  radio.startListening();
}
void loop() {
 //RADYO İLETİŞİM
  if (radio.available()) {
    radio.read(&gelen_komut, sizeof(gelen_komut));
    Serial.println(gelen_komut);
   }  
}
