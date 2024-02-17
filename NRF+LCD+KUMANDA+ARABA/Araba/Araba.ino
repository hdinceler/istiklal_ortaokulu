#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define yakinlik_siniri  5   // araba bu cm cinsinden degerden  daha yakın cisim algılarsa dursun
long zaman=0;
long mesafe_on=0;
long mesafe_arka=0;
unsigned long baslangic_zamani_millis=0;;
unsigned long baslangic_zamani_micros=0;;
char buff[10];

unsigned int x_degeri=0;
unsigned int y_degeri=0;
unsigned int joy_buton=0;
unsigned int yukari_buton=0;
unsigned int asagi_buton=0;
unsigned int sag_buton=0;
unsigned int sol_buton=0;

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

RF24 radio(CE_PIN , CSN_PIN); // CE, CSN pimleri
char gelen_komut[32] = "";

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
   //Serial.println(gelen_komut);
    //gelen komut cümlesi parçalara ayrıştırılıyor
    // Serial.print(gelen_komut);Serial.print("-");
    strcpy( buff , strtok( gelen_komut,  "," ) ); x_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); y_degeri= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); joy_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); yukari_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); asagi_buton= atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); sag_buton = atoi(buff);
    strcpy( buff , strtok(NULL,  "," ) ); sol_buton= atoi(buff);
    //  komut parçaları çıkış pinlerine dağıtılıyor
    digitalWrite(pin_on_far , yukari_buton );
    digitalWrite(pin_sis_fari,sol_buton );
    digitalWrite(pin_korna, sag_buton);
    // Serial.print(x_degeri);Serial.print(",");
    // Serial.print(y_degeri);
     Serial.print(",\n");

  // motor sürücü yönetimi
  if (y_degeri >=526 && y_degeri < 1024){   ileri_git( map(y_degeri, 526,1023, 0,255) ); } 
  else if (y_degeri >= 0 && y_degeri < 520) {geri_git(map(y_degeri, 520, 0, 0, 255)); }
  else if (x_degeri >= 0 && x_degeri < 504) {sola_don(map(x_degeri, 504, 0, 0, 255)); }
  else if (x_degeri > 510 && x_degeri < 1024) {saga_don(map(x_degeri, 510, 1023, 0, 255)); }
  else dur();
  
    //LCD ekrana konum yazdırma işlemleri
    lcd.setCursor(1,0);lcd.print("X"); //Joystick X exseni
    lcd.setCursor(6,0);lcd.print("Y");  //Joystick Y ekseni
    lcd.setCursor(10,0);lcd.print("J");  //Joystick butonu
    lcd.setCursor(11,0);lcd.print("U");  //yukarı düğme
    lcd.setCursor(12,0);lcd.print("D");  //aşağı düğme
    lcd.setCursor(13,0);lcd.print("R");  //sağ düğme
    lcd.setCursor(14,0);lcd.print("L");  //sol düğme

    lcd.setCursor(0,1);lcd.print(x_degeri);
    lcd.setCursor(5,1);lcd.print(y_degeri);
    lcd.setCursor(10,1);lcd.print(joy_buton);
    lcd.setCursor(11,1);lcd.print(yukari_buton);
    lcd.setCursor(12,1);lcd.print(asagi_buton);
    lcd.setCursor(13,1);lcd.print(sag_buton);
    lcd.setCursor(14,1);lcd.print(sol_buton);
  }  
}
