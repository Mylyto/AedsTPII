#include <stdio.h>
#include <stdlib.h>
#include "route.h"

void initRoute(TRoute* route, unsigned int num_city){
    route->endNum = num_city;
    route->demand = 0;
    route->endSize = 0;
    route->topo = 0;
    route->num_city = 0;
}

void initListRoute(TListRoute* listRoute){
    listRoute->topo = 0;
    listRoute->num_city = 0;
}

int insertRouteList(TListRoute* listRoute, TRoute* route){
    if(listRoute->topo == MAX)
        return 0;
    listRoute->route[listRoute->topo] = *route;
    listRoute->num_city = route->num_city;
    listRoute->topo++;
    return 1;
}

int insertCityRoute(TRoute* route, TCity* city, unsigned int distance){
    if(route->topo==route->endNum)
        return 0;
    route->cities[route->topo] = *city;
    route->demand += route->cities[route->topo].demand;
    route->cities[route->topo].visitd = 1;
    route->endSize += distance;
    route->topo++;
    return 1;
}

