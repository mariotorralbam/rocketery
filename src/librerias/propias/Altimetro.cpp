/*
Inicializa las medidas de presión a cota 0 metros y 5 metros
La cota 0 metros se utilizará para determinar la altura máxima
La cota 5 metros se utilizará para determinar que el vuelo ha terminado
y activar el sistema de búsqueda.

La cota 0 metros se obtiene con la media aritméticas de 20 medidas de presión

La cota 5 metros se obtiene con la cota 0 metros añadiendo 0.60 milibares
*/

#include "Altimetro.h"
// METODOS PUBLICOS
void Altimetro::Initialize()
{
	altStatus = altimetro.begin();
	if (altStatus)
	{
		for (int i = 0; i < numMedidas; i++)
		{
			double medida = midePresion();
			if (medida != 0)
				cota0 += medida;
			else
			{
				cota0 = 0;
				break;
			}
		}

		cota0 = cota0 / numMedidas;
		cota5 = cota0 - 0.55;
	}
}

double Altimetro::midePresion()
{
	altStatus = altimetro.startTemperature();

	if (altStatus)
	{
		delay(altStatus);

		altStatus = altimetro.getTemperature(temperatura);

		if (altStatus)
		{
			delay(altStatus);

			altStatus = altimetro.startPressure(3);

			if (altStatus)
			{
				delay(altStatus);

				altStatus = altimetro.getPressure(presion, temperatura);

				if (altStatus)
				{
					return presion;
				}
				else
				{
					return altStatus;
				}
			}
			else
			{
				return altStatus;
			}
		}
		else
		{
			return altStatus;
		}
	}
	else
	{
		return altStatus;
	}
}

double Altimetro::getCota0()
{
	return cota0;
}

double Altimetro::getCota5()
{
	return cota5;
}

double Altimetro::getAltura(double cota0, double cotaMax)
{
	return altimetro.altitude(cotaMax, cota0);
}

