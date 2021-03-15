/*
Rutina para la lectura de la memoria EEPROM y escritura
en consola de las alturas registradas
*/
#include <EEPROM.h>
//
bool endLecture;
int memPos;
double altValue;

template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

//SETUP
void setup() {
  endLecture = false;
  memPos = 0;
  Serial.begin(9600);
  Serial.println("*************************");
  Serial.println("INICIALIZACION COMPLETADA");
  Serial.println("*************************");
  Serial.println(" ");
  Serial.println("Cargada rutina de lectura y presentación de alturas máximas registradas");
  delay(2000);
}
//MAIN PROCESS
void loop() {
  while(!endLecture)
  {
    altValue = 0;
    EEPROM_readAnything(memPos,altValue);
    if (!altValue)
    {
      Serial.println("Finalizada lectura de memoria");
      endLecture = true;
    }
    else
    {
      Serial.print("Altura máxma registrada = ");
      Serial.print(altValue);
      Serial.println(" m.");
      Serial.println("**********");
    }
    memPos++;
    delay(2000);
  }
}