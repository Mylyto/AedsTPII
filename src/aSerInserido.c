#include <stdio.h>
#include <stdlib.h>

#define NMAX 101
//int a=0;

//Função que auxilia permuta informando tamanho da matriz
unsigned long int Fatorial(unsigned long int n){
    if(n==0 || n==1)
    return 1;
    return n*Fatorial(n-1);
}

int* encontraMelhorRota(Generator *gen){
	int i, j;
	unsigned int last_city, current_city = gen->permutations[0][0], acumulator = 0, comparator = 0, melhor = 0;
	for (i = 1; i < gen->number_of_cities; i++){
		last_city = current_city;
		current_city = gen->permutations[0][i];
		acumulator += gen->distances[last_city][current_city];

	}
	comparator = acumulator;	//Atribui a comparator um valor inicial como se a primeira permutação fosse a melhor
	for (i = 1; i < Fatorial(gen->number_of_cities); i++) {
		acumulator = 0;
		for (j = 1; j < gen->number_of_cities; j++) {
			last_city = gen->permutations[i][j-1];
			current_city = gen->permutations[i][j];
			acumulator += gen->distances[last_city][current_city];
		}
		if(acumulator < comparator){
			comparator = acumulator;
			melhor = i;
		}
	}
	return gen->permutations[melhor];
}
//Função que permuta as possibilidades
//Parametros:
//nivel: iteradora entre niveis de casas decimais usadas
//qtd_termos: x em P(n,x)
//num_city: n em P(n,x)
//vec_exit: matriz resultante
void permuta(int nivel, int * n, int qtd_termos, int num_city, int *** vec_exit, int *k) {
        int i, j, parada = 0, *vec_temp;//Variaveis iteradoras, sinal para parar,vetor temporario
        vec_temp = (int *)malloc((qtd_termos+1)*sizeof(int));//alocando espaço para cada linha da matriz tendo base no numero de casas decimais max (qtd_termos)
        if (nivel<=qtd_termos) {	//"Enquanto" iterador nivel estiver no intervalo 1<->qtd_termos
            for (i=1; i<=num_city; i++) {
                 n[nivel]=i;
                 permuta(nivel+1, n, qtd_termos, num_city, vec_exit, k);	//Recursão
            }
        } else {	//Quando Recursão chegar ao fim
             for (i=1; i<=qtd_termos; i++) {	//Conferir se há repetiçoes
                  for (j=1; j<=qtd_termos; j++) {
                       if((n[i]==n[j])&&(i != j)){
                            parada = 666;//Se tem repitido acionar parada
                            break;
                       }
                   }
                }//Fim de Conferir repetiçoes
                if(parada != 666){	//Se não houve repetiçoes
                     for (i=1; i<=qtd_termos; i++) {
                            vec_temp[i] =  n[i];
                     }
                     vec_temp[0] = 0;//???
                     vec_temp[i] = 0;
                     vec_temp[i+1] = 666;
                     (*vec_exit)[*k] = (int *)malloc((qtd_termos + 1)*sizeof(int)); //
                     for(j = 0; j <= i+1; j++){
                        (*vec_exit)[*k][j] = vec_temp[j];
                     }
                     (*k)++;
                }
        }
}
void geradorDistancias(int num_city, int *** vec_distancias){
    int i, j;
    for(i=0;i<num_city;i++){
        (*vec_distancias)[i] = (int*)malloc(num_city*sizeof(int));
        for(j=0;j<num_city;j++){
            if(i==j)
                (*vec_distancias)[i][j] = 0;
            else
                (*vec_distancias)[i][j] = rand()%100+1;
        }
    }
        for(i=0;i<num_city;i++){
            for(j=0;j<num_city;j++){
               if (((*vec_distancias)[i][j]) != ((*vec_distancias)[j][i]))
                    (*vec_distancias)[j][i] = (*vec_distancias)[i][j];
            }
        }


}

int demanda( int * vec_city, int num_city){
    int i, maior = 0, demandaFinal=0 ;
    for(i=0;i<num_city;i++){
        vec_city[i] = rand()%1000+1;
        demandaFinal += vec_city[i];
        if(maior < vec_city[i]){
            maior = vec_city[i];
        }
    }
    vec_city[i] = demandaFinal;	//Pq dar valor para um container q sera apagado agora?
    return maior;
}

int trucks(int * vec_trucks, int num_city, int * vec_city, int maior,int repetir){
    int i = 2,j, capacity_truck, demandaFinal;
    demandaFinal = vec_city[num_city];
    if(repetir==0){
        while(1){
            if(demandaFinal%i == 0){
                if(maior > (demandaFinal/i) ){
                    if(i==2)
                        capacity_truck = demandaFinal;
                    else
                        capacity_truck = demandaFinal/(i-1);
                    break;
                }else{
                    i++;
                }
            }
        }
    } else {
        i = repetir;
        while(1){
            if(demandaFinal%i == 0){
                capacity_truck = demandaFinal/i;
                break;
            }else{
                i--;
            }
        }
        i++;
    }

    for(j=0;j<=i;j++)
        vec_trucks[j] = capacity_truck;
    return i-1;
}

int main(void) {
        int i, j, k = 0, qtd_termos = 2, C = 0;
        int num_city = 4;
        int n[NMAX];
        int **vec_exit;
        int **vec_distancias;
        int *vec_city;
        int maior;
        int *vec_trucks;
	
	//Chama Permuta
       for(i = 1; i<=qtd_termos; i++){
            C = C + Fatorial(num_city)/Fatorial(num_city-i);
       }
        vec_exit = (int**)malloc(C*sizeof(int));
        for (i=1; i<=qtd_termos; i++) {
                n[i]=-1;
        }
        for(i = 1; i<=qtd_termos; i++){
            permuta(1, n, i, num_city, &vec_exit, &k);
        }
        for(i = 0; i<C; i++){
            for(j=0; j < C; j++){
            if(vec_exit[i][j] == 666)
                    break;
                printf(" %d " , vec_exit[i][j]);
            }
            printf("\n");
        }
        printf("----%d\n", C);


	//GeradorDistancia
        vec_distancias = (int**)malloc(num_city*sizeof(int));
        geradorDistancias(num_city, &vec_distancias);
        for(i=0; i<num_city; i++){
            for(j=0; j<num_city; j++){
                printf(" %d " , vec_distancias[i][j]);
            }
            printf("\n");
        }

        printf("\n");
	//demanda
        vec_city = (int*)malloc(num_city*sizeof(int));
        maior = demanda(vec_city, num_city);
        for(i=0;i<=num_city;i++){
            printf(" %d ", vec_city[i] );
        }
        printf("\n ---%d \n", maior);

        printf("\n");
	//trucks
        vec_trucks = (int*)malloc(num_city*sizeof(int) + sizeof(int));
        trucks(vec_trucks, num_city, vec_city, maior, 0);


}



