#ifndef GENERATOR_H
#define GENERATOR_H
#include "city.h"
#include "citystack.h"
#define MAX 100
#define MAXX 10000
typedef struct{
	City *cities;
	unsigned int number_of_permutations; // contator de quantos linhas tem a permutação
	unsigned int number_of_cities;
	unsigned int number_of_combinations; // contador de quantas linhas tem a matriz de combinações
	unsigned int number_of_trucks;
	unsigned int truck_capacity;
	unsigned int vector_Aux[MAX]; // vetor 'universal' para usar em recursões etc.
	unsigned int distances[MAX][MAX]; // matriz prar armazenar as distâncias entre as cidades.
	int **permutations; // ponteiro de ponteiros para armazenar as permutações geradas, posteriormente as combinações.
	int combinations[MAXX][MAX]; // matriz para guardar as combinações de ZEROS
}Generator;

int generateTrucks(Generator* g, CityStack* cs);
void generateDistances(Generator* g);
void generateCities(Generator* g, CityStack* cs);
int initGenerator(Generator* g, unsigned int n); // inicializa o gerador
unsigned long int Fatorial(unsigned long int n); // calcula fatorial recursivo
void generatePermutation(unsigned int nivel, Generator* g, unsigned int n); // gera permutações recursivas
void generateCombinations(Generator* g, unsigned int last); // gera combinações com zeros
int generateRoute(Generator* g, int **bestRoute); // gera rotas e calcula a demanda e menor rota
#endif
