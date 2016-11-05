#include "citystack.h"


void initCityStack(CityStack *cs){
	cs->top = 0;
	cs->endRequirements = 0;
	cs->greater_Requirements =0;
}
void push(CityStack *cs,City c){
	cs->cities[cs->top++] = c;
	cs->endRequirements += c.requirements;
	if(cs->greater_Requirements<c.requirements)
        cs->greater_Requirements=c.requirements;
}
void pop(CityStack *cs,City *c){
	*c = cs->cities[--cs->top];
	cs->endRequirements -= c->requirements;
}
unsigned int size(CityStack *cs){
	return cs->top;
}
