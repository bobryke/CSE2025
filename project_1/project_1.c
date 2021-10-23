#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node{
    int value;
    struct node* next; 
} node;

void insertNode(node **head, int value){
    struct node* newNode = (node*) malloc(sizeof(node));
    newNode->value  = value;

    if(*head == NULL){ // if starting pointer doesnt indicate any adress first node will be directed to the starting pointer
            *head = newNode;
            return;
        }

    node *currentPtr = *head;
    while (currentPtr->next != NULL){
            currentPtr = currentPtr->next;
        }
    currentPtr -> next = newNode;
}

void multiplyLists(node **multiplicand, node **multiplier, node **result){
    // multiplier digits
    node *currentMultiplierPtr = *multiplier;
    while (currentMultiplierPtr->next != NULL){
            // multiplicand digits
            node *currentMultiplicandPtr = *multiplicand;
            int carry = 0;
            int multiplcandIndex = 0;
            while (currentMultiplicandPtr->next != NULL){
                if(index == 0){
                    int value = currentMultiplierPtr->value * currentMultiplicandPtr->value + carry;
                    carry = (value /= 10)%10; // update the carry in here
                    insertNode(result, value%10);
                    currentMultiplicandPtr = currentMultiplicandPtr->next;
                }else{
                    printf("index: %d\n", multiplcandIndex);
                }
                multiplcandIndex += 1;
            }
            // next multiplier digit
            currentMultiplierPtr = currentMultiplierPtr->next;
        }
    return;
}

void printNodes(node **head){
    node *currentPtr = *head;
    printf("%d", currentPtr->value);
    while (currentPtr->next != NULL){
            currentPtr = currentPtr->next;
            printf("%d", currentPtr->value);
        }
}

int main(void){
    node* multiplicandHead = NULL;
    node* multiplierHead = NULL;
    node* resultHead = NULL;

    char input_multiplicand[999];
    char input_multiplier[999];
    // read the input
    fgets(input_multiplicand, 999, stdin);
    fgets(input_multiplier, 999, stdin);
    // delete the trailing '/n'
    input_multiplicand[strcspn(input_multiplicand, "\n")] = 0;
    input_multiplier[strcspn(input_multiplier, "\n")] = 0;
    
    for(int i = 0; i<strlen(input_multiplicand); i++){
        // with -48, the char is turned into the corresponding integer
        insertNode(&multiplicandHead, input_multiplicand[i]-48);
    }

    for(int i = 0; i<strlen(input_multiplier); i++){
        // with -48, the char is turned into the corresponding integer
        insertNode(&multiplierHead, input_multiplier[i]-48);
    }
    printf("\nprinting nodes: ");
    printNodes(&multiplicandHead);
    multiplyLists(&multiplicandHead, &multiplierHead, &resultHead);
    printf("\nprinting nodes: ");
    //printNodes(&resultHead);
}