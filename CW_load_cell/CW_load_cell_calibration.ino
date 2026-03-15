
// Calibration



#include "iarduino_ADC_CS1237.h" 
iarduino_ADC_CS1237 adc1(10, 9);
iarduino_ADC_CS1237 adc2(7, 6); 

int32_t read_dit; 
int32_t read_dash;




void setup() {
 

Serial.begin(115200);
 
  bool i; 
  adc1.setPulseWidth(30);
  // adc1.begin();
  i = adc1.begin();
  if (!i) { Serial.print(F("\n\r adc1 not present ")); }
  adc1.setPinVrefOut(true);
  adc1.setVrefIn(5.0);
  adc1.setSpeed(640);
  adc1.setPGA(2);
  adc1.setChannel(0);

  adc2.setPulseWidth(30);
  //adc2.begin();
  i = adc2.begin();
  if (!i) { Serial.print(F("\n\r adc2 not present ")); }
  adc2.setPinVrefOut(true);
  adc2.setVrefIn(5.0);
  adc2.setSpeed(640);
  adc2.setPGA(2);
  adc2.setChannel(0);



  
}




void loop() {
   
  read_dash = (adc2.analogRead() / 10000) * 10000;
  read_dit = (adc1.analogRead() / 1000) * 1000;
  Serial.print(F("\n\r dash: "));
  Serial.print(read_dash);
  Serial.print(F("\n\r dit: "));
  Serial.println(read_dit);
 
 
}