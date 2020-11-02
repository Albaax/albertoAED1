#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int word(char *linha, char *newline);

int main(){
    
    char *linha;
    linha = (char*) malloc(sizeof(char)*80);

    if(linha == NULL){
        printf("Memoria insuficiente!\n");
        return -1;
    }

    printf("Diga a frase:\n");
    scanf(" %[^\n]s", linha);

    int k = strlen(linha);

    char *newline;
    newline = (char*) malloc(sizeof(char)*k+1);
    
    if(newline == NULL){
        printf("Memoria insuficiente!\n");
        return -1;
    }
    
    int n;
    n = word(linha, newline);

    int i;

    printf("\nA frase ficou:\n");
    for(i=0; i<n; i++){
        printf("%c", newline[i]);
    }
    
    printf("\n");
    free(linha);
    free(newline);
    return 0;
}

int word(char *linha, char *newline){

    int n=0;

    for( ; *linha != '\0'; linha++){
        if(*linha == ' '){
            *newline = '\n';
            newline++;
        }
        else{
            *newline = *linha;
            newline++;
        }
        n++;
    }

    *newline = '\0';
    system("pause");
    free(linha);

    return n;
}