#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define FALSE 0
#define TRUE 1

typedef struct data {
        int number;
}Data;

typedef struct node{
        Data data;
        struct node *left;
        struct node *right;
        int balance;
}Node;

void In_Order(Node *ptr);

Node *Rotate_Left(Node *pPtr);
Node *Rotate_Right(Node *pPtr);
Node *Insert(Node *pPtr, int ikey);
Node *Insert_Left_Check(Node *pPtr, int *pTaller);
Node *Insert_Right_Check(Node *pPtr, int *pTaller);
Node *Insert_Left_Balance(Node *pPtr);
Node *Insert_Right_Balance(Node *pPtr);

void Display(Node *ptr, int level);
int Is_Avl(Node *root);
int Height(Node *root);
int FB(Node *root);
void Free_Node(Node *root);

// Ainda faltando alguns requesitos do Stack Overflow

int main(){

        int choice = 0, key, n, i;
        Node *root = NULL;
        srand(time(NULL));
        while (choice != 3){
                
                printf("\n");
                printf("(1) Insert (type n - generate random numbers)\n");
                printf("(2) List\n");
                printf("(3) Verify if is AVL and exit\n");

                printf("\nChoose an option: ");
                scanf("%d", &choice);

                switch (choice) {
                        case 1:
                                printf("\nType N: ");
                                scanf("%d", &n);
                                for (i = 0; i < n; i++){                        
                                        key = rand() % 1000;
                                        root = Insert(root, key);
                                }
                                break;

                        case 2:
                                printf("\n");
                                Display(root, 0);
                                printf("\n");
                                break;

                        case 3:
                                i = Is_Avl(root);
                                if(i == 1)
                                        printf("Is an AVL tree!\n");
                                else
                                        printf("Is not an AVL tree!\n");
                                        
                                
                                break;

                        default:
                                printf("Choice inexistent. Try again!\n");

                } 
        }         

        Free_Node(root);
        return 0;

}

Node *Insert(Node *pPtr, int ikey){
        
        static int taller;

        if (pPtr == NULL) {//
                pPtr = (Node *)malloc(sizeof(Node));

                if(pPtr == NULL){
                    printf("\nERROR: Allocation failed!");
                    return 0;
                }
                pPtr->data.number = ikey;
                pPtr->left = NULL;
                pPtr->right = NULL;
                pPtr->balance = 0;
                taller = TRUE;
        }

        else if (ikey < pPtr->data.number){                     // Inserção na subarvore esquerda      
                pPtr->left = Insert(pPtr->left, ikey);
                if (taller == TRUE)
                        pPtr = Insert_Left_Check(pPtr, &taller);
        }

        else if (ikey > pPtr->data.number){                     // Inseerção na subarvore direita                    
                pPtr->right = Insert(pPtr->right, ikey);
                if (taller == TRUE)
                        pPtr = Insert_Right_Check(pPtr, &taller);
        }

        else {                                                  // 2 key
                printf("Duplicate key\n");
                taller = FALSE;
        }
        return pPtr;
} 

Node *Insert_Left_Check(Node *pPtr, int *pTaller){

        switch (pPtr->balance){
                case 0:                                         // Estava balanceado
                        pPtr->balance = 1;                      // Agora esq ficou desbalanceado
                        break;
                case -1:                                        // Dir estava desbalanceado
                        pPtr->balance = 0;                      // Agora balanceado
                        *pTaller = FALSE;
                        break;
                case 1:                                         // Esq estava desbalanceada
                        pPtr = Insert_Left_Balance(pPtr);        // Balanceamento na esquerda
                        *pTaller = FALSE;
                        break;
        }
        return pPtr;
} 

Node *Insert_Right_Check(Node *pPtr, int *pTaller){

        switch (pPtr->balance){
                case 0:                                         // Estava balanceado
                        pPtr->balance = -1;                     // Agora dir ficou desbalanceado
                        break;
                case 1:                                         // Esquerda estava desbalanceada
                        pPtr->balance = 0;                      // Agora balanceado
                        *pTaller = FALSE;
                        break;
                case -1:                                        // Direita desbalanceada
                        pPtr = Insert_Right_Balance(pPtr);       // Balanceamento na direita
                        *pTaller = FALSE;
                        break;
        }
        return pPtr;
} 

