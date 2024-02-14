#include <Arduino.h>
#include <SPI.h>
#include "printf.h"
#include "RF24.h"
// pin tanımlamaları
#define CE_PIN 9
#define CSN_PIN 10
#define btn_joy  8
#define btn_up  2
#define btn_down 4
#define btn_right 3
#define btn_left 5
#define x_pin  A0
#define y_pin  A1

RF24 radio(CE_PIN, CSN_PIN);
char buff[10];
char giden_komut[64] = "";

unsigned int x_degeri = 0;
unsigned int y_degeri = 0;

void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(0xF0F0F0F0E12E);
  radio.setPALevel(RF24_PA_MIN); // en düşük seviye enerji tüketimi , düşük sinyal menzili
  radio.stopListening();//verici  modunda çalış. 
  Serial.begin(9600);
}

void loop() {
  x_degeri = analogRead(x_pin);
  y_degeri = analogRead(y_pin);
  sprintf( giden_komut , "%d,%d,%d,%d,%d,%d,%d",x_degeri,y_degeri, !digitalRead(btn_joy), !digitalRead(btn_up), !digitalRead(btn_down),  !digitalRead(btn_right),  !digitalRead(btn_left));
  radio.write(&giden_komut , sizeof(giden_komut));
}