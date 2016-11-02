#include <stdio.h>
#include <stdlib.h>

#define NMAX 101
int a=0;

unsigned long int Fatorial(unsigned long int n){
    if(n==0 || n==1)
    return 1;
    return n*Fatorial(n-1);
}

void permuta(int nivel, int * n, int qtd_termos, int num_city, int *** vec_exit) {
        int i, j, parada = 0, *vec_temp;
        vec_temp = (int *)malloc((qtd_termos+1)*sizeof(int));
        if (nivel<=qtd_termos) {
            for (i=1; i<=num_city; i++) {
                 n[nivel]=i;
                 permuta(nivel+1, n, qtd_termos, num_city, vec_exit);
            }
        } else {
             for (i=1; i<=qtd_termos; i++) {
                  for (j=1; j<=qtd_termos; j++) {
                       if((n[i]==n[j])&&(i != j)){
                            parada = 666;
                            break;
                       }
                   }
                }
                if(parada != 666){
                     for (i=1; i<=qtd_termos; i++) {
                            vec_temp[i] =  n[i];
                     }
                     vec_temp[0] = 0;
                     vec_temp[i] = 0;
                     vec_temp[i+1] = 666;
                     (*vec_exit)[a] = (int *)malloc((qtd_termos + 1)*sizeof(int));
                     for(j = 0; j <= i+1; j++){
                        (*vec_exit)[a][j] = vec_temp[j];
                     }
                     a++;
                }
        }
}
void geradorDistancias(int num_city, int *** vec_distancias){
    int i, j, aleatorio;
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
    vec_city[i] = demandaFinal;
    return maior;
}

int trucks(int * trucks, int num_city, int * vec_city, int maior){
    int i = 2, capacity_truck, demandaFinal;
        demandaFinal = vec_city[num_city];
        while(1){
            if(demandaFinal%i == 0){
                if(maior > (demandaFinal/i) )
                    capacity_truck = demandaFinal;
                else
                    capacity_truck = demandaFinal/i;
                break;
            }
        }

    return capacity_truck;
}


int main(void) {
        int i, j, qtd_termos = 2, C = 0, teste;
        int num_city = 4;
        int n[NMAX];
        int **vec_exit;
        int **vec_distancias;
        int *vec_city;
        int maior;
        int *vec_trucks;

       for(i = 1; i<=qtd_termos; i++){
            C = C + Fatorial(num_city)/Fatorial(num_city-i);
       }
        vec_exit = (int**)malloc(C*sizeof(int));
        for (i=1; i<=qtd_termos; i++) {
                n[i]=-1;
        }
        for(i = 1; i<=qtd_termos; i++){
            permuta(1, n, i, num_city, &vec_exit);
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



        vec_distancias = (int**)malloc(num_city*sizeof(int));
        geradorDistancias(num_city, &vec_distancias);
        for(i=0; i<num_city; i++){
            for(j=0; j<num_city; j++){
                printf(" %d " , vec_distancias[i][j]);
            }
            printf("\n");
        }

        printf("\n");

        vec_city = (int*)malloc(num_city*sizeof(int));
        maior = demanda(vec_city, num_city);
        for(i=0;i<=num_city;i++){
            printf(" %d ", vec_city[i] );
        }
        printf("\n ---%d \n", maior);

        printf("\n");

        vec_trucks = (int*)malloc(num_city*sizeof(int) + sizeof(int));
        trucks(vec_trucks, num_city, vec_city, maior);


}



