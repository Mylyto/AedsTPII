#include "citystack.h"
void initCityStack(CityStack *cs){
	cs->top = 0;
	cs->end_requirements = 0;
	cs->greater_requirements = 0;
}
void push(CityStack *cs,City c){
	cs->cities[cs->top++] = c;
	cs->end_requirements += c.requirements;
	if(cs->greater_requirements<c.requirements){
        	cs->greater_requirements=c.requirements;
	}
}
void pop(CityStack *cs,City *c){
	*c = cs->cities[--cs->top];
	cs->end_requirements -= c->requirements;
	cs->greater_requirements = 0;
}
unsigned int getGreaterRequirements(CityStack *cs){
	unsigned int i, greater_requirements;
	if(cs->greater_requirements == 0 && size(cs) != 0){
		greater_requirements = cs->cities[0].requirements;
		for (i = 1; i < cs->top; i++) {
			if(greater_requirements < cs->cities[i].requirements){
				greater_requirements = cs->cities[i].requirements;
			}
		}
		cs->greater_requirements = greater_requirements;
	}
	return cs->greater_requirements;
}
unsigned int size(CityStack *cs){
	return cs->top;
}
