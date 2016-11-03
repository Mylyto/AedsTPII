#ifndef TRUCK_H
#define TRUCK_H
#include "path.h"
typedef struct{
	unsigned int capacity;
	Path route;
} Truck;
void initTruck(Truck *, Path, unsigned int);
void forwardTruckRoute(Truck *);
unsigned int getCapacity(Truck);
Path getRoute(Truck);
void setRoute(Truck*,Path);

#endif
