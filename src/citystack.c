#include "citystack.h"
void initCityStack(CityStack *cs){
	cs->top = 0;
}
void push(CityStack *cs,City c){
	cs->cities[cs->top++] = c;
}
void pop(CityStack *cs,City *c){
	*c = cs->cities[--cs->top];
}
unsigned int size(CityStack *cs){
	return cs->top;
}
