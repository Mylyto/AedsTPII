#ifndef CITYSTACK_H
#define CITYSTACK_H

#define MAXSTACKSIZE 200
#include "city.h"
typedef struct {
	City cities[MAXSTACKSIZE];
	unsigned int end_Requirements; // MUDANÇA ARMAZENAR O SOMATORIO DE DEMANDA
	unsigned int top;
} CityStack;

void initCityStack(CityStack* cs);
void push(CityStack* cs,City c);
void pop(CityStack* cs,City* c);
unsigned int size(CityStack* cs);

#endif
