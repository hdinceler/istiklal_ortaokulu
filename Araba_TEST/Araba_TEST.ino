#include <SPI.h>
#include <Wire.h>
#define yakinlik_siniri  5   // araba bu cm cinsinden degerden  daha yakın cisim algılarsa dursun
long zaman=0;
long mesafe_on=0;
long mesafe_arka=0;
unsigned long baslangic_zamani_millis=0;;
unsigned long baslangic_zamani_micros=0;;
char buff[10];
 
#define pin_on_far 2
#define pin_sag_teker_ileri 3 //~PWM
#define pin_korna 4
#define pin_sag_teker_geri 5 //~PWM
#define pin_sol_teker_ileri 6 //~PWM
#define CSN_PIN 7 // NRF için
#define CE_PIN 8 // NRF için
#define pin_sol_teker_geri 9 //~PWM
#define pin_sis_fari 10

uint8_t pin_mesafe_echo_on = A0;
uint8_t pin_mesafe_trig_on = A1;
uint8_t pin_mesafe_echo_arka = A2;
uint8_t pin_mesafe_trig_arka = A3;
#include "araba_kutuphane.h"

void setup() {
  pinMode( pin_on_far, OUTPUT);
  pinMode( pin_sag_teker_ileri , OUTPUT);
  pinMode( pin_korna , OUTPUT);
  pinMode( pin_sag_teker_geri , OUTPUT);
  pinMode( pin_sol_teker_ileri , OUTPUT);
  pinMode( pin_sol_teker_geri , OUTPUT);
  pinMode( pin_sis_fari, OUTPUT);

  pinMode(pin_mesafe_trig_on, OUTPUT);
  pinMode(pin_mesafe_echo_on, INPUT);
  pinMode(pin_mesafe_trig_arka, OUTPUT);
  pinMode(pin_mesafe_echo_arka, INPUT);
  Serial.begin(9600);
}

void far_yak(){digitalWrite(pin_on_far,1);  }
void far_sondur(){digitalWrite(pin_on_far,0);}
void sis_fari_yak(){digitalWrite(pin_sis_fari,1);}
void sis_fari_sondur(){digitalWrite(pin_sis_fari,0);}
void korna_cal(){digitalWrite(pin_korna,1);}
void korna_sus(){digitalWrite(pin_korna,0);}

void loop() {
ileri_git( 90 ); delay(2000);
geri_git(90);delay(2000); 
sola_don( 90);delay(2000);
saga_don(90);delay(2000);
dur();
far_yak();delay(2000);
far_sondur();delay(2000);
sis_fari_yak();delay(1000);
sis_fari_sondur();delay(1000);
korna_cal();delay(1000);
korna_sus();delay(1000);
}
