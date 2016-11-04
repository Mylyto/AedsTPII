#include <stdio.h>
#include <stdlib.h>
#include "city.h"

void initCity(TCity* city, unsigned int position){
    city->demand = rand()%1000+1 * 10;//gera aleatoriamente a demanda da cidade.
    city->visitd = 0; // diz se a cidade já foi ou não visitada.
    city->ID = position; // diz qual a posição da cidade em relação ao vetor, um identificador.
}

void initListCity(TListCity* listCity){
    listCity->topo=0; // inicializa o vetor na posição zero
    listCity->greater_Demand = 0; // atirbui a maior demanda como zero por padão.
}

int insertListCity(TListCity* listCity, TCity* city){
    if(listCity->topo==MAX)// verifica se a lista não está cheia
        return 0;
    listCity->city[listCity->topo] = *city; // atribui cidade no topo.
    listCity->sumDemand += listCity->city[listCity->topo].demand; // soma a demanda da cidade ao somatorio de demanda
    if(listCity->greater_Demand < city->demand) // verifica se a nova cidade tem a maior demanda de todas da lista
        listCity->greater_Demand = city->demand; // se sim a guarda ela
    listCity->topo++;
    return 1;
}