Node *Insert_Left_Balance(Node *pPtr){

        Node *auxPtr, *bptr;

        auxPtr = pPtr->left;
        if (auxPtr->balance == 1) {                             // Inserçao subarvore esq
                pPtr->balance = 0;
                auxPtr->balance = 0;
                pPtr = Rotate_Right(pPtr);
        }

        else {                                                  // Insertion subarvore dir
                bptr = auxPtr->right;
                switch (bptr->balance){
                        case -1:                                // Inserção dir
                                pPtr->balance = 0;
                                auxPtr->balance = 1;
                                break;
                        case 1:                                 // Inserçao esq
                                pPtr->balance = -1;
                                auxPtr->balance = 0;
                                break;
                        case 0:                                 // B eh o novo no inserido
                                pPtr->balance = 0;
                                auxPtr->balance = 0;
                                break;
                }
                bptr->balance = 0;
                pPtr->left = Rotate_Left(auxPtr);
                pPtr = Rotate_Right(pPtr);
        }
        return pPtr;
} 

Node *Insert_Right_Balance(Node *pPtr){

        Node *auxPtr, *bptr;

        auxPtr = pPtr->right;
        if (auxPtr->balance == -1) {                            // Inserçao subarvore dir
                pPtr->balance = 0;
                auxPtr->balance = 0;
                pPtr = Rotate_Left(pPtr);
        }

        else {                                                  // Inserçao subarvore esq
                bptr = auxPtr->left;
                switch (bptr->balance) {
                        case -1:                                 // Inserçao dir
                                pPtr->balance = 1;
                                auxPtr->balance = 0;
                                break;
                        case 1:                                  // Inserçao esq
                                pPtr->balance = 0;
                                auxPtr->balance = -1;
                                break;
                        case 0:                                 // B eh o novo no inserido
                                pPtr->balance = 0;
                                auxPtr->balance = 0;
                                break;
                }
                bptr->balance = 0;
                pPtr->right = Rotate_Right(auxPtr);
                pPtr = Rotate_Left(pPtr);
        }
        return pPtr;
} 

Node *Rotate_Left(Node *pPtr){
        
        Node *auxPtr;
        auxPtr = pPtr->right;                                   // A eh o filho a direita de P
        pPtr->right = auxPtr->left;                             // O filho a direita de 
        auxPtr->left = pPtr;                                    // P se torna o filho a esquerda de A
        return auxPtr;                                          // A eh a nova raiz da subarvore inicializada com a raiz P
}

Node *Rotate_Right(Node *pPtr){
        
        Node *auxPtr;     
        auxPtr = pPtr->left;                                    // A eh o filho a esquerda de P
        pPtr->left = auxPtr->right;                             // Filho a direita de A se torna o filho a esquerda de P
        auxPtr->right = pPtr;                                   // P se torna o filho a direita de A
        return auxPtr;                                          // A eh a nova raiz da subarvore inicializada com a raiz P 
} 

void Display(Node *ptr, int level){

        int i;
        if(ptr == NULL )                                        // No nodes
                return;
        else{
                Display(ptr->right, level+1);
                printf("\n");
                for (i = 0; i < level; i++)
                        printf("    ");
                printf("%d", ptr->data.number);
                Display(ptr->left, level+1);
        }
}

// isAVL
int FB(Node *root){
        
        if(root == NULL)
                return 0;

        return Height(root->left) - Height(root->right);
}

int Height(Node *root){
        int iLeft, iRight;

        if(root == NULL)
                return 0;
        
        iLeft = Height(root->left);
        iRight = Height(root->right);

        if(iLeft > iRight)
                return iLeft + 1;

        else
                return iRight + 1;
}

int Is_Avl(Node *root){
        
        int fb;
        if (root == NULL)
                return 1;
        
        if (!Is_Avl(root->left))
                return 0;
        
        if (!Is_Avl(root->right))
                return 0;
        
        fb = FB (root);
        if ((fb > 1) || (fb < -1))
                return 0;
        
        else
               return 1;
}

void Free_Node(Node *root){                                         // Libera a arvore

    if(root == NULL)
            return;
        
    Free_Node(root->left);
    Free_Node(root->right);

    free(root);
}