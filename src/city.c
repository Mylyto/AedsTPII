#include "city.h"
static int city_IDs = 0;
int initCity(Generator *g,City* c,unsigned int req){
	if(req > g->truck_capacity){
		return 0;
	}
	c->requirements = req;
	c->met_requirements = 0;
	c->id = city_IDs++;
	return 1;
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
