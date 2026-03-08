#include "iarduino_ADC_CS1237.h" 
#include <EEPROM.h>
#define EEPROM_START 0
#define MAGIC_NUMBER 0x1977

iarduino_ADC_CS1237 adc1(10, 9);
iarduino_ADC_CS1237 adc2(7, 6); 

int32_t read_dit; 
int32_t read_dash;
int32_t calc_pressure_threshold_dit; 
int32_t calc_pressure_threshold_dash;
int counter_dit;
int counter_dash;
int32_t read_dash_value;
int32_t read_dit_value;
int32_t factor_dit = 6250;   
int32_t factor_dash = 6250; 



struct config_t { 
  int eeprom_magic_number;
  int grams_dit;
  int grams_dash;
} configuration;


void setup() {

  
counter_dit = 0;
counter_dash = 0;
pinMode(3, OUTPUT); // dit
pinMode(12, OUTPUT); // dash

Serial.begin(115200);
 
  int magic = readInt(EEPROM_START);
  if (magic != MAGIC_NUMBER) {
    Serial.println("EEPROM not initialized, writing default values...");
    initDefaultConfig();
  } else {
    Serial.println("EEPROM already initialized, reading values...");
    readConfig();
  }

  // Print values
  Serial.print("Magic: "); Serial.println(configuration.eeprom_magic_number, HEX);
  Serial.print("Grams Dit: "); Serial.println(configuration.grams_dit);
  Serial.print("Grams Dash: "); Serial.println(configuration.grams_dash);

  bool i; 
  pinMode(LED_BUILTIN, OUTPUT);
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

  

  read_dash = (adc2.analogRead() / 1000) * 1000;
  read_dit = (adc1.analogRead() / 1000) * 1000;
 
  read_dash_value = read_dash;
  read_dit_value = read_dit;
  Serial.print(F("\n\r adc1 idle: "));
  Serial.print(read_dash);
  Serial.print(F("\n\r adc2 idle: "));
  Serial.println(read_dit);

  calc_pressure_threshold_dash = (configuration.grams_dash * factor_dash) + read_dash_value;
  Serial.println(calc_pressure_threshold_dash);
  calc_pressure_threshold_dit = (configuration.grams_dit * factor_dit) + read_dit_value;
  Serial.println(calc_pressure_threshold_dit);


  // R when ready

          digitalWrite(3, HIGH);
          delay(100);
          digitalWrite(3, LOW);
          delay(100);
          digitalWrite(12, HIGH);
          delay(100);
          digitalWrite(12, LOW);
          delay(100);
          digitalWrite(3, HIGH);
          delay(100);
          digitalWrite(3, LOW);
          delay(2500);




}




void loop() {
   
  read_dash = (adc2.analogRead() / 1000) * 1000;
  read_dit = (adc1.analogRead() / 1000) * 1000;
  Serial.print(F("\n\r waga dit: "));
  Serial.print((read_dit - read_dit_value) / factor_dit);
  Serial.print(F("\n\r waga dash: "));
  Serial.print((read_dash - read_dash_value) / factor_dash);
  Serial.print(F("\n\r grams dit: "));
  Serial.print(configuration.grams_dit);
  Serial.print(F("\n\r grams dash: "));
  Serial.println(configuration.grams_dash);


  
  
  if (read_dit > calc_pressure_threshold_dit) {
   
    digitalWrite(3, HIGH);
    counter_dit++;
    if (counter_dit == 200) {
      counter_dit = 0;
      digitalWrite(3, LOW);
      tara(1);
    }
  }
  else {
   
    digitalWrite(3, LOW);//extra
    counter_dit = 0;

  }  //
  if (read_dash > calc_pressure_threshold_dash) {
    
    digitalWrite(12, HIGH);
    counter_dash++;
    if (counter_dash == 200) {
      counter_dash = 0;
      digitalWrite(12, LOW);
      tara(2);
    }
  }
  else {
   
    digitalWrite(12, LOW);
    counter_dash = 0;  

  }  
 
  
}


 void tara(int paddle) {

  Serial.print("Tare");
  delay(2500);
  read_dash = (adc2.analogRead() / 1000) * 1000;
  read_dit = (adc1.analogRead() / 1000) * 1000;

  
  if (paddle == 2) {

          if (read_dit > calc_pressure_threshold_dit) {
          writeConfig();
          digitalWrite(12, HIGH);
          delay(100);
          digitalWrite(12, LOW);
          delay(2500);
          return;
          }
      
      configuration.grams_dash = configuration.grams_dash + 5;
        if (configuration.grams_dash == 50) {
          configuration.grams_dash = 5;
        }
    calc_pressure_threshold_dash = (configuration.grams_dash * factor_dash) + read_dash_value;
    
    for (int i = 0; i < configuration.grams_dash /5; i++) {
    digitalWrite(12, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(300);
    }
    



  }
  
  if (paddle == 1) {

          if (read_dash > calc_pressure_threshold_dash) {
          writeConfig();
          digitalWrite(3, HIGH);
          delay(100);
          digitalWrite(3, LOW);
          delay(2500);
          return;
          }

      configuration.grams_dit = configuration.grams_dit + 5;
        if (configuration.grams_dit == 50) {
          configuration.grams_dit = 5;
        }
    calc_pressure_threshold_dit = (configuration.grams_dit * factor_dit) + read_dit_value;

        for (int i = 0; i < configuration.grams_dit /5; i++) {
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        delay(350);
        }
    
  }
  
}

// --- Helper functions ---
void writeInt(int address, int value) {
  EEPROM.write(address, (value >> 8) & 0xFF);
  EEPROM.write(address + 1, value & 0xFF);
}

int readInt(int address) {
  return (EEPROM.read(address) << 8) | EEPROM.read(address + 1);
}

void writeInt32(int address, int32_t value) {
  EEPROM.write(address, (value >> 24) & 0xFF);
  EEPROM.write(address + 1, (value >> 16) & 0xFF);
  EEPROM.write(address + 2, (value >> 8) & 0xFF);
  EEPROM.write(address + 3, value & 0xFF);
}

int32_t readInt32(int address) {
  return ((int32_t)EEPROM.read(address) << 24) |
         ((int32_t)EEPROM.read(address + 1) << 16) |
         ((int32_t)EEPROM.read(address + 2) << 8) |
         EEPROM.read(address + 3);
}

// --- Write the full config ---
void writeConfig() {
  int addr = EEPROM_START;
  writeInt(addr, configuration.eeprom_magic_number); addr += 2;
  writeInt(addr, configuration.grams_dit); addr += 2;
  writeInt(addr, configuration.grams_dash); addr += 2;
}

// --- Read the full config ---
void readConfig() {
  int addr = EEPROM_START;
  configuration.eeprom_magic_number = readInt(addr); addr += 2;
  configuration.grams_dit = readInt(addr); addr += 2;
  configuration.grams_dash = readInt(addr); addr += 2;
}

// --- Initialize default config ---
void initDefaultConfig() {
  configuration.eeprom_magic_number = MAGIC_NUMBER;
  configuration.grams_dit = 5;
  configuration.grams_dash = 5;

  writeConfig();
}
