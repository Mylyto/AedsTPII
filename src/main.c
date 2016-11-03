#include <stdio.h>
#include <stdlib.h>

#include "city.h"
#include "truck.h"
#include "route.h"
#include "generator.h"

int main(){
    TGenerator gerador;
    TCity cidade;
    TListCity listaCidade;
    TTruck caminhao;
    TListTruck listaCaminhao;
    TRoute rota;
    TListRoute listaRota;
    int num = 5, i, j, possibilty=0;
/*
    initListCity(&listaCidade);
    for(i=0;i<num;i++){
        initCity(&cidade, i);
        printf(" %d ", cidade.demand);
        printf(" %d ", cidade.ID);
        printf(" %d ", cidade.visitd);
        insertListCity(&listaCidade, &cidade);
    }
        printf("\n");
        printf(" %d ", listaCidade.greater_Demand);
        printf(" %d ", listaCidade.sumDemand);
        printf(" %d ", listaCidade.topo);
*/
    initGenerator(&gerador, num);
    for(i=0;i<gerador.num_city;i++){
        for(j=0;j<gerador.num_city;j++){
            printf(" %d ", gerador.array_distances[i][j]);
        }
        printf("\n");
    }

printf("\n");
    for(i=0;i<gerador.aux;i++){
        for(j=0;j<num;j++){
           if(gerador.array_combinations[i][j] == -2)
                break;
            printf(" %d ", gerador.array_combinations[i][j]);
        }
        printf("\n");
    }
    return 0;
}
