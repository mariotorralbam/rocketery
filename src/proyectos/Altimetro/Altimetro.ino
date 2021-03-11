/*  Programa para medir la altura máxima
alcanzado por el cohete.

Está comprendido en dos partes.
La primera inicializa variables y establece cotas de referencia

La segunda determina si el modelo está en la guía, volando o descendiendo.
Durante la fase de vuelo realiza mediciones de presión para determinar
la altura máxima alcanzada y guardarla en memoria.

Durante las tres fases controla si se dan errores que los comunicará
mediante pitidos del zumbador
*/
#include "Altimetro.h"
#include <EEPROM.h>
//
//Dispositivos
Altimetro altimetro;
//int pinBuzzer = 9;
//
bool error;
bool volando;
//
//Presiones de referencia
//double presionCota0;
double presionCota5;
//
//Presion actual
double actualPresion;
//
//Presion minima = maxima altura
double minimaPresion;
//double maxAltura;
//Funciones auxiliares
void signalInitOk()
{  
  Serial.println("Inicialización completada correctamente");
//
  /*
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(30);                       // Esperamos 30ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(500);                     // Esperamos 0.5 segundos
  */
}
//
void signalVueloOk()
{
  Serial.println("Vuelo completado correctamente");
  /*
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(30);                       // Esperamos 30ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(2000);                     // Esperamos 2 segundos
  */
}
//
void signalInitKo()
{
  Serial.println("Inicializacion con errores");
  /*
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  */
}
//
void signalVueloKo()
{
  Serial.println("Vuelo finalizado con errores");
  /*
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, HIGH);   // Ponemos en alto(5V) el pin del buzzer
  delay(60);                       // Esperamos 60ms
  digitalWrite(pinBuzzer, LOW);    // Ponemos en bajo(0V) el pin del buzzer
  delay(2000);                     // Esperamos 2 segundos
  */
}
//
void setup()
{
  //pinMode(pinBuzzer, OUTPUT);
//
  volando = false;
  error = false;
//
  altimetro.Initialize();
//
  //presionCota0 = altimetro.getCota0();
  if ( altimetro.getCota0() == 0)
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
        //volando = true;
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
        //maxAltura = altimetro.getAltura(altimetro.getCota0(), minimaPresion);
        EEPROM.write(0, altimetro.getAltura(altimetro.getCota0(), minimaPresion));
        while (true)
        {
          signalVueloOk();
        }
      }
    }
  }
  else
  {
    if (!volando)
    {
      while (true)
      {
        signalInitKo();
      }
    }
    else
    {
      signalVueloKo();
    }
  }
}
