#include "citystack.h"


void initCityStack(CityStack *cs){
	cs->top = 0;
	cs->end_Requirements = 0;
}
void push(CityStack *cs,City c){
	cs->cities[cs->top++] = c;
	cs->end_Requirements += c.requirements;
}
void pop(CityStack *cs,City *c){
	*c = cs->cities[--cs->top];
	cs->end_Requirements -= c->requirements;
}
unsigned int size(CityStack *cs){
	return cs->top;
}
