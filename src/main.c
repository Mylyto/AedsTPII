#include <stdio.h>
#include <stdlib.h>

#include "city.h"
#include "truck.h"
#include "route.h"
#include "generator.h"

int main(){
    int num = 3, i, j, possibilty=0;

    TGenerator gerador;

    TCity cidade;
    TListCity listaCidade;
    TListTruck listaCaminhao;
    TListRoute listaRota;

    initListCity(&listaCidade);
    for(i=0;i<num;i++){
        initCity(&cidade, i);
        printf("demanda: %d ", cidade.demand);
        printf("\n");
        insertListCity(&listaCidade, &cidade);
        printf("somatorio: %d \n", listaCidade.sumDemand);
        printf("maior: %d \n", listaCidade.greater_Demand);
        printf("quantidade: %d \n", listaCidade.topo);
    }

    initGenerator(&gerador, num);
    for(i=0;i<gerador.num_city;i++){
        for(j=0;j<gerador.num_city;j++){
            printf(" %d ", gerador.array_distances[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<gerador.aux;i++){
        for(j=0;j<num+(num*2);j++){
          if(gerador.array_combinations[i][j] == -2)
                break;
            printf(" %d ", gerador.array_combinations[i][j]);
        }
        printf("\n");
    }


    generateRoute(&gerador, &listaCaminhao, &listaCidade, &listaRota);
    printf("--- %d ", listaRota.topo);
    return 0;
}
