/*  Programa para medir la altura máxima
alcanzada por el cohete.

Está comprendido en dos partes.
La primera inicializa variables, establece cotas de referencia y valida 
estado de la memoria

La segunda determina si el modelo está en la guía, volando o descendiendo.
Durante la fase de vuelo realiza mediciones de presión para determinar
la altura máxima alcanzada y guardarla en memoria.

Durante las tres fases controla el estado del vuelo. Si es OK o KO
lo comunicará mediante una serie de pitidos en el zumbador.
*/
#include "Altimetro.h"
#include <EEPROM.h>
//
//Dispositivos
Altimetro altimetro;
int pinBuzzer = 9;
//
bool error;
//
//Presiones de referencia
double presionCota5;
//
//Presion actual
double actualPresion;
//
//Presion minima = maxima altura
double minimaPresion;
//
//Posición de memoria donde grabar
//el registro de altura
int memPos;
//********************************
//Funciones auxiliares
//********************************
//Inicializacion correcta
void signalInitOk()
{  
  //Serial.println("Inicialización completada correctamente");

  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(30);                       // Esperamos 30ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(100);                      // Esperamos 0.1 segundos
  
}
//Vuelo terminado correctamente
void signalVueloOk()
{
  //Serial.println("Vuelo completado correctamente");
  
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(30);                       // Esperamos 30ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(2000);                     // Esperamos 2 segundos
  
}
//Inicialización incorrecta
void signalInitKo()
{
  //Serial.println("Inicializacion con errores");
  
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  
}
//Erroes durante el vuelo
void signalVueloKo()
{
  //Serial.println("Vuelo finalizado con errores");
  
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(2000);                     // Esperamos 2 segundos
  
}
//Error de memoria llena
void memoryFull()
{
  //Serial.println("Memoria llena");
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(100);                      // Esperamos 100ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  
}
//Recupera la primera posición de memoria libre
//donde grabará la altura máxima registrada
//Si toda la memoria está llena, devuelve -1
int getEEPROMfst()
{
  bool mempos = false;
  int i =0;
  while (!mempos&&i<EEPROM.length())
  {
    if (!EEPROM.read(i))
    {
      mempos = true;
    }
    else
    {
      i++;
    }
  }
  if(mempos)
  {
    return i;
  }
  else
  {
    return -1;
  }
}
//
//********************************
// FUNCION SETUP
//********************************
//
void setup()
{
  // Serial.begin(9600);
  //Serial.println("INICIO");
  pinMode(pinBuzzer, OUTPUT);
  minimaPresion = 0;
  error = false;
//
  altimetro.Initialize();
//
  memPos = getEEPROMfst();
  if ( altimetro.getCota0() == 0 || memPos == -1)
  {
    error = true;
  }
  else
  {
    presionCota5 = altimetro.getCota5();
//   
    for (int i = 0; i < 3; i++)
    {
      signalInitOk();
    }
  }
}
//
//**********************************
//PROCESO PRINCIPAL
//**********************************
//
void loop()
{
  if (!error)
  {
    actualPresion = altimetro.midePresion();
    if (actualPresion == 0)
    {
      error = true;
    }
    if (minimaPresion == 0)
    {
      if (actualPresion < presionCota5) //Por encima de cota5 la presion será menor
      {
        minimaPresion = actualPresion;
      }
    }
    else
    {
      if (actualPresion < presionCota5)
      {
        if (actualPresion < minimaPresion)
        {
          minimaPresion = actualPresion;
        }
      }
      else
      {
        //Grabamos la altura máxima
        EEPROM.write(memPos, altimetro.getAltura(altimetro.getCota0(), minimaPresion));
        //Serial.print("Altura maxima = ");
        //Serial.println(altimetro.getAltura(altimetro.getCota0(), minimaPresion));
        while (true)
        {
          signalVueloOk();
        }
      }
    }
  }
  else
  {
    if (minimaPresion == 0)
    {
      if (memPos == -1)
      {
        while (true)
        {
          memoryFull();
        }
      }
      else
      {
        while (true)
        {
          signalInitKo();
        }
      }
    }
    else
    {
      signalVueloKo();
    }
  }
}