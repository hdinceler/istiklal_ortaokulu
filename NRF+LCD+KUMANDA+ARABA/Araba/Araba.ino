#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define yakinlik_siniri  10   // araba bu cm cinsinden degerden  daha yakın cisim algılarsa dursun
long zaman;
long mesafe;
unsigned long baslangic_zamani_millis=0;;
unsigned long baslangic_zamani_micros=0;;
bool trigDurumu = false;
char buff[10];

 

uint8_t x_degeri=0;
uint8_t y_degeri=0;
uint8_t joy_buton=0;
uint8_t yukari_buton=0;
uint8_t asagi_buton=0;
uint8_t sag_buton=0;
uint8_t sol_buton=0;

int pin_mesafe_trig = 2;
int pin_mesafe_echo = 4;
#define pin_far 2
#define pin_sag_teker_ileri 3 //~PWM
#define pin_korna 4
#define pin_sag_teker_geri 5 //~PWM
#define pin_sol_teker_ileri 6 //~PWM
#define CE_PIN 8 // NRF için
#define CSN_PIN 7 // NRF için
#define pin_sol_teker_geri 9 //~PWM

RF24 radio(CE_PIN , CSN_PIN); // CE, CSN pimleri
char gelen_komut[32] = "";

void setup() {
  
  pinMode(pin_mesafe_trig, OUTPUT);
  pinMode(pin_mesafe_echo, INPUT);

  pinMode( pin_far, OUTPUT);
  pinMode( pin_korna , OUTPUT);
  pinMode( pin_sag_teker_ileri , OUTPUT);
  pinMode( pin_sag_teker_geri , OUTPUT);
  pinMode( pin_sol_teker_ileri , OUTPUT);
  pinMode( pin_sol_teker_geri , OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E12E); // Vericinin yazma hattı adresi
  radio.startListening();
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.clear();
 
}

void loop() {
 
//RADYO İLETİŞİM
  if (radio.available()) {
    
    radio.read(&gelen_komut, sizeof(gelen_komut));
    
    strcpy( buff , strtok( gelen_komut,  "," ) ); x_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); y_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); joy_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); yukari_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); asagi_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); sag_buton = atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); sol_buton= atoi(buff);

    Serial.println(gelen_komut);
     lcd.setCursor(0,0);lcd.print("X"); //Joystick X exseni
    lcd.setCursor(4,0);lcd.print("Y");  //Joystick Y ekseni
    lcd.setCursor(8,0);lcd.print("J");  //Joystick butonu
    lcd.setCursor(10,0);lcd.print("U");  //yukarı düğme
    lcd.setCursor(11,0);lcd.print("D");  //aşağı düğme
    lcd.setCursor(12,0);lcd.print("R");  //sağ düğme
    lcd.setCursor(13,0);lcd.print("L");  //sol düğme

    lcd.setCursor(0,1);lcd.print(x_degeri);
    lcd.setCursor(4,1);lcd.print(y_degeri);
    lcd.setCursor(8,1);lcd.print(joy_buton);
    lcd.setCursor(10,1);lcd.print(yukari_buton);
    lcd.setCursor(11,1);lcd.print(asagi_buton);
    lcd.setCursor(12,1);lcd.print(sag_buton);
    lcd.setCursor(13,1);lcd.print(sol_buton);
  }  
}
