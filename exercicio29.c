#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/*Programa que armazena nomes, deve armazenar todos nomes na mesma string.
O tamanho da string  deve crescer e diminuir conforme os nomes forem colocados ou removidos
Faça o seguninte menu:
*/


char *add(char *pName, char *pName2);
char *removes(char *pName, char *del);
char check(char *pName, char *pCheck);

int main(){

    setlocale(LC_ALL, "Portuguese");
    char name2[25];
    int counter = 0;
    int i = 0;
    char *name = (char *)malloc(sizeof(char) * 25);

    if(name==NULL){
        printf("\nERRO! Falta de memoria\n");
        return -1;
    }

    while(1){
    printf("\t-------MENU-------");
    printf("\n\t(1) Adicionar nome \n\t(2) Remover nome \n\t(3) Listar \n\t(0) Sair\n");

    printf("\nDigite a opcao desejada: ");
    scanf("%d", &i);

    switch(i){
        case 1:
            if(counter == 0){ // Nenhum nome adicionado
                printf("\nDigite o nome que deseja adicionar: ");
                scanf("%s", name);
            }

            else{   // Já existe algum nome adicionado
                printf("\nDigite o nome que deseja adicionar: ");
                scanf("%s", name2);    
                name = (char *)realloc(name, sizeof(char)*(strlen(name) + strlen(name2) +2));    
                name = add(name, name2);
            }

            counter++;

            system("pause");
            system("cls");
        break;

        case 2:
            if(counter == 0) printf("\nNenhum nome foi encontrado!\n");

            else
            {
                printf("\nDigite o nome que voce deseja remover: ");
                scanf("%s", name2);

                check(name, name2);
                int exist = check(name, name2);

                if(exist == 1){
                    name = removes(name, name2);
                    printf("\nNome removido.\n");
                }

                else{
                    printf("\nO nome %s nao foi encontrado.\n", name2);
                }


            }
            
            system("pause");
            system("cls");
        break;

        case 3:
            if (counter == 0) printf("\nNenhum nome adicionado!\n");

            else printf("\nO(s) nome(s) adicionados sao:\n%s\n\n", name);

            system("pause");
            system("cls");
        break;

        case 0:
            printf("\nFim do programa!\n");
            free(name);
            system("pause");
            system("cls");
        break; 

        default:
            printf("\nOpcao invalida!\n");
            system("pause");
            system("cls");
        break;
        }

        if(i == 0) break;

    system("cls");
    }

    return 0;
}

char *add(char *pName, char *pName2){

    char *origin = pName; // Guarda o endereço na posição inicial

    while(*pName != '\0'){  // Move o ponteiro ate achar o '\0'
        pName++;
    }

    *pName = '\n'; // Substitui o '\0' por '\n'
    pName++;

    while(*pName2 != '\0'){
        *pName = *pName2;
        pName++;
        pName2++;
    }

    *pName = '\0';

    pName = origin; // Volta pra posição inicial

    return pName;
}

char check(char *pName, char *pCheck){ // Confere se a string descrita existe

    char *coin, mirror[75];
    
    strcpy(mirror, pName);
    coin = strtok(mirror, "\n");

    while(coin != NULL){
        if(strcmp(pCheck, coin) == 0){
            return 1;
        }

        coin = strtok(NULL, "\n");
    }

    return -1;
}


char *removes(char *pName, char *del){      // Remove o nome pedido

    int position = 1, k = 1;
    char *coin;
    char temp[75], mirror[75], mirror2[75];
    temp[0] = '\0';

    strcpy(mirror, pName);
    coin = strtok(mirror, "\n");

    while(coin != NULL){
        if(strcmp(del, coin) == 0) break;

        coin = strtok(NULL, "\n");
        position++;
    }

    strcpy(mirror2, pName);
    coin = strtok(mirror2, "\n");

    while(coin != NULL){
        if(position == k) coin = strtok(NULL, "\n");
        if(coin == NULL) break;

        strcat(temp, coin);
        strcat(temp, "\n");

        coin = strtok(NULL, "\n");
        k++;
    }

    pName = (char *) realloc(pName, strlen(temp) * sizeof(char));

    strcpy(pName, temp);

    return pName;
}