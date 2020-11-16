#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    char name[20];
    int age;
    int phonenumber;
}Data;

typedef struct node {
    Data data;
    struct node *next;
    struct node *previous;
}Node;

typedef struct list {
    int size;
    Node *head;
    Node *pLast;
}List;

typedef struct control {
    int k, l;
    int choice;
    char nameAux[20];
    List *pList;
}Control;


List *Create_List();
List *Search_By_Name(List *list, Control *pControl);
Control *Create_Control(void *pBuffer);

int Insert_Person(List *list, Data data);
void Clear_List(List *list);
void Print_List(List *list);
void Remove_Last_Person(List *list);
void Remove_byName(List *list, Control *pControl);
void Sort_Queue_Bubblesort(List *list, Control *pControl);

int main(){

    void *pBuffer = (void*) malloc(sizeof(Control));
    Control *pControl = Create_Control(pBuffer);                        // Struct Control crated
    List *listMain = Create_List();                                     // Struct List created
    pControl->pList = listMain;                                         
    Data data;

    do{

        printf("\n------MENU------"
               "\n(1) - Add a Person"
               "\n(2) - Remove a Person by name"
               "\n(3) - Remove last Person added"
               "\n(4) - Search a Person by name"
               "\n(5) - List People"
               "\n(6) - Sort with bubblesort and print"
               "\n(0) - Clear and Exit");

        printf("\n\nChoose an option: ");
        scanf("%d", &(pControl->choice));

        switch(pControl->choice) {
            
            case 1:

                printf("\n-----Person Data----");                                       // Receive data from user
                printf("\n--Name: ");
                scanf(" %[^\n]s", data.name);
                printf("--Age: ");
                scanf("%d", &data.age);
                printf("--Phonenumber: ");
                scanf("%d", &data.phonenumber);

                Insert_Person(listMain, data);
                printf("\nPerson registered!");
                break;
            
            case 2:

                listMain->size++;
                if(listMain->head == NULL){
                    printf("\nThe list is empty!");
                    break;
                }

                printf("\nWho do you want to remove? ");
                scanf(" %[^\n]s", pControl->nameAux);

                Remove_byName(listMain, pControl);
                break;

            case 3:

                Remove_Last_Person(listMain);
                break;

            case 4:

                if(listMain->head == NULL){
                    printf("\nThe list is empty!");
                }
                else{
                    printf("\nWho are you looking for: ");
                    scanf(" %[^\n]s", pControl->nameAux);

                    Search_By_Name(listMain, pControl);
                }
                break;
            
            case 5:

                Print_List(listMain);
                break;
            
            case 6:

                Sort_Queue_Bubblesort(listMain, pControl);
                break;

            case 0:

                printf("\nLeaving...");
                break;
            default:
                
                printf("\nThis option does not exist!");
                break;
            }
            printf("\n");

    }while(pControl->choice != 0);
    
    Clear_List(listMain);
    free(pBuffer);
    return 0;
}

List *Create_List(){                                                        // Create and inicialize a Struct List
    List *list = (List*) malloc(sizeof(List));

    if(list == NULL){
        printf("\nERROR: Allocation failed!");
        return 0;
    }
    list->size = 0;
    list->head = NULL;
    list->pLast = NULL;

    return list;
}

List *Search_By_Name(List *list, Control *pControl){                           

    Node *tempNode = list->head;
    
    pControl->k = 0;    // aux
    while(tempNode != NULL){                                                
        if(strcmp(tempNode->data.name, pControl->nameAux) == 0){            // If strcmp = 0. print the person
            printf("\nName: %s", tempNode->data.name);
            printf("\nAge: %d", tempNode->data.age);
            printf("\nPhonenumber: %d", tempNode->data.phonenumber);
            printf("\n---------");
            pControl->k++;
        }
        tempNode = tempNode->next;        
    }

    
    if(pControl->k == 0)
        printf("\n%s was not founded.", pControl->nameAux);

    free(tempNode);
    return 0;
}


