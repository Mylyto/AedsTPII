#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "generator.h"

int main(){
	City c;
	CityStack cs;
	Generator g;
	clock_t Ticks[2];//VARIAVEL PARA LEITURA DE HORAS (time.h)
	unsigned int N = 6, condition=1 , i, j;
	int *bestRoute;
	double tempo;

	srand(time(NULL));
	//initCityStack(&cs);

	//ABRINDO ARQUIVOS
	FILE *openArq;	
	FILE *exitArq;
	if((openArq = fopen("entrada.txt","r")) == NULL || (exitArq = fopen("saida.txt", "w")) == NULL){
		printf("Ocorreu erro com o(s) arquivo(s)");
    	}
	condition = initGenerator(&g, N);
	if(condition){
        	while(condition){
        		generateCities(&g,&cs);
        		condition = generateTrucks(&g, &cs);
        	}
        	generateDistances(&g);
    	}
	printf(" %d ", g.number_of_trucks);
	for(i=0;i<g.number_of_trucks;i++){
        	generateCombinations(&g,i);
	}
    	for(i=0;i<g.number_of_combinations;i++){
        	for(j=0;j<g.number_of_cities+g.number_of_trucks+2;j++){
            		printf(" %d ", g.permutations[i][j]);
		}
        	printf("\n");
    	}


    	generateRoute(&g,&bestRoute);
    	//EXIBE A MELHOR ROTA.
	for(i=0;i<=g.number_of_cities+(3+g.number_of_trucks);i++){
		if(bestRoute[i]==-2){
		    break;
		}else if (i==0){
		    printf("[");
		   printf(" %d ", bestRoute[i]);
		}else if (bestRoute[i]==0 && bestRoute[i+1]!=-2){
		    printf(" %d ", bestRoute[i]);
		    printf("][");
		    printf(" %d ", bestRoute[i]);
		}else if(bestRoute[i]==0){
		    printf(" %d ", bestRoute[i]);
		    printf("]");
		}else{
		    printf(" %d ", bestRoute[i]);
		}

	}
    	fclose(openArq);
    	fclose(exitArq);
    	return 0;
}
