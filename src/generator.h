#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "city.h"
#include "truck.h"
#include "route.h"

#define MAX 200

typedef struct{
    unsigned int num_city; //Quarda o numero total de cidadas
    unsigned int num_truck; // guarda o numero total de caminhões
    unsigned int aux;// contator 'universa', tipo um top para o arrai combinations
    unsigned int aux2;
    unsigned int vectorAux[100]; // Vetor auxiliar para contrar as permutações em generateCombinations
    unsigned int array_distances[100][100]; // Matriz para gerar e guerdar as distancias entre as cidades;
    unsigned int arrayAux1[1000][MAX];
    unsigned int arrayAux2[1000][MAX];
    unsigned int capacity_truck;
    unsigned int **array_combinations; // matriz para guardar todas as combinações possíveis.
//    unsigned int array_combinations[MAX][MAX] // Matriz usada na permutação de caminhões únicos
}TGenerator;

void initGenerator(TGenerator* generator, TListCity* listCity, TListRoute* listRoute, TListTruck* listTruck, unsigned int num_city);
int generateCapacity(TGenerator* generator, TListCity* listCity, unsigned int condition);
unsigned long int Fatorial(unsigned long int n);
void generateCombination(int nivel, TGenerator* generator, int K);
//void generateCombination(TGenerator* generator, unsigned int N, unsigned int k); // permutaço de caminhão unico
int generateRoute(TGenerator* generator);
int generateTruckRoute(TGenerator* generator, int last );

#endif // GENERATOR_H_INCLUDED
