#ifndef GENERATOR_H
#define GENERATOR_H
#include "path.h"
#include "truck.h"
#include "city.h"
#include "citystack.h"

typedef struct{
	Truck *trucks;
	City *cities;
	unsigned int number_of_cities;
	unsigned int **distances;
	int **permutations;
}Generator;
int** generatePermutation(unsigned int number_of_cities);

#endif
