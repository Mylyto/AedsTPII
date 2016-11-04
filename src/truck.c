#include <stdio.h>
#include <stdlib.h>
#include "truck.h"
// Inicializa o caminhão;
void initTruck(TTruck* truck, unsigned int capacity, TRoute* route){
    truck->capacity = capacity; // atribui a capacidade ao caminhão
    if(truck->capacity < route->endDemand) // verifica se a demanda da rota é compatível com a capacidade do caminhão
        return 0;
    return 1;
}
//INicializa a lista
void initListTruck(TListTruck* listTruck){
    listTruck->topo = 0;
}

//insere uma lista de caminhãos
int insertListTruck(TListTruck* listTruck, TTruck* truck){
    if(listTruck->topo==MAX) // vế se a lista tem posões disponíveis
        return 0;
    listTruck->truck[listTruck->topo] = *truck;//insere o caminhão na lista
    listTruck->topo++; // incrementa o topo.
    return 1;
}

void printListTruck(TListTruck * listtruck){
    int i;
        for(i=0;i<listtruck->topo; i++){
            printf("[");
            printf(" %d ", listtruck->truck[listtruck->topo].route.cities[i].ID);
            printf("]");
    }

}
