#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#define MAX 1000
typedef struct{
    unsigned int capacity;
    unsigned int filled;
    unsigned int used;
}TTruck;

typedef struct{
    TTruck truck[MAX];
    unsigned int topo;
}TListTruck;

void initTruck(TTruck* truck, unsigned int capacity);
void initListTruck(TListTruck* listTruck);
int insertListTruck(TListTruck* listTruck, TTruck* truck);

#endif // TRUCK_H_INCLUDED
