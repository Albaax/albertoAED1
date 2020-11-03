#include <stdio.h>
#include <stdlib.h>

/*Faça uma agenda capaz de incluir, apagar, buscar e listar quantas
pessoas o usuário desejar, porém, você não pode usar variáveis a
não ser ponteiros. Toda a informação deve ser guardada num “void
*pBuffer”.*/

typedef struct Person {                     // Dados da pessoa
    char name[20];
    int age;
    long int phonenumber;
} Person;

void *pBuffer;
int *choice, *amountPeople, *k, *l;         // Declarando variaveis inteiras e do tipo Struct para o uso
Person *thisPerson, *tempPerson;

void addPerson();
void checkEndBuffer(void *pBuffer);
void atributesBuffer(void *pBuffer);

int main(){
    
    pBuffer = (void*) malloc((sizeof(int)*4) + sizeof(Person)); // Aloca espaço para os 4 inteiros e "tempPerson"
    
    atributesBuffer(pBuffer);
    *amountPeople = 0;

    while(1){
        printf("\n-------MENU-------"
            "\n(1) - Add a person"
            "\n(2) - Remove a person"
            "\n(3) - Search a person"
            "\n(4) - List people"
            "\n(8) - Exit");

        printf("\n\nChoose an option: ");
        scanf("%d", choice);


        switch(*choice){

            case 1:

                (*amountPeople)++;

                pBuffer = (void*) realloc(pBuffer, (sizeof(int)*4) + sizeof(Person) + sizeof(Person)*(*amountPeople));

                atributesBuffer(pBuffer);
                checkEndBuffer(pBuffer);                
                addPerson();
                        
                printf("\nThe person was registered!\n");


                break;

            case 2:


                break;

            case 3:


                break;

            case 4:


                break;
            
            case 8:

                printf("\nLeaving...");
                free(pBuffer);
                return 0;
            
            default:

                printf("\nOption was not founded!");
        }
    }


}


void addPerson(){  // Adiciona os dados da pessoa
    printf("\nName: ");
    scanf(" %s[^\n]", thisPerson->name);
    printf("Age: ");
    scanf("%d", &thisPerson->age);
    printf("Phonenumber: ");
    scanf("%li", &thisPerson->phonenumber);
}

void atributesBuffer(void *pBuffer){  // Coloca os atributos inteiros e "struct Person" nas posicoes do Buffer
    amountPeople = pBuffer;
    choice = amountPeople + 1;
    k = choice + 1;
    l = k + 1;
    tempPerson = (Person*) l + 1;
    if(*amountPeople > 0){
        thisPerson = (Person*) tempPerson + 1;
    }
}

void checkEndBuffer(void *pBuffer){  // Verifica onde fica o final do Buffer
    thisPerson = tempPerson + 1;
    for(*k = 1; *k < *amountPeople; k++ ){   // Se k eh menor que "amountPeople" passa pra proxima posicao do Buffer ate achar a ultima posicao
        thisPerson++;
    }    
}

