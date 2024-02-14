#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(9,10); // CE, CSN
char giden_komut[32];

  #define pin_far 2
  #define pin_korna 4
  #define pin_gaz_sag A0
  #define pin_gaz_sol A1
  
  signed short rightSpeed=0;
  signed short leftSpeed=0;
  uint8_t far_durum=0;
  uint8_t korna_durum=0; 
  int  get_potans( unsigned short read, unsigned short frw_max, unsigned short frw_min, unsigned short bck_min,unsigned short bck_max);
void setup() {
  
  pinMode( pin_far , INPUT_PULLUP );
  pinMode( pin_korna , INPUT_PULLUP );
  pinMode( pin_gaz_sag , INPUT );
  pinMode( pin_gaz_sol , INPUT );

  radio.begin();
  Serial.begin(9600);
  radio.openWritingPipe(0xF0F0F0F0E12E);
  radio.setPALevel(RF24_PA_MIN); // en düşük seviye enerji tüketimi , düşük sinyal menzili
  radio.stopListening();//verici  modunda çalış. 
}

void loop() {

  rightSpeed = get_potans(  analogRead( pin_gaz_sag )  , 730, 455,304,0 );
  leftSpeed = get_potans(  analogRead( pin_gaz_sol )  , 755, 508,260,150 );
  
  far_durum = !digitalRead( pin_far ); 
  korna_durum = !digitalRead( pin_korna ); 

  sprintf( giden_komut , "%d,%d,%d,%d", leftSpeed ,rightSpeed, far_durum , korna_durum );

  radio.write(&giden_komut , sizeof(giden_komut));
  Serial.print ( analogRead( pin_gaz_sol ));
  Serial.print ( "-" );
  Serial.print ( analogRead( pin_gaz_sag ));
  Serial.print("--Kumanda:");
  Serial.println(giden_komut);
  //delay(20);
}


  int get_potans( unsigned short read, unsigned short frw_max, unsigned short frw_min, unsigned short bck_min,unsigned short bck_max){
            signed short speed=0;
            if(read>frw_max) speed=255;
            else if(  read <= frw_max && read >=  frw_min ) speed=map( read , frw_min, frw_max, 0 ,255 );
            else if(  read <  frw_min && read >   bck_min ) speed=0;
            else if(  read <= bck_min && read >=  bck_max ) speed=map( read , bck_min, bck_max, 0 ,-255 );
            else if(  read <  bck_max ) speed=-255;
            return speed;
  }
