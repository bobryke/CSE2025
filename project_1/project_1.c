#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Node structure for linked list
typedef struct node{
    int value;
    struct node* next; 
} node;

// Function for inserting a node to a given linked list
void insertNode(node **head, int value){
    struct node* newNode = (node*) malloc(sizeof(node));
    newNode->value  = value;
    // if starting pointer doesnt indicate any adress first node will be directed to the starting pointer
    if(*head == NULL){ 
            *head = newNode;
            return;
        }

    // It skips over till last node where next node is empty
    node *currentPtr = *head;
    while (currentPtr->next != NULL){
            currentPtr = currentPtr->next;
        }
    // links the new node to the end of linked list   
    currentPtr -> next = newNode;
}

// Function for multiplying the linked list and saving it into a another linked list
void multiplyLists(node **multiplicand, node **multiplier, node **result){
    
    // multiplier digits
    node *currentMultiplierPtr = *multiplier;
    int multiplierIndex = 0; // to track the index of multiplier di
    int carry = 0; // to hold the carry digit of multiplication for next iteration
    while (currentMultiplierPtr != NULL){
            // multiplicand digits
            node *currentMultiplicandPtr = *multiplicand;
            node* currentResultPtr = *result;
            
            // it skips the multiplier digits by the index of multipler
            // The reason is every currentMultiplierPtr digit is multiples of 10**index.
            
            // to illustrate; 
            //   12
            //   23
            //x____
            //  36 
            // 24  --> 6 is skipped
            //_____
            // 276

            for(int i = 0; i <multiplierIndex; i++){
                    currentResultPtr = currentResultPtr->next;
                }
            
            //goes through multiplicand digits till the last digit/
            while (currentMultiplicandPtr != NULL){
                // if linked list of result indicates empty node then it inserts
                if (currentResultPtr == NULL){
                    int value = currentMultiplierPtr->value * currentMultiplicandPtr->value + carry;
                    carry = (value / 10)%10; // update the carry in here
                    insertNode(result, value%10);
                    currentResultPtr = *result;
                    while (currentResultPtr != NULL){
                        currentResultPtr = currentResultPtr->next;
                    }
                // else it updates the value of current node    
                } else {
                    int value = currentMultiplierPtr->value * currentMultiplicandPtr->value + carry + currentResultPtr->value;
                    carry = (value / 10)%10; // update the carry in here
                    currentResultPtr->value = value%10;
                    currentResultPtr = currentResultPtr->next;
                }
                currentMultiplicandPtr = currentMultiplicandPtr->next;
            }
            // at the end of the multiplication if there is any carry left, it will be inserted to linked list
            if(carry != 0){
            insertNode(result, carry);
            carry = 0;
        }
            // update the pointer to next multiplier digit
            currentMultiplierPtr = currentMultiplierPtr->next;
            // update the value of multiplier digit
            multiplierIndex += 1;
        }
        // at the end of the multiplication if there is any carry left, it will be inserted to linked list
        if(carry != 0){
            insertNode(result, carry);
            carry = 0;
        }
                   
    return;
}

// Fuction for reversing a linked. It is need beacuse while multiplying the numbers 
// process happening from right to left
// when it comes to printing the result it happens from left to right.
// Since one-way linked lists used in this project it is a necessary function 
void reverseList(node** head){
    node* prevPtr = NULL;
    node* currentPtr = *head;
    node* nextPtr = NULL;
    while(currentPtr != NULL){
        nextPtr = currentPtr->next;
        currentPtr->next = prevPtr;
        prevPtr = currentPtr;
        currentPtr = nextPtr;
    }
    *head = prevPtr;
}

// write the results to the ouput file
void printListsToFile(node **multiplicand, node **multiplier, node **result){
    FILE *outputFilePtr;

    // With using reverseList function, before printing the results I reversed the linked lists
    // one by one
    // The reason is digits are multiplied right from left but printed the opposite way.
    reverseList(multiplicand);
    reverseList(multiplier);
    reverseList(result);

    if ((outputFilePtr = fopen("output.txt", "w")) !=NULL) {
        //write multiplicand
        node *currentPtr = *multiplicand;
        while (currentPtr != NULL){
               fprintf(outputFilePtr, "%d", currentPtr->value);
                currentPtr = currentPtr->next;
                
            }
        fprintf(outputFilePtr, "\n");
        //write multiplier
        currentPtr = *multiplier;
        while (currentPtr != NULL){
               fprintf(outputFilePtr, "%d", currentPtr->value);
                currentPtr = currentPtr->next;
                
            }
        fprintf(outputFilePtr, "\n");
        //write result
        currentPtr = *result;
        while (currentPtr != NULL){
               fprintf(outputFilePtr, "%d", currentPtr->value);
                currentPtr = currentPtr->next;
                
            }
    }else{
        printf("File could not saved");
    }
}

int main(int argc, char* argv[]){
    FILE *inputFilePtr;
    node* multiplicandHead = NULL;
    node* multiplierHead = NULL;
    node* resultHead = NULL;

    // main function gets the dir of input file from command line
    // main function gets the dir of input file from command line
    if ((inputFilePtr = fopen(argv[1], "r")) != NULL) {
        char input_multiplicand, input_multiplier;

        // creates a linked list for multiplicand from input
        while (((input_multiplicand = fgetc(inputFilePtr)) != EOF) && (input_multiplicand != '\n'))
        {   
            insertNode(&multiplicandHead, atoi(&input_multiplicand));
        }
        
        // creates a linked list for multiplier from input
        while (((input_multiplier = fgetc(inputFilePtr)) != EOF) && (input_multiplier != '\n'))
        {   
            insertNode(&multiplierHead, atoi(&input_multiplier));
        }

        //reversing the linked lists beacuse numbers are multiplied right to left
        reverseList(&multiplicandHead);
        reverseList(&multiplierHead);

        // multiples
        multiplyLists(&multiplicandHead, &multiplierHead, &resultHead);
        // puts the result to the output file
        printListsToFile(&multiplicandHead, &multiplierHead, &resultHead);
    }
}