Control *Create_Control(void *pBuffer){                                     // Create and incialize a Struct Control
    Control *pControl = pBuffer;

    pControl->k = 0;
    pControl->l = 0;
    pControl->choice = 0;
    pControl->pList = NULL;

    return pControl;
    
}

int Insert_Person(List *list, Data data){

    Node *node = (Node*) malloc(sizeof(Node));
    if(node == NULL){                                                       // Check if node was allocated
        printf("\nERROR: Allocation failed!");
        return 0;   
    }

    node->data = data;                                                      // Node Data receive data from the user
    node->next = list->head;                                                // Next pointo to Head(If size=1, head=NULL)
    node->previous = NULL;                                                  // Previous point to NULL

    if(list->head != NULL)                                                  // If list isn't empty
        list->head->previous = node;                                        // Head previous point to the new node   
    list->head = node;                                                      // Node is the new head
    
    return 1;
}

void Clear_List(List *list){                                                // Free node by node

    if(list->head == NULL)
        return;
    
    else{
        Node *tempNode;
        while(list->head != NULL){
            tempNode = list->head;
            list->head = list->head->next;
            free(tempNode);
        }
    }
    free(list);                                                                     // Free List
}

void Print_List(List *list){                                                        // Print list

    if(list->head == NULL){
        printf("\nThe list is empty!");
        return;
    }

    Node *tempNode = list->head;

    printf("\n------Agenda-----");
    while(tempNode != NULL){
        printf("\nName: %s", tempNode->data.name);
        printf("\nAge: %d", tempNode->data.age);
        printf("\nPhonenumber: %d", tempNode->data.phonenumber);
        printf("\n------------");        
        tempNode = tempNode->next;
    }
    free(tempNode);
}

void Remove_Last_Person(List *list){                                                // Remove the last person 

    if(list->head == NULL){
        printf("\nThe list is empty!");
        return;
    }

    Node *tempNode = list->head;

    list->head = tempNode->next;
    if(tempNode->next != NULL)
        list->head->previous = NULL;

    list->size--;
    printf("\n%s was removed!", tempNode->data.name);
    free(tempNode);
}

void Remove_byName(List *list, Control *pControl){

    Node *tempNode = list->head;

    while(tempNode != NULL && strcmp(tempNode->data.name, pControl->nameAux) != 0){     // While tempNode != NULL and strcmp are not 0 = (names are equal)
        tempNode = tempNode->next;                                                      
    }

    if(tempNode == NULL){                                                               // If the name from user does not exist return to main 
        printf("\n%s does not exist!", pControl->nameAux);
        free(tempNode);
        return;
    }

    if(tempNode->previous == NULL)                                                      // If the person is the first on the list
        list->head = tempNode->next;                                                    // If is the only person Head will point to NULL
    
    else
        tempNode->previous->next = tempNode->next;                                      // Next from previous node point to tempNode next
    
    if(tempNode != NULL && tempNode->next != NULL)                                                             
        tempNode->next->previous = tempNode->previous;                                  // Previous from next node will point to temp-previous

    printf("\n%s was removed!", tempNode->data.name);
    free(tempNode);
}


void Sort_Queue_Bubblesort(List *list, Control *pControl){                              // ERROR: Funcion is not working as should be

    if(list->head == NULL){
        printf("\nThe list is empty!");
        return;
    }

    if(list->size == 1){
        printf("\nThe list is already sorted!");
        return;
    }
    Node *tempNode = list->head;
    Node *aux = NULL;

    for(pControl->k = 0; pControl->k < list->size - 1; (pControl->k)++){
        tempNode = list->head;
        {
            if(strcmp(tempNode->data.name, tempNode->next->data.name) > 0){
                aux = tempNode->next;
                tempNode = tempNode->next;
                tempNode->next = aux;
            }            
                tempNode = tempNode->next;
        }
    }

    Print_List(list);
    free(tempNode);
    free(aux);
}















