#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "generator.h"

int main(){
    City c;
    CityStack cs;
    Generator g;
    clock_t Ticks[2];//VARIAVEL PARA LEITURA DE HORAS (time.h)
    int condition, i, j = 0, temp, n;
    int *bestRoute;
    double tempo;

    srand(time(NULL));

    //ABRINDO ARQUIVOS
	FILE *exitArq;
	if((exitArq = fopen("saida.txt", "w")) == NULL){
		printf("Ocorreu erro com o arquivo(s)");
    }
        scanf("%d", &n);
           condition = initGenerator(&g, n);
            if(condition){
                while(condition){
                    generateCities(&g,&cs);
                    condition = generateTrucks(&g, &cs);
                }
                generatePermutation(1,&g,n);
                for(i=0;i<g.number_of_trucks;i++)
                    generateCombinations(&g,i);
                for(i=0;i<g.number_of_combinations;i++){
                    for(j=0;j<g.number_of_cities+g.number_of_trucks+2;j++)
                        printf(" %d ", g.permutations[i][j]);
                    printf("\n");
            }

            /*//generateRoute(&g,&bestRoute);
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

           }*/
            Ticks[1] = clock();
            tempo = ((Ticks[1] - Ticks[0])*1000.0/ CLOCKS_PER_SEC) / 1000;
            fprintf(exitArq, "Numeros de cidades: %d tempo: %.3f\n", n, tempo);
            }


    fclose(exitArq);
    return 0;

}
