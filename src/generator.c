#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

//Iniciar GERADOR
//IDEIA: GERAR AO INICAR O GERADOR AS CIDADES, A LISTA DE CIADAES, A MATRIZ DE DISTANCIAS
// A MATRIZ DE COMBINAÇÕES // GERAR O NUMERO DE CAMINHÕES
// E JÁ GERAR A MELHOR ROTA DE TAL FORMA QUE O NUM DE CAMINHÕES SEJA

void initGenerator(TGenerator* generator, TListCity* listCity, TListRoute* listRoute, TListTruck* listTruck, unsigned int num_city){
    unsigned int i, j, possibility;
    TCity cidade;

    generator->num_city = num_city;
    generator->num_truck = 1;
    generator->capacity_truck =0;
    generator->aux = 0;
    generator->aux2 = 0;

    for(i=0;i<generator->num_city;i++){
        initCity(&cidade, i);
        printf("demanda: %d ", cidade.demand);
        printf("\n");
        insertListCity(listCity, &cidade);
        printf("somatorio: %d \n", listCity->sumDemand);
        printf("maior: %d \n", listCity->greater_Demand);
        printf("quantidade: %d \n", listCity->topo);
    }

    for(i=0;i<generator->num_city+1;i++){
        for(j=0;j<generator->num_city+1;j++){
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
    //for(i=3;i<=num_city;i++){
        generateCombination(1, generator, num_city);
    //}

}

//GERADOR DE CAPACIDADE CO DAMINHÃO
int generateCapacity(TGenerator* generator, TListCity* listCity, unsigned int condition){
//CONDITION É PADRÃO COMO ZERO
    int i = 1,  sumDemand, capacity_Truck, maximum, lastDivisor;
    sumDemand = listCity->sumDemand; //ṕega o somatório da demanda de todas as cidades.
    maximum = listCity->greater_Demand; // Pega a maior demanda de uma punica ciadade.
    if(condition==0){
         while(1){ // sempre executado
            if(sumDemand%i == 0){ // se o somatorio é divisível por i então
                if(maximum > (sumDemand/i)){ // se a divisão desse somatório é menor que a maior demanda então
                    if(i==2){// se forem dois caminhões
                        capacity_Truck = sumDemand;
                    } // a capacidade do caminhão gerará um unico caminhão de capacidade máxima
                    else{
                        capacity_Truck = sumDemand/lastDivisor;
                    }
                        // caso contrário a capacidade do caminhão receberá
                        // o ultimo divisor de i cuja o maximum era menor que a demanda dividida por i
                    break; // interrompe o loop;
                }else {
                    lastDivisor = i;
                    i++;// caso a maior demanda não seja maior que a demanda dividida por i, esse i é guardado
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

    generator->num_truck = sumDemand/capacity_Truck;
    generator->capacity_truck = capacity_Truck;
    //VERIFICAR O RETORNO DO I.
    //generator->capacity_truck = capacity_Truck;
    return generator->num_truck; // Retorna a quantidade de caminhões
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


int mover(TGenerator* generator, int last ){
    //Last é usado para dize quantos caminhões serão. Ex, last = 2 quer dizer que deve haver 3 zeros 010230
    // Mas last depende de um vetor nessa primeira implmentação, ou seja executa a sua primeira versão com 1
    // e guarda a matriz, executa a sua segunda função com 2 caminhões e gusrda a sua matriz
    // executa a sua função com a matriz guardada na ultima excução e gera uma nova matriz.
    int i,j,l,  aux, cont=0, position=0, condition=0;
        if(last == 1){//Primeira Execução
            for(l=0;l<generator->aux;l++){
                for(i=0;i<=generator->num_city+3;i++){
                    if(i<2)
                        generator->vectorAux[i] = generator->array_combinations[l][i]; //copia o vetor passado normalmente no vertor auxilixar
                     else if(i==2)
                         generator->vectorAux[i] = 0; // insere 0 na terceira posição
                     else
                        generator->vectorAux[i] = generator->array_combinations[l][i-1]; // na quarta posição em diante recebe o vetor passado -1, pois ele está descolado
                        // uma função a menos que o auxiliar por ter recebido o zero
                 }
                for(i=1;i<=generator->num_city-1;i++){ // CONTANTE 9 A SER DEFINIDA
                    if(generator->vectorAux[i+1]!=0){
                        // verifica se o proximo numero não é zero, ou seja não está no final.
                        // caso não ele inverte os números de posição andado com o zero.
                        aux = generator->vectorAux[i];
                        generator->vectorAux[i] = generator->vectorAux[i+1];
                        generator->vectorAux[i+1] = aux;
                    }
                    for(j=0;j<=generator->num_city+(last+4);j++){
                        generator->arrayAux1[generator->aux2][j] = generator->vectorAux[j];
                    }
                    generator->aux2++;
                }
            }
        }else{
         for(l=0;l<generator->aux;l++){
                for(i=0;i<=generator->num_city+last+2;i++){
                    if(i<2)
                        generator->vectorAux[i] = generator->array_combinations[l][i]; //copia o vetor passado normalmente no vertor auxilixar
                     else if(i==2)
                         generator->vectorAux[i] = 0; // insere 0 na terceira posição
                     else
                        generator->vectorAux[i] = generator->array_combinations[l][i-1]; // na quarta posição em diante recebe o vetor passado -1, pois ele está descolado
                        // uma função a menos que o auxiliar por ter recebido o zero
                 }
                for(i=1;i<=generator->num_city-1;i++){ // CONTANTE 9 A SER DEFINIDA
                    if(generator->vectorAux[i+1]!=0){
                        // verifica se o proximo numero não é zero, ou seja não está no final.
                        // caso não ele inverte os números de posição andado com o zero.
                        aux = generator->vectorAux[i];
                        generator->vectorAux[i] = generator->vectorAux[i+1];
                        generator->vectorAux[i+1] = aux;
                    }
                    for(j=0;j<=generator->num_city+(last+4);j++){
                        generator->arrayAux1[generator->aux2][j] = generator->vectorAux[j];
                    }
                    generator->aux2++;
                }
            }
    }

    //free(generator->array_combinations);
    //generator->array_combinations = (int**)malloc(generator->aux2*sizeof(int*));
    //generator->aux=0;
    for(i=0;i<generator->aux;i++){
        //generator->array_combinations[i] = (int*)malloc((generator->num_city+(last+1))*sizeof(int));
        for(j=0;j<30;j++){
             generator->array_combinations[i][j] = generator->arrayAux1[i][j];
        }
        //generator->aux++;
    }
    //generator->aux2=0;
    last++;
    return last;
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

int generateRoute(TGenerator* generator){
    int i, j;
	unsigned int last_city, current_city = generator->array_combinations[0][0], acumulator = 0, comparator = 0, melhor = 0;
	for (i = 1; i < generator->num_city + 3; i++){
		last_city = current_city;
		if(current_city != -2 && generator->array_combinations[0][i] != -2){
            current_city = generator->array_combinations[0][i];
            acumulator += generator->array_distances[last_city][current_city];
		}
	}
	comparator = acumulator;	//Atribui a comparator um valor inicial como se a primeira permutação fosse a melhor
	for (i = 1; i < Fatorial(generator->num_city); i++) {
		acumulator = 0;
		for (j = 1; j < generator->num_city + 2; j++) {
			last_city = generator->array_combinations[i][j-1];
            if(current_city != -2 && generator->array_combinations[i][j] != -2){
                current_city = generator->array_combinations[i][j];
                acumulator += generator->array_distances[last_city][current_city];
			}
		}
		if(acumulator < comparator){
			comparator = acumulator;
			melhor = i;
		}
	}

    return generator->array_combinations[melhor];
}
