#include <stdio.h>
#include <stdlib.h>


// Nao pronto.

void retira(int N, int *pVet);

int main(){
    int N, *pVet, i;

    printf("\nDigite o tamanho do vetor: ");
    scanf("%d", &N);

    pVet = (int *) malloc(sizeof(int)*N);

    if(pVet == NULL){
        printf("\nMemória insuficiente.\n");
        return -1;
    }
    printf("\nPreencha o Vetor: ");

    for(i = 0; i<N; i++){
        printf("\nVetor[%d] = ", i + 1);
        scanf("%d", &pVet[i]);
    }

    retira(N, pVet);

    printf("\nO vetor ficou");
    for(i = 0; i<N; i++){
        printf("Vetor[%d] = %d", i, *pVet);
        pVet++;
    }

    free(pVet);
    printf("\n");
    system("pause");
    system("cls");
    return 0;

}

void retira(int N, int *pVet){
    int *aux, *p;
    
    for(aux = pVet; aux!=NULL; aux++){  //aux recebe o endereço do vetor
        for(pVet = aux + 1; pVet!=NULL; pVet++){
            if(*pVet == *aux){
                for(p = pVet; p!=NULL; p++){
                    *p = *(p + 1);
                }
            } else {pVet++;}
        }
    }
    pVet = aux;

}