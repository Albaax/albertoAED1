#include <stdio.h>
#include <stdlib.h>

/*Faça um programa que armazene a informacao de varias
pessoas.
• O programa so deve sair quando o usuario disser que nao
deseja mais entrar com os dados de outra pessoa.
• Antes de sair o programa deve apresentar, de forma
organizada, os dados de todas as pessoas.*/

typedef struct {
    char nome[30];
    int idade;
    int altura;
} Pessoa;


int main(){
    Pessoa *pPeople;
    int i = 0, mem = 1, choice;

    pPeople = (Pessoa *)malloc(sizeof(Pessoa));

    if(pPeople == NULL){
        printf("\nMemoria insuficiente!");
        return -1;
    }

    while(1){
        
        printf("\n\tDADOS DA PESSOA\n");
        printf("\nNome: ");
        scanf(" %s", pPeople[i].nome);
        printf("\nIdade: ");   
        scanf("%d", &pPeople[i].idade);
        printf("\nAltura: ");
        scanf("%d", &pPeople[i].altura); 

        printf("\n\t(0) Listar e sair\n\t(Any number) Adicionar mais pessoas\n\nOpcao: ");
        scanf("%d", &choice);

        if(choice == 0){
            break;
        }

        if(choice != 0){
            mem += 1;
            i++;
            pPeople = realloc(pPeople, sizeof(Pessoa) * mem);
        }
    
        system("cls");
    }

    int k;
    printf("\nListando:");
    for(k = 0; k <= i; k++){
        printf("\n---------\n");
        printf("\nNome: %s", pPeople[k].nome);
        printf("\nIdade: %d", pPeople[k].idade);
        printf("\nAltura: %d\n", pPeople[k].altura);
    }

    printf("\n");
    system("pause");
    free(pPeople);
    system("cls");

    return 0;
}