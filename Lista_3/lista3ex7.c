#include <stdio.h>
#include <stdlib.h>

int retira(int n, int *pVet);

int main(){
    int N, *pVet, i;

    printf("\nDigite o tamanho do vetor: ");
    scanf("%d", &N);

    pVet = (int *) malloc(sizeof(int)*N);

    if(pVet == NULL){
        printf("\nMemória insuficiente.\n");
        return -1;
    }
    printf("\nPreencha o Vetor:\n");

    for(i = 0; i<N; i++){
        printf("Vetor[%d] = ", i + 1);
        scanf("%d", &pVet[i]);
    }

    N = retira(N, pVet);

    printf("\nO vetor ficou:");
    for(i = 0; i<N; i++){
        printf(" %d",pVet[i]);
    }

    free(pVet);
    printf("\n");
    system("pause");
    system("cls");
    return 0;

}

int retira(int N, int *pVet){
    int k, i, j = 0;
    
    if(N == 0 || N == 1) return N;

    for(i = 0; i<N; i++){
        for(j = i + 1; j<N; j++){
            if(pVet[i] == pVet[j]){
                for(k = j; k<N; k++){
                    pVet[k] = pVet[k+1];
                }
                N--;
            }
        }
    }

    return N;
}


