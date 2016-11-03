#include <stdio.h>
#include <stdlib.h>

#include "generator.h"


void initGenerator(TGenerator* generator, unsigned int num_city){
    unsigned int i, j, possibility;

    generator->num_city = num_city;
    generator->num_truck = 1;
    generator->aux = 0;
    for(i=0;i<generator->num_city;i++){
        for(j=0;j<generator->num_city;j++){
            if(i<j)
                generator->array_distances[i][j] = rand()%100+1;
            else if(i>j)
                generator->array_distances[i][j] = generator->array_distances[j][i];
            else // if (i==j)
                generator->array_distances[i][j] = 0;
        }
    }
    possibility = Fatorial(num_city);
    generator->array_combinations = (int**)malloc(possibility*sizeof(int*));
       generateCombination(generator, num_city, 0);
}

int generateCapacity(TGenerator* generator, TListCity* listCity, unsigned int condition){
    unsigned int i = 2,  sumDemand, capacity_Truck, maximum=0, last;
    sumDemand = listCity->sumDemand;
    if(condition==0){
         while(1){
            if(sumDemand%i == 0){
                if(maximum > (sumDemand/i)){
                    if(i==2)
                        capacity_Truck = sumDemand;
                    else
                        capacity_Truck = sumDemand/last;
                    break;
                }else {
                    last = i;
                }
            }else {
                i++;
            }
        }
    }else{
        i = condition;
        while(1){
            if(sumDemand%i == 0){
                capacity_Truck = sumDemand/i;
                break;
            }else{
                i--;
            }
        }
    }
    i++;
    generator->num_truck = i;
    return capacity_Truck;
}

void generateCombination(TGenerator* generator, unsigned int N, unsigned int k) {
    static level = -1;
    level = level+1; generator->vectorAux[k] = level;
    int i;

    if (level == N){
             for (i = 0; i < N; i++) {
                generator->array_combinations[generator->aux] = (int*)malloc((N)*sizeof(int));
                for (i = 0; i < N; i++) {
                    generator->array_combinations[generator->aux][(i)] = generator->vectorAux[i];
                    //generator->array_combinations[generator->aux][(2*i)] = -1;
                }
            }
            //generator->array_combinations[generator->aux][0] = 0;
            //generator->array_combinations[generator->aux][2*i] = -2;
            generator->aux++;
    }else{
        for (i = 0; i <N; i++){
            if (generator->vectorAux[i] == 0){
                generateCombination(generator, N, i);
            }
        }
    }
    level = level-1; generator->vectorAux[k] = 0;
}

unsigned long int Fatorial(unsigned long int n){
    if(n==0 || n==1)
    return 1;
    return n*Fatorial(n-1);
}


int generateRoute(TGenerator* generator, TListTruck* listTruck, TListCity* listCity, TListRoute* listaRoute){
    TRoute rota;
    unsigned int i,j, capacity_truck, demand_city, ID_city, visited_city;




}
