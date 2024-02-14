#ifndef ARABA_KUTUPHANE_H
#define ARABA_KUTUPHANE_H

  void turn_right(uint8_t speed);
  void turn_left(uint8_t speed);
  void right_back(uint8_t speed);
  void right_forward(uint8_t speed);
  void left_back (uint8_t speed);
  void left_forward(uint8_t speed);
  void left_stop();
  void right_stop();
  void all_stop();
  void motor_test();
  bool zaman_say_milis(unsigned int zaman_say_interval  );
  bool zaman_say_micros(unsigned int zaman_say_interval  );
  void run_right( signed short speed);
  void run_left(  signed short speed);
  void alarm(uint8_t mesafe);
  uint8_t mesafe_olc();
  bool zaman_say_milis(unsigned int zaman_say_interval  );
  bool zaman_say_micros(unsigned int zaman_say_interval  );


void alarm(uint8_t mesafe){
        digitalWrite(pin_far, HIGH);
        digitalWrite(pin_korna, HIGH);
        delay(4 * mesafe);      
        digitalWrite(pin_far, LOW);
        digitalWrite(pin_korna, LOW);
        delay(4 * mesafe );      
}

uint8_t mesafe_olc(){
  if( zaman_say_micros(500) ){
    digitalWrite(pin_mesafe_trig, HIGH);
    if( zaman_say_micros(10)  ) digitalWrite(pin_mesafe_trig, LOW);
    zaman = pulseIn(pin_mesafe_echo, HIGH);
    mesafe = (zaman / 29.1) / 2;
    return mesafe;
  }
}


 bool zaman_say_milis(unsigned int zaman_say_interval  ){
        unsigned long currentTime = millis();
        // İki sinyal arasındaki süreyi kontrol et
        if (currentTime - baslangic_zamani_millis >= zaman_say_interval) {
            baslangic_zamani_millis = currentTime; // Sonraki sinyal için süre sayacını sıfırla
            return true;
        }
        return false;
    }
 bool zaman_say_micros(unsigned int zaman_say_interval  ) {
        unsigned long currentTime = micros();
        // İki sinyal arasındaki süreyi kontrol et
        if (currentTime - baslangic_zamani_micros >= zaman_say_interval) {
            baslangic_zamani_micros = currentTime; // Sonraki sinyal için süre sayacını sıfırla
            return true;
        }
        return false;
    }

 



  void run_right(signed short speed){
    if ( speed ==0  ) right_stop();
    else if( speed >0  && speed < 256   )   right_forward(  speed     );
    else if( speed <0  && speed > -256  )   right_back(   abs(speed)  );
  }
  void run_left(signed short speed){
    if ( speed ==0  ) right_stop();
    else if( speed >0  && speed < 256   )   left_forward(   speed     );
    else if( speed <0  && speed > -256  )     left_back(     abs(speed)   );
  }


  void right_back(uint8_t speed){
    analogWrite( pin_R1 , speed );
    analogWrite( pin_R2 , 0 );
    Serial.print("--right_back:");
    Serial.print(speed);
  }

  void right_forward(uint8_t speed){
    analogWrite( pin_R1 , 0 );
    analogWrite( pin_R2 , speed );
    Serial.print("--right_forward:");
    Serial.print(speed);
  }

  void left_back (uint8_t speed){
    analogWrite( pin_L1 , 0 );
    analogWrite( pin_L2 , speed );
    Serial.print(" --left_back:");
    Serial.print(speed);
  }

  void left_forward(uint8_t speed){
    analogWrite( pin_L1 , speed );
    analogWrite( pin_L2 , 0 );
    Serial.print("--left_forward:");
    Serial.print(speed);
  }

  void left_stop(){
    analogWrite( pin_L1 , 0 );
    analogWrite( pin_L2 , 0 );
    Serial.print("--left_stop");
  }
  void right_stop(){
    analogWrite( pin_R1 , 0 );
    analogWrite( pin_R2 , 0 );
    Serial.print("--right_stop");
  }

  void turn_right(uint8_t speed){
    right_back(speed);
    left_forward(speed);
    Serial.print("--turn_right:");
    Serial.print(speed);
  }
  void turn_left(uint8_t speed){
    right_forward(speed);
    left_back(speed);
    Serial.print("--turn_left:");
    Serial.print(speed);
  }

  void all_stop(){
    right_stop();
    left_stop();  
    Serial.print("--  all_stop");
  }
  void motor_test(){
    right_forward(255);
    delay(2000);
    right_back(255);
    delay(2000);
    right_stop();

    left_forward(255);
    delay(2000);
    left_back(255);
    delay(2000);
    left_stop();
    Serial.print("\n motor_test ");
  }
#endif
