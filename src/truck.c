#include <stdio.h>
#include <stdlib.h>
#include "truck.h"

void initTruck(TTruck* truck, unsigned int capacity){
    truck->capacity = capacity;
    truck->filled = 0;
    truck->used = 0;

}
void initListTruck(TListTruck* listTruck){
    listTruck->topo = 0;
}
int insertListTruck(TListTruck* listTruck, TTruck* truck){
    if(listTruck->topo==MAX)
        return 0;
    listTruck->truck[listTruck->topo] = *truck;
    listTruck->topo++;
    return 1;
}
