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
        digitalWrite(pin_on_far, HIGH);
        digitalWrite(pin_korna, HIGH);
        delay(4 * mesafe);      
        digitalWrite(pin_on_far, LOW);
        digitalWrite(pin_korna, LOW);
        delay(4 * mesafe );      
}

uint8_t mesafe_olc_on(){
  if( zaman_say_micros(500) ){
    digitalWrite(pin_mesafe_trig_on, HIGH);
    if( zaman_say_micros(10)  ) digitalWrite(pin_mesafe_trig_on, LOW);
    zaman = pulseIn(pin_mesafe_echo_on, HIGH);
    mesafe_on = (zaman / 29.1) / 2;
    return mesafe_on;
  }
}
uint8_t mesafe_olc_arka(){
  if( zaman_say_micros(500) ){
    digitalWrite(pin_mesafe_trig_arka, HIGH);
    if( zaman_say_micros(10)  ) digitalWrite(pin_mesafe_trig_arka, LOW);
    zaman = pulseIn(pin_mesafe_echo_arka, HIGH);
    mesafe_arka = (zaman / 29.1) / 2;
    return mesafe_arka;
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

 

void ileri_git(uint8_t hiz){
  Serial.print("ileri_hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( pin_sag_teker_ileri, hiz );analogWrite( pin_sol_teker_ileri, hiz );analogWrite( pin_sag_teker_geri, 0 );analogWrite(pin_sol_teker_geri, 0 );
}
void geri_git(uint8_t hiz){
  Serial.print("geri_hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( pin_sag_teker_ileri, 0 );analogWrite( pin_sol_teker_ileri, 0 );analogWrite( pin_sag_teker_geri, hiz );analogWrite(pin_sol_teker_geri, hiz );
}

void saga_don(uint8_t hiz){
  Serial.print("saga hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( pin_sag_teker_ileri, 0 );analogWrite( pin_sol_teker_ileri, hiz );analogWrite( pin_sag_teker_geri, hiz  );analogWrite(pin_sol_teker_geri, 0 );

}

void sola_don(uint8_t hiz){
  Serial.print("sola hiz:");
  Serial.print(hiz);
  Serial.print("-");
  analogWrite( pin_sag_teker_ileri, hiz );analogWrite( pin_sol_teker_ileri, 0 );analogWrite( pin_sag_teker_geri, 0 );analogWrite(pin_sol_teker_geri, hiz  );

}
void dur(){
  analogWrite( pin_sag_teker_ileri, 0 );analogWrite( pin_sol_teker_ileri, 0 );analogWrite( pin_sag_teker_geri, 0 );analogWrite(pin_sol_teker_geri, 0  );
  // Serial.println("dur");
}


 
#endif
