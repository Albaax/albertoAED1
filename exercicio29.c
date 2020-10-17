#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoas{
    char nome[100];
}nomepessoas;

void adiciona(nomepessoas *p);

int main(){

    nomepessoas people, *pPeople;

    pPeople = (nomepessoas *)malloc(sizeof(nomepessoas));

    if(pPeople==NULL){
        printf("\nERRO! Falta de memoria");
        return -1;
    }

    int i=1;

    while(i!=0){
    printf("------MENU------");
    printf("\n1) Adicionar nome \n2) Remover nome \n3) Listar \n0) Sair\n");

    printf("\nDigite a opcao desejada: ");
    scanf("%d", &i);

    switch(i){
        case 1:
        adiciona(pPeople);
        printf("\nNome: %s", pPeople->nome);
        break;
        case 0:
        break; 
        }
    system("cls");
    }
    free(pPeople);
    return 0;
}

void adiciona(nomepessoas *pPeople){
    
    printf("\nDigite o nome que deseja adicionar: ");
    fgets(pPeople->nome, 100, stdin);
    
}