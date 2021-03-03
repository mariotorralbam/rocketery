#include <EEPROM.h>
#include <Wire.h>

int value;
bool done;
void setup() {

  //Initiate Serial communication.
  Serial.begin(9600);
  value = 0;
  done = false;
}

void loop() {

  if (!done)
  {
    Serial.println("Proceso de grabado en EEPROM");
    EEPROM.write(0,3);
    Serial.println("Proceso de grabado en EEPROM terminado");

    Serial.println("Lectura de EEPROM");
    value = EEPROM.read(0);
    Serial.println("Lecutra completada");
    value = value + 3;
    Serial.println(value);

    done = true;
  }
}
