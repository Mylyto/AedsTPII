#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "city.h"
#include "truck.h"
#include "route.h"

#define MAX 1000

typedef struct{
    unsigned int num_city;
    unsigned int num_truck;
    unsigned int aux;
    unsigned int vectorAux[MAX];
    unsigned int array_distances[MAX][MAX];
    unsigned int **array_combinations;
}TGenerator;

void initGenerator(TGenerator* generator, unsigned int num_city);
int generateCapacity(TGenerator* generator, TListCity* listCity, unsigned int condition);
unsigned long int Fatorial(unsigned long int n);
void generateCombination(TGenerator* generator, unsigned int N, unsigned int k);
int generateRoute(TGenerator* generator, TListTruck* listTruck, TListCity* listCity, TListRoute* listRoute);

#endif // GENERATOR_H_INCLUDED
