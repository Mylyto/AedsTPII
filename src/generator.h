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
	unsigned int combinations[MAXX][MAX]; // matriz para guardar as combinações de ZEROS
	unsigned int distances[MAX][MAX]; // matriz prar armazenar as distâncias entre as cidades.
	int **permutations; // ponteiro de ponteiros para armazenar as permutações geradas, posteriormente as combinações.
}Generator;

void generateTrucks(Generator* g, CityStack* cs, int condition);
//CONDITION É PADRÃO COMO ZERO, caso CONDITIONS DIFERENTE DE ZERO INDICA QUE QUER UM MULTIPLO, TAL QUE DEVE SER MENOR QUE O NUMERO ANTERIOR
// OU SEJA, SE O ULTIMO MULTIPLO FOI 4 DEVE-SE PASSAR CONdITION 3 PARA RETORNAR O PRÓXIMO MULTIPLO, PODENDO SER 3 OU 2 OU 1.

void generateDistances(Generator* g);
//função q ira gerar a matriz de distancias

void generateCities(Generator* g, CityStack* cs);
//função q ira gerar as demandas das cidades

void initGenerator(Generator* g, unsigned int n); // inicializa o gerador
// parãmetros G- gerador N - numero de cidades

unsigned long int Fatorial(unsigned long int n); // calcula fatorial recursivo
//parãmetros N - numero de cidades

void generatePermutation(unsigned int nivel, Generator* g,unsigned int n); // gera permutações recursivas
// nivel - auxiliar da recursividade, g-onde tem a matriz de permutação e auxiliar, N- permutação de qto em qto

void generateCities(Generator* g, CityStack* cs); // gera cidades e demanda
// g-> gerador para armazenar as cidades no vetor  cs-> para colocá-las em uma lista

void generateCombinations(Generator* g, unsigned int last); // gera combinações com zeros
//g-> gerador, onde estãos as matrizes de permutação, combinação e o vetor auxiliar
//last-> é o numero de caminhões -1, usado para determinar qtos zeros deve haver
///LEMBRE-SE: laste deve começar com 0, depois 1, depois 2, depois 3... pois ele gera em cima do resultado gerado

int *generateRoute(Generator* g); // gera rotas e calcula a demanda e menor rota



#endif
