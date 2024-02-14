#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#define pin_R1 3 //~PWM
#define pin_R2 5 //~PWM
#define pin_L1 9 //~PWM
#define pin_L2 6 //~PWM

#define pin_far A5 //DIGITAL
#define pin_korna A4 //DIGITAL

//MESAFE ÖLÇÜM BİLDİRİMLERİ
int pin_mesafe_trig = 2;
int pin_mesafe_echo = 4;
#define yakinlik_siniri  10   // araba bu cm cinsinden degerden  daha yakın cisim algılarsa dursun
#define pin_far A5 // DIGITAL
#define pin_korna A4 // DIGITAL
long zaman;
long mesafe;
unsigned long baslangic_zamani_millis=0;;
unsigned long baslangic_zamani_micros=0;;
// const unsigned long okumaAraligi = 1; // Okuma aralığı (milisaniye cinsinden)
bool trigDurumu = false;


#include "araba_kutuphane.h"

RF24 radio(7,8); // CE, CSN pimleri

signed short rightSpeed=0;
signed short leftSpeed=0;
uint8_t far_durum=0;
uint8_t korna_durum=0;
char buff[10];
char gelen_komut[32] = "";


void setup() {
  
  pinMode(pin_mesafe_trig, OUTPUT);
  pinMode(pin_mesafe_echo, INPUT);

  pinMode( pin_far, OUTPUT);
  pinMode( pin_korna , OUTPUT);
  pinMode( pin_R1 , OUTPUT);
  pinMode( pin_R2 , OUTPUT);
  pinMode( pin_L1 , OUTPUT);
  pinMode( pin_L2 , OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E12E); // Vericinin yazma hattı adresi
  radio.startListening();
  all_stop();
}

void loop() {
 
//RADYO İLETİŞİM
  if (radio.available()) {
    
    radio.read(&gelen_komut, sizeof(gelen_komut));
    Serial.println(gelen_komut);
     
  }  
}
