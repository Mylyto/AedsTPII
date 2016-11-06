#ifndef CITY_H
#define CITY_H
#include <time.h>
#include <stdlib.h>
typedef struct{
	unsigned int id;
	unsigned int requirements;
	unsigned char met_requirements;
}City;
void initCity(City*);
void meetRequirements(City*);
unsigned int getRequirements(City);
unsigned char getMetRequirements(City);
#endif
