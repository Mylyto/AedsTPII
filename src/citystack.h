#ifndef CITYSTACK_H
#define CITYSTACK_H
#include "city.h"

#define MAXSTACKSIZE 200

typedef struct {
	City cities[MAXSTACKSIZE];
	unsigned int endRequirements; // MUDANÇA ARMAZENAR O SOMATORIO DE DEMANDA
	unsigned int greater_Requirements; // MUDANÇA PARA ARMAZENAR A MAIOR DEMANDA
	unsigned int top;
} CityStack;

void initCityStack(CityStack* cs);
void push(CityStack* cs,City c);
void pop(CityStack* cs,City* c);
unsigned int size(CityStack* cs);
#endif
