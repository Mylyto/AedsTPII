#ifndef ROUTE_H_INCLUDED
#define ROUTE_H_INCLUDED

#include "city.h"
#define MAX 200

//A rota possui um vetor de cidades pela a qual ela percorre
typedef struct{
    City cities[MAX];
    unsigned int endDemand; // demanda total da rota
    unsigned int topo; // num de cidades na rota
    unsigned int theSize; // o tamanho da rota
}Route;

// Lista de rotas
// IDEIA: 4 cidades e 2 caminhoẽs, uma rota seria 010, outra 02340.
// Loga essa lista de rotas seria guardada na lista. e cria outra lista para as rotas 0120 0340
typedef struct{
    Route route[MAX];
    unsigned int endSize; // tamanho total de toda a rota
    unsigned int topo; // numero de rotas;
}ListRoute;


void initRoute(Route* route, unsigned int num_city);
void initListRoute(ListRoute* listRoute);
int insertListRoute(ListRoute* listRoute, Route* route);
int insertRouteCity(Route* route, City* city, unsigned int distance);

#endif // ROUTE_H_INCLUDED
