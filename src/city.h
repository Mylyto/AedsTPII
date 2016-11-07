#ifndef CITY_H
#define CITY_H
#include <time.h>
#include "generator.h"
#include <stdlib.h>
typedef struct{
	unsigned int id;
	unsigned int requirements;
	unsigned char met_requirements;
}City;
int initCity(Generator *g,City* c,unsigned int req);
void meetRequirements(City*);
unsigned int getRequirements(City);
unsigned char getMetRequirements(City);
#endif
