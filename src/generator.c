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
    for(i=1;i<=num_city;i++){
        generateCombination(1, generator, i);
    }

}

//GERADOR DE CAPACIDADE CO DAMINHÃO
int generateCapacity(TGenerator* generator, TListCity* listCity, unsigned int condition){
//CONDITION É PADÃO COMO ZERO
    unsigned int i = 2,  sumDemand, capacity_Truck, maximum, last;
    sumDemand = listCity->sumDemand; //ṕega o somatório da demanda de todas as cidades.
    maximum = listCity->greater_Demand; // Pega a maior demanda de uma punica ciadade.
    if(condition==0){
         while(1){ // sempre executado
            if(sumDemand%i == 0){ // se o somatorio é divisível por i então
                if(maximum > (sumDemand/i)){ // se a divisão desse somatório é menor que a maior demanda então
                    if(i==2) // se forem dois caminhões
                        capacity_Truck = sumDemand; // a capacidade do caminhão gerará um unico caminhão de capacidade máxima
                    else
                        // caso contrário a capacidade do caminhão receberá
                        // o ultimo divisor de i cuja o maximum era menor que a demanda dividida por i
                        capacity_Truck = sumDemand/last;
                    break; // interrompe o loop;
                }else {
                    last = i; // caso a maior demanda não seja maior que a demanda dividida por i, esse i é guardado
                    // e o while continua a rodar;
                }
            }else {
                i++;
            }
        }
    }else{
    // caso o condition seja diferente de ZERO, ou seja recebe o valor de UMA unidade a menos
    // de caminhões que foi insificiente para fazer a rota para gerar um multiplo maior que o menor multiplo possível
        i = condition;
        while(1){
            if(sumDemand%i == 0){ // se i é divisível,
                capacity_Truck = sumDemand/i;
                break;
            }else{ // caso contrário continua no loop a procura do mair multiplo acima do menor multiplo possível
                i--;
            }
        }
    }
    generator->num_truck = i; // o numero de caminhões é guardada no gerador
    return capacity_Truck; // Retorna a capacidade de caminhões
}


//GERA TODAS AS COMBINAÇÕES
void generateCombination(int nivel, TGenerator* generator, int K){
// nivel, da recursão e K é permutar de quantas casas ex: 3 cidade de K=1 seria [1] [2] [3];
    int i, j, parada = 0, *vec_temp; // Vetor temporário para auxiliar a bagunça;
    vec_temp = (int*)malloc((K*2)*sizeof(int)); //Aloca dinâmicamente para usar o vetor auxiliar.
    if (nivel<=K) {
        for (i=1; i<=generator->num_city; i++) {
             generator->vectorAux[nivel]=i; // Usa a recursão para gerar numeros para o vetor auxiliar
             generateCombination(nivel+1, generator, K);
        }
    } else {
         for (i=1; i<=K; i++) {
              for (j=1; j<=K; j++) {
                   if((generator->vectorAux[i]==generator->vectorAux[j])&&(i != j)){
                        //estuda e remove permutações de casa repetidas
                        parada = 8;
                        break;
                   }
               }
            }
            if(parada != 8){ // se não houver numeros repetidos no vetor
                 for (i=1; i<=K; i++) {
                        vec_temp[i] =  generator->vectorAux[i]; // o vetor temporario recebe os numeros gerados na recursao
                 }
                 vec_temp[0] = 0; // Primeira posição recebe 0 por padrão;
                 vec_temp[i] = 0; // como se fosse [01230] começa e termina
                 vec_temp[i+1] = -2; // critério de parada;
                 //Aloca o vetor de vetores da matriz de combinações
                 generator->array_combinations[generator->aux] = (int *)malloc((K*3)*sizeof(int));
                 for(j = 0; j <= i+1; j++){ // A martiz de combinações recebe todos os numeros gerados na recursão
                    generator->array_combinations[generator->aux][j] = vec_temp[j];
                 }
                 free(vec_temp); // Desaloca o vetor temporario;
                 generator->aux++; // incrementa o contador 'universal'
            }
        }
}


/*void generateCombination(TGenerator* generator, unsigned int N, unsigned int k) {
    static level = -1;
    level = level+1; generator->vectorAux[k] = level;
    int i;

    if (level == N){
             for (i = 0; i < N; i++) {
                generator->array_combinations[generator->aux] = (int*)malloc((N)*sizeof(int));
                for (i = 0; i < N; i++) {
                    generator->array_combinations[generator->aux][i] = generator->vectorAux[i];
                   // generator->array_combinations[generator->aux][(2*i)] = -1;
                }
                generator->array_combinations[generator->aux][i] = -2;
            }
            //generator->array_combinations[generator->aux][0] = 0;
            //generator->array_combinations[generator->aux][2*i] = 0;
            //generator->array_combinations[generator->aux][(2*i)+1] = -2;
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
*/

//FATORIAL USADO PARA CALCULAR O TAMANHO DA ALOCAÇÃO DE DEVE SER FEITA NA MATRIZ DE COMBINAÇÕES
unsigned long int Fatorial(unsigned long int n){
    if(n==0 || n==1)
    return 1;
    return n*Fatorial(n-1);
}

int generateRoute(TGenerator* generator, TListTruck* listTruck, TListCity* listCity, TListRoute* listaRota){
   // TRoute rota;
    //unsigned int distancia=0, topTruck = listTruck->topo, topCity = listCity->topo, i=0; //topRoute = listaRota->topo;
    //initRoute(&rota, generator->num_city);
    //while(topCity>=0){
     //   if(topCity==0){
       //     insertCityRoute(&rota, &listCity->city[topCity], 10 );//rota.cities[i] = listCity->city[topCity];
         //   break;
        //}
        //insertCityRoute(&rota, &listCity->city[topCity], 10 );
        //rota.cities[i] = listCity->city[topCity];
        //i++;
        //topCity--;
   // }
    //insertRouteList(&listaRota,&rota);
   // listaRota->route[listaRota->topo] = rota;

    return 0;
}
