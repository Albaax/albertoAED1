#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Implemente a funcao realloc:
void *realloc(void *pont, size_t newsize);

Dica: void *memcpy(void *destination, const void * source, size_t num);
*/

void *reallocando(void *pointer, size_t tam);

int main(){

    int *pointer = (int*)malloc(sizeof(int));
    pointer = reallocando(pointer, 50);
    
    free(pointer);
    return 0;
}

void *reallocando(void *pointer, size_t tam){
    void *aux = malloc(tam);
    
    memcpy(aux, pointer, sizeof(pointer));

    free(pointer);
    return aux;
}