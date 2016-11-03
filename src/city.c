#include "city.h"
static int city_IDs = 0;
void initCity(City* c,unsigned int i){
	c->requirements = i;
	c->met_requirements = 0;
	c->id = city_IDs++;
}
void meetRequirements(City* c){
	c->met_requirements = 1;
}
unsigned int getRequirements(City c){
	return c.requirements;
}
unsigned char getMetRequirements(City c){
	return c.met_requirements;
}
