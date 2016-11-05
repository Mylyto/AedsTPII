#include <stdio.h>
#include <stdlib.h>

#include "generator.h"

//Iniciar GERADOR
//IDEIA: GERAR AO INICAR O GERADOR AS CIDADES, A LISTA DE CIADAES, A MATRIZ DE DISTANCIAS
// A MATRIZ DE COMBINAÇÕES // GERAR O NUMERO DE CAMINHÕES
// E JÁ GERAR A MELHOR ROTA DE TAL FORMA QUE O NUM DE CAMINHÕES SEJA

void initGenerator(Generator* g, unsigned int n){
    int i,j,possibility;
    int *bestRoute;
    CityStack cs;
    n-=1;
    g->number_of_cities = n;
    g->number_of_combinations = 0;
    g->number_of_permutations = 0;
    g->truck_capacity = 0;
    generateCities(g, &cs);//Gerando as cidades e q=guardando-as na na Stack e no gerador
    generateDistances(g);//Gerando a Matriz de distancias
    for(i=0;i<=n;i++)
        possibility += Fatorial(n)/Fatorial(n-i);//Calculando as possibilidades máximas de alocação de memória
    g->permutations = (int**)malloc(possibility*sizeof(int*));//Alocando memória suficiente para a matiz de permutações
    generatePermutation(1, g, n);//gerando recursivamente as permutações recursivamente.
    generateTrucks(g,&cs,0); // gera a capacidade do caminhão e a quatidade de caminhões
   // for(i=1; i<=3;i++)
    generateCombinations(g,g->number_of_trucks-1); // GERA COMBINAÇÕES COM ZEROS
    bestRoute=generateRoute(g, possibility, &cs); // ESCOLHE A MELHOR ROTA

    //EXIBRE A MELHOR ROTA.
    for(i=0;i<=g->number_of_cities+(3+g->number_of_trucks);i++){
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

}

//GERA TODAS AS PERMUTAÇÕES
int generatePermutation(int nivel, Generator* g, int n){
// nivel, da recursão e K é permutar de quantas casas ex: 3 cidade de K=1 seria [1] [2] [3];
    int i, j, parada = 0, *vec_temp; // Vetor temporário para auxiliar a bagunça;
    vec_temp = (int*)malloc((n*2)*sizeof(int)); //Aloca dinâmicamente para usar o vetor auxiliar.
    if (nivel<=n) {
        for (i=1; i<=g->number_of_cities; i++) {
             g->vector_Aux[nivel]=i; // Usa a recursão para gerar numeros para o vetor auxiliar
             generatePermutation(nivel+1, g, n);
        }
    } else {
         for (i=1; i<=n; i++) {
              for (j=1; j<=n; j++) {
                   if((g->vector_Aux[i]==g->vector_Aux[j])&&(i != j)){
                        //estuda e remove permutações de casa repetidas
                        parada = 8;
                        break;
                   }
               }
            }
            if(parada != 8){ // se não houver numeros repetidos no vetor
                 for (i=1; i<=n; i++) {
                        vec_temp[i] =  g->vector_Aux[i]; // o vetor temporario recebe os numeros gerados na recursao
                 }
                 vec_temp[0] = 0; // Primeira posição recebe 0 por padrão;
                 vec_temp[i] = 0; // como se fosse [01230] começa e termina
                 vec_temp[i+1] = -2; // critério de parada;
                 //Aloca o vetor de vetores da matriz de combinações
                 g->permutations[g->number_of_permutations] = (int *)malloc((n*3)*sizeof(int));
                 for(j = 0; j <= i+1; j++){ // A martiz de combinações recebe todos os numeros gerados na recursão
                    g->permutations[g->number_of_permutations][j] = vec_temp[j];
                    printf(" %d ", g->permutations[g->number_of_permutations][j]);
                 }
                 free(vec_temp); // Desaloca o vetor temporario;
                 g->number_of_permutations++; // incrementa o contador 'universal'
                 printf("\n");
            }
        }
}

void generateCities(Generator* g, CityStack* cs){
    City c;
    int i;
    initCityStack(cs); // inicializa a pilha de cidades
    g->cities = (City*)malloc(g->number_of_cities*sizeof(City)); // aloca o vetor de cidades
    for(i=0;i<g->number_of_cities;i++){
        initCity(&c); // inicializa a cidade
        push(cs, c); // insere a cidade na pilha
    }
    for(i=0;i<g->number_of_cities;i++){
        g->cities[i] = cs->cities[i]; // atiribui o vetor cidade ao vetor no tad generator
        printf("\nDemanda: %d ID: %d meet: %d\n" ,g->cities[i].requirements, g->cities[i].id, g->cities[i].met_requirements );
    }

}

//CRIA A MATRIZ DE DISTÂNCIAS
void generateDistances(Generator* g){
    int i, j;
    //gerar Distancias espelhadas
    for(i=0;i<=g->number_of_cities;i++){
        for(j=0;j<=g->number_of_cities;j++){
            if(i<j)
                g->distances[i][j] = rand()%100+1;
            else if(i>j)
                g->distances[i][j] = g->distances[j][i];
            else // if (i==j)
                g->distances[i][j] = 0;
        }
    }
    for(i=0;i<=g->number_of_cities;i++){
        for(j=0;j<=g->number_of_cities;j++){
               printf(" %d " , g->distances[i][j]);
        }
        printf("\n");
    }

}

//GERADOR DE CAPACIDADE CO DAMINHÃO
void generateTrucks(Generator* g, CityStack* cs, int condition){
//CONDITION É PADRÃO COMO ZERO
    int i = 1,  sumDemand, capacity_Truck, maximum, lastDivisor;
    sumDemand = cs->endRequirements; //ṕega o somatório da demanda de todas as cidades.
    maximum = cs->greater_Requirements; // Pega a maior demanda de uma punica ciadade.
    if(condition==0){
         while(1){ // sempre executado
            if(sumDemand%i == 0){ // se o somatorio é divisível por i então
                if(maximum > (sumDemand/i)){ // se a divisão desse somatório é menor que a maior demanda então
                    if(i==2)// se forem dois caminhões
                        capacity_Truck = sumDemand; // a capacidade do caminhão gerará um unico caminhão de capacidade máxima
                    else
                        capacity_Truck = sumDemand/lastDivisor;// caso contrário a capacidade do caminhão receberá
                        // o ultimo divisor de i cuja o maximum era menor que a demanda dividida por i
                    break; // interrompe o loop;
                }else{
                    lastDivisor = i;
                    i++;// caso a maior demanda não seja maior que a demanda dividida por i, esse i é guardado
                    // e o while continua a rodar;
                }
            }else{
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
    g->number_of_trucks = sumDemand/capacity_Truck; // numero de caminhão é dado pela disião
    g->truck_capacity = capacity_Truck;
    printf("\ntrucks: %d capacity: %d\n", g->number_of_trucks, g->truck_capacity);
}





void generateCombinations(Generator* g, int last){
    //Last é usado para dize quantos caminhões serão. Ex, last = 2 quer dizer que deve haver 3 zeros 010230
    // Mas last depende de um vetor nessa primeira implmentação, ou seja executa a sua primeira versão com 1
    // e guarda a matriz, executa a sua segunda função com 2 caminhões e gusrda a sua matriz
    // executa a sua função com a matriz guardada na ultima excução e gera uma nova matriz.
    int i,j,l,  aux, cont=0, position=0, condition=0;
    g->number_of_combinations = 0;
    g->number_of_combinations=0;
    if(last == 0){

    }else if(last == 1){//Primeira Execução
            for(l=0;l<g->number_of_permutations;l++){
                for(i=0;i<=g->number_of_cities+3;i++){
                    if(i<2)
                        g->vector_Aux[i] = g->permutations[l][i]; //copia o vetor passado normalmente no vertor auxilixar
                     else if(i==2)
                         g->vector_Aux[i] = 0; // insere 0 na terceira posição
                     else
                        g->vector_Aux[i] = g->permutations[l][i-1]; // na quarta posição em diante recebe o vetor passado -1, pois ele está descolado
                        // uma função a menos que o auxiliar por ter recebido o zero
                 }
                for(i=1;i<=g->number_of_cities-1;i++){
                    if(g->vector_Aux[i+1]!=0){
                        // verifica se o proximo numero não é zero, ou seja não está no final.
                        // caso não ele inverte os números de posição andado com o zero.
                        aux = g->vector_Aux[i];
                        g->vector_Aux[i] = g->vector_Aux[i+1];
                        g->vector_Aux[i+1] = aux;
                    }
                    for(j=0;j<=g->number_of_cities+(last+4);j++){
                        g->array_Combinations[g->number_of_combinations][j] = g->vector_Aux[j]; // atribui a linha do vetor na matriz combinação
                    }
                    g->number_of_combinations++; // incrementa o contador 'universal' do array
                }
            }
        for(i=0;i<g->number_of_permutations;i++){
            for(j=0;j<g->number_of_cities+last+3;j++){
                 g->permutations[i][j] = g->array_Combinations[i][j]; // atribui as combinações zeradas com os zeros na matriz permutação
                 printf(" %d ", g->permutations[i][j]);
            }
            printf("\n");
    }
        }else{

            // ERRO FUNÇÃO não funciona
            // IDEIA: Sabe-se que se há 2 caminhões deve haver 2 zeros antes do ultimo zero ex:
            // 012034560 ... tal que se usar o numero de caminhões para contar esses zeros sabemos onde mover
            // logo enquanto não encontrar o segundo zero a matriz se repete... 012...
            // Quando a enconta deve repetir o zero e a próxima posição. 01203, ou seja
            // na posição+2 depois do segundo zero encontrado deve ser inserido mais um zero
            // 012030 ... e apartir dai recebe normalmente o vetor uma posição descolada;
            // 0120304560.
            // Segunda ida, MOVER O ZERO INSERIDO// Deve-se guardar a posição do ultimo zero, para que
            // a movimentação do vetor so ocorra após o zero ser inserido
            // Ex. 0120304560 -> 0120340560 -> 0120345060 e break quando encontrar um zero final ou -2;
         for(l=0;l<g->number_of_permutations;l++){
                cont=0; position=0;
                for(i=0;i<=g->number_of_cities+last+2;i++){
                    if(g->permutations[l][i] == 0){
                        cont++;
                        position=i+2;
                    }
                    if(i<position && last >= cont)
                        g->vector_Aux[i] = g->permutations[l][i]; //copia o vetor passado normalmente no vertor auxilixar
                     else if(i==position)
                         g->vector_Aux[i] = 0; // insere 0 na terceira posição
                     else
                        g->vector_Aux[i] = g->permutations[l][i-1]; // na quarta posição em diante recebe o vetor passado -1, pois ele está descolado
                        // uma função a menos que o auxiliar por ter recebido o zero
                 }
                for(i=5;i<20;i++){
                        aux = g->vector_Aux[i];
                        g->vector_Aux[i] = g->vector_Aux[i+1];
                        g->vector_Aux[i+1] = aux;

                    for(j=0;j<=g->number_of_cities+(last+4);j++){
                        g->array_Combinations[g->number_of_combinations][j] = g->vector_Aux[j];
                    }
                    g->number_of_combinations++;
                }
            }
        for(i=0;i<g->number_of_permutations;i++){
            for(j=0;j<g->number_of_cities+last+3;j++){
                //Sabe-se que o vetor possui normlamente além da combinação mais 3 casas, tal que 123 ->
                // 01230-2 para dizer o final do vetor, logo a cada last, ou seja há uma insersão a mais de casa no vetor,
                 //logo 01230-2 -> 010230-2
                 g->permutations[i][j] = g->array_Combinations[i][j];
                 // Transfere as combinações para a matriz de permutações
                 // Sobre escrevendo as antigas permutações de 01234560 para 010234560
                 printf(" %d ", g->permutations[i][j]);
            }
            printf("\n");
        }
    }
}



/*void generateCombination(TGenerator* generator, unsigned int N, unsigned int k) {
    static level = -1;
    level = level+1; generator->vector_Aux[k] = level;
    int i;

    if (level == N){
             for (i = 0; i < N; i++) {
                generator->array_combinations[generator->aux] = (int*)malloc((N)*sizeof(int));
                for (i = 0; i < N; i++) {
                    generator->array_combinations[generator->aux][i] = generator->vector_Aux[i];
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

int generateRoute(Generator* g, unsigned int p, CityStack* cs){
    int i, j, k, r ,q , again;
	unsigned int last_city, current_city = g->permutations[0][0], acumulator = 0, comparator = 0, melhor = 0, capacity =0;

    //Guarda as demandas das cidades num vetor auxiliar tal que a demanda inical é 0.
    g->vector_Aux[i]=0;
    for(i=1;i<=g->number_of_cities;i++){
        g->vector_Aux[i] = g->cities[i-1].requirements;
    }

   //FUNÇÃO ERRO Ideia, execuata uma vez.
    do{
        // IDEIA: Diminuir uma permutação gerada a cada vez que sua demanda é insuficiente
        // Tal que, se todas as permutações forem impossíveis, gera-se novamente todas as permutações
        // e gera novente as combinações// tal que se com três caminhões ou seja. 01203450670 não foi possível
        // gera combinações de 012405670 por exemplo para rotas de dois caminhões
        // se não for possível, gera com 1 caminhão único.
        if(g->number_of_permutations==0){
                generatePermutation(1,g,g->number_of_cities);
                //generateCombinations(g,0);
        }
        printf("---- %d ", g->number_of_permutations);
        again = 0;
        for (i = 1; i < g->number_of_cities + 2; i++){
            last_city = current_city;
            if(current_city != -2 && g->permutations[0][i] != -2){
                current_city = g->permutations[0][i];
                acumulator += g->distances[last_city][current_city];
            }
        }

        comparator = acumulator;	//Atribui a comparator um valor inicial como se a primeira permutação fosse a melhor
        for (i = 1; i < g->number_of_permutations; i++) {
            acumulator = 0;
            for (j = 1; j < g->number_of_cities; j++) {
                last_city = g->permutations[i][j-1];
                if(current_city != -2 && g->permutations[i][j] != -2){
                    current_city = g->permutations[i][j];
                    acumulator += g->permutations[last_city][current_city];
                }
            }
            if(acumulator < comparator){
                comparator = acumulator;
                melhor = i;
            }
        }
        for(j=1;j<g->number_of_cities+3;j++){
            if(g->permutations[melhor][j]==0) // Verifica se não há zero, tal que 0120 é uma capacidade e 03450 é outra
                capacity = 0;
            capacity += g->vector_Aux[g->permutations[melhor][j]]; // conta a capacidade até encontrar um zero
            if(capacity > g->truck_capacity){ // e verifica se o somatorio não ultrapassa a capacidade do truck
                again = 1; // caso sim repetir recebe 1;
                // Função ERRO: sabe-se que a rota encontrada possui demanda insuficienta, tal que,
                //deve remover essa  'MELHOR' das permutações, tal que, apartir da melhor rota, ela é
                //sobrescrita com a posição da proxima permutação.
                    for(r=0;r<=g->number_of_permutations;r++){
                        for(q=0;q<g->number_of_cities+3;q++){
                            if(r>=melhor)
                                g->permutations[r][q] = g->permutations[r+1][q];
                    }
                   // free(g->permutations[r-1]);
                    g->number_of_permutations--;
                }

            break;
            }
        }
    }while(again);

    return g->permutations[melhor];
}
