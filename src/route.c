#include <stdio.h>
#include <stdlib.h>
#include "route.h"
//Inicializa a rota
void initRoute(Route* route, unsigned int num_city){
//    route->endNum = num_city;
    route->endDemand = 0;
    route->theSize = 0;
    route->topo = 0;
}
//Inicializa a lista de rotas
void initListRoute(ListRoute* listRoute){
    listRoute->topo = 0;
    listRoute->endSize = 0;
}

//insere uma rota na lista
int insertListRoute(ListRoute* listRoute, Route* route){
    if(listRoute->topo == MAX) // Verifica se a lista está cheia
        return 0;
    listRoute->route[listRoute->topo] = *route; // atribui a rota na lista
    listRoute->endSize += listRoute->route[listRoute->topo].theSize; // soma a distancia na distancia total
    listRoute->topo++;
    return 1;
}
//Insere uma cidade na rota
int insertRouteCity(Route* route, City* city, unsigned int distance){
    if(route->topo==100) // verifica se a lista está cheia ou se a cidade já está inserida na rota
        return 0;
    route->cities[route->topo] = *city; // atribui a cidade na rota
    route->endDemand += route->cities[route->topo].requirements; // faz o somarotio da demanda da cidade
    route->cities[route->topo].met_requirements = 1; // atribui a cidade como visitada;
    route->theSize += distance; // faz o somatorio da distancia da rota;
    route->topo++;
    return 1;
}

