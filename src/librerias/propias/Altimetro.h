// Altimetro.h
//Funciones del altimetro.
//Determinar cota0 y cota5 elegida como umbral
//Obtener medidas de presión durante el vuelo para obtener altura máxima
#ifndef _ALTIMETRO_h
#define _ALTIMETRO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SFE_BMP180.h>

class Altimetro
{
private:
	double cota0;
	double cota5;
	double temperatura;
	double presion;
	char altStatus;
	const int numMedidas = 20;
	SFE_BMP180 altimetro;
public:
	void Initialize();
	double midePresion();
	double getCota0();
	double getCota5();
	double getAltura(double cota0, double cotaMax);
};
#endif

