#ifndef PATH_H
#define PATH_H
#include "citystack.h"
typedef struct{
	CityStack cities;
	unsigned int size;
}Path;
void initPath(Path*,City*,unsigned int);
void forwardRoute(Path*);
unsigned int getSize(Path*);
City getNextCity(Path*);
#endif
