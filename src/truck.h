#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "route.h"
#define MAX 1000
typedef struct{
    unsigned int capacity;
    TRoute route; // todos os caminhões terão uma rota única.
}TTruck;

//Lista de caminhões para printar no final;
typedef struct{
    TTruck truck[MAX];
    unsigned int topo;
}TListTruck;

void initTruck(TTruck* truck, unsigned int capacity, TRoute* route);
void initListTruck(TListTruck* listTruck);
int insertListTruck(TListTruck* listTruck, TTruck* truck);
void printListTruck(TListTruck* listTruck);

#endif // TRUCK_H_INCLUDED
