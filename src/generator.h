#ifndef GENERATOR_H
#define GENERATOR_H
#include "path.h"
#include "truck.h"
#include "city.h"
#include "citystack.h"
#define MAX 100
#define MAXX 1000
typedef struct{
	Truck *trucks;
	City *cities;
	unsigned int number_of_permutations;
	unsigned int number_of_cities;
	unsigned int number_of_combinations;
	unsigned int number_of_trucks;
	unsigned int truck_capacity;
	unsigned int vector_Aux[MAX];
	unsigned int array_Combinations[MAXX][MAX];
	unsigned int distances[MAX][MAX];
	int **permutations;
}Generator;


void initGenerator(Generator* g, unsigned int n);

//unsigned int generateCapacity(TGenerator* g, TListCity* listCity, unsigned int condition);
//unsigned long int Fatorial(unsigned long int n);
//void generateCombination(int nivel, TGenerator* generator, int K);
//void generateCombination(TGenerator* generator, unsigned int N, unsigned int k); // permutaço de caminhão unico
//unsigned int generateRoute(TGenerator* generator);
//unsigned int generateTruckRoute(TGenerator* generator, int last );

unsigned long int Fatorial(unsigned long int n);
int generatePermutation(int nivel, Generator* g, int n);
void generateCities(Generator* g, CityStack* cs);
void generateCombinations(Generator* g, int last);
int generateRoute(Generator* g, CityStack* cs);



#endif
