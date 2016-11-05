#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "city.h"
#include "truck.h"
#include "route.h"
#include "generator.h"

int main(){
    int num = 4, i, j, possibilty=0, qtd;
    int *vec;
    srand(time(NULL));
    TGenerator gerador;


    TListCity listaCidade;
    TListTruck listaCaminhao;
    TListRoute listaRota;

    initListCity(&listaCidade);


    initGenerator(&gerador, &listaCidade, &listaRota, &listaCaminhao, num);
    for(i=0;i<gerador.num_city+1;i++){
        for(j=0;j<gerador.num_city+1;j++){
            printf(" %d ", gerador.array_distances[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<gerador.aux;i++){
        for(j=0;j<num+(num*2);j++){
            printf(" %d ", gerador.array_combinations[i][j]);
            if(gerador.array_combinations[i][j] == -2)
                break;
        }
        printf("\n");
    }

printf("\nMELHOR ROTA");
    vec = generateRoute(&gerador);
    for(i=0;i<num+2;i++)
        printf(" %d ", vec[i]);
printf("\n");
printf("CAPACIDADE Q QUANTIDADE DE CAMINHÕES: ");

    qtd = generateCapacity(&gerador, &listaCidade, 0);
    printf("%d %d %d\n", qtd, gerador.capacity_truck, gerador.num_truck);
    qtd = generateCapacity(&gerador, &listaCidade, qtd-1);
    printf("%d %d %d\n", qtd, gerador.capacity_truck, gerador.num_truck);

    mover(&gerador, 1);
 printf("\n");

    for(i=0;i<gerador.aux2;i++){
        for(j=0;j<num+(num*2);j++){
            printf(" %d ", gerador.arrayAux1[i][j]);
            if(gerador.arrayAux1[i][j] == -2)
                break;
        }
        printf("\n");
    }

   mover(&gerador, 2);
    printf("SEGUNDA\n");
        for(i=0;i<gerador.aux;i++){
            for(j=0;j<num+(num*2);j++){
                printf(" %d ", gerador.array_combinations[i][j]);
                if(gerador.array_combinations[i][j] == -2)
                    break;
            }
            printf("\n");
        }
        printf("\n");

            for(i=0;i<gerador.aux2;i++){
        for(j=0;j<num+(num*2);j++){
            printf(" %d ", gerador.arrayAux1[i][j]);
            if(gerador.arrayAux1[i][j] == -2)
                break;
        }
        printf("\n");
    }



    return 0;
}
