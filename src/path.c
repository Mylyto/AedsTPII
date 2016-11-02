#include "path.h"
void initPath(Path *p,City *c,unsigned int sz){
	int i;
	p->size = sz;
	initCityStack(&p->cities);
	for (i = sz - 1; i >= 0; i--) {
		push(&p->cities,c[i]);
	}
}
void forwardRoute(Path *p){
	City c;
	pop(&p->cities,&c);
}
unsigned int getSize(Path *p){
	return p->size;
}
City getNextCity(Path *p){
	return p->cities.cities[(p->cities.top-1)];
}
