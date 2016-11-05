#include "truck.h"
void initTruck(Truck *t, Path p, unsigned int cap){
	t->route.size = p.size;
	t->route.cities = p.cities;
	t->capacity = cap;
}
void forwardTruckRoute(Truck *t){
	forwardRoute(&t->route);
}
unsigned int getCapacity(Truck t){
	return t.capacity;
}
Path getRoute(Truck t){
	return t.route;
}
void setRoute(Truck *t, Path p){
	t->route.size = p.size;
	t->route.cities = p.cities;
}
