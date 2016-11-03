#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "city.h"
#define MAX 1000

typedef struct{
    TCity cities[MAX];
    unsigned int endNum;
    unsigned int num_city;
    unsigned int demand;
    unsigned int topo;
    unsigned int endSize;
}TRoute;

typedef struct{
    TRoute route[MAX];
    unsigned int num_city;
    unsigned int topo;
}TListRoute;


void initRoute(TRoute* route, unsigned int num_city);
void initListRoute(TListRoute* listRoute);
int insertRouteList(TListRoute* listRoute, TRoute* route);
int insertCityRoute(TRoute* route, TCity* city, unsigned int distance);

#endif // ROUTE_H_INCLUDED
