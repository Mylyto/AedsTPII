#ifndef CITYSTACK_H
#define CITYSTACK_H
#include "city.h"
#define MAXSTACKSIZE 1000
typedef struct {
	City cities[MAXSTACKSIZE];
	unsigned int top;
} CityStack;
void initCityStack(CityStack*);
void push(CityStack*,City);
void pop(CityStack*,City*);
unsigned int size(CityStack*);

#endif
