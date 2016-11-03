#include <stdio.h>
#include <stdlib.h>
#include "city.h"

void initCity(TCity* city, unsigned int position){
    city->demand = rand()%1000+1;
    city->visitd = 0;
    city->ID = position;
}
void initListCity(TListCity* listCity){
    listCity->topo=0;
    listCity->greater_Demand = 0;
}
int insertListCity(TListCity* listCity, TCity* city){
    if(listCity->topo==MAX)
        return 0;
    listCity->city[listCity->topo] = *city;
    listCity->sumDemand += listCity->city[listCity->topo].demand;
    if(listCity->greater_Demand < city->demand)
        listCity->greater_Demand = city->demand;
    listCity->topo++;
    return 1;
}
