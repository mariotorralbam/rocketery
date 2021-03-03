/*  This is a default program--
  Use File->Load Prog to load a different program
*/
#include <EEPROM.h>
bool valueSet = false;

int sevenSeg100 [] = {0,1,2,3};
int sevenSeg10 [] = {4,5,6,7};
int sevenSeg1 [] = {8,9,10,11};
int sevenSegLow = 12;

int randomNumber;
int randomNumberAux;

int hundredAux = 0;
int tensAux = 0;
int unitsAux = 0;

int hundred = 0;
int tens = 0;
int units = 0;

int binaryAuxiliar[10];
int dividends[] = {100,10,1};

void setup()
{
  //pinMode(piezoPin,OUTPUT);

  for (int i = 0; i < 3; i++ )
  {
    pinMode(sevenSeg100[i],OUTPUT);
    pinMode(sevenSeg10[i],OUTPUT);
    pinMode(sevenSeg1[i],OUTPUT);
  }
  pinMode(sevenSegLow,OUTPUT);
}

void loop()
{
  if (!valueSet)
  {
    randomNumber = random(999);
    randomNumberAux = randomNumber;

    for (int i = 0; i<3;i++)
    {
      if ( i == 0 && randomNumber > 99 )
      {
        hundredAux = randomNumberAux / 100;
        randomNumberAux = randomNumberAux%100;
      }

      if ( i == 1 && randomNumber > 9)
      {
        tensAux = randomNumberAux / 10;
        randomNumberAux = randomNumberAux%10;
      }

      if ( i == 2 )
      {
        unitsAux = randomNumberAux;
      }
    }

    digitalWrite(sevenSegLow,HIGH);

    initializeDisplay();

    EEPROM.write(0,hundredAux);
    EEPROM.write(1,tensAux);
    EEPROM.write(2,unitsAux);

    hundred = EEPROM.read(0);
    tens = EEPROM.read(1);
    units = EEPROM.read(2);

    for (int i = 0; hundred > 0; i++)
    {
      binaryAuxiliar[i]=hundred%2;
      hundred = hundred/2;
    }

    for (int i = 0; i<4; i++)
    {
      toBinaryH(i);
    }

    initializeDisplay();

    for (int i = 0; tens > 0; i++)
    {
      binaryAuxiliar[i]=tens%2;
      tens = tens/2;
    }

    for (int i = 0; i<4; i++)
    {
      toBinaryT(i);
    }

    initializeDisplay();

    for (int i = 0; units > 0; i++)
    {
      binaryAuxiliar[i]=units%2;
      units = units/2;
    }

    for (int i = 0; i<4; i++)
    {
      toBinaryU(i);
    }

    digitalWrite(sevenSegLow,LOW);
    valueSet=true;
  }

  delay(1000);
}

void initializeDisplay()
{
  for (int i = 0; i < 10; i++)
  {
    binaryAuxiliar[i]=0;
  }
}

void toBinaryH(int i)
{
  if ( binaryAuxiliar[i] == 0 )
  {
    digitalWrite(sevenSeg100[i],LOW);
  }
  else
  {
    digitalWrite(sevenSeg100[i],HIGH);
  }
}

void toBinaryT(int i)
{
  if ( binaryAuxiliar[i] == 0 )
  {
    digitalWrite(sevenSeg10[i],LOW);
  }
  else
  {
    digitalWrite(sevenSeg10[i],HIGH);
  }
}

void toBinaryU(int i)
{
  if ( binaryAuxiliar[i] == 0 )
  {
    digitalWrite(sevenSeg1[i],LOW);
  }
  else
  {
    digitalWrite(sevenSeg1[i],HIGH);
  }
}
