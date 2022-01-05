// Author Berkay Mengunogul
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//max macro
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// node structure for linked list
typedef struct Node{
    int value;
    int height;
    int position;
    int depthLevel;
    struct Node* leftChild; 
    struct Node* rightChild; 
} node;


// for sorting the nodes by their values by descending order
void insertionSort(node *array, int numOfElements){
    node key;
    for(int i=0; i < numOfElements; i++){
        key = array[i];
        int j = i - 1;
        while (j >= 0 && array[j].value < key.value) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

// get height
int getHeight(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

// right rotate
node *rightRotate(node *y) {
  node *x = y->leftChild;
  node *T2 = x->rightChild;

  x->rightChild = y;
  y->leftChild = T2;

  y->height = MAX(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
  x->height = MAX(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;

  return x;
}

// left rotate
node *leftRotate(node *x) {
  node *y = x->rightChild;
  node *T2 = y->leftChild;

  y->leftChild = x;
  x->rightChild = T2;

  x->height = MAX(getHeight(x->leftChild), getHeight(x->rightChild))+ 1;
  y->height = MAX(getHeight(y->leftChild), getHeight(y->rightChild))+ 1;

  return y;
}

// Get the balance factor
int checkBalance(node *N) {
  if (N == NULL)
    return 0;
  return getHeight(N->leftChild) - getHeight(N->rightChild);
}

// Insert node
node *insertAVL(node *curNode, node *keyNode) {
  // Find the correct position to insertNode the node and insertNode it
  if (curNode == NULL)
    return keyNode;

  if (keyNode->value < curNode->value)
    curNode->leftChild = insertAVL(curNode->leftChild, keyNode);
  else if (keyNode->value > curNode->value)
    curNode->rightChild = insertAVL(curNode->rightChild, keyNode);
  else
    return curNode;

  // Update the balance factor of each node and
  // Balance the tree
  curNode->height = 1 + MAX(getHeight(curNode->leftChild),
               getHeight(curNode->rightChild));

  int balance = checkBalance(curNode);
  if (balance > 1 && keyNode->value < curNode->leftChild->value)
    return rightRotate(curNode);

  if (balance < -1 && keyNode->value > curNode->rightChild->value)
    return leftRotate(curNode);

  if (balance > 1 && keyNode->value > curNode->leftChild->value) {
    curNode->leftChild = leftRotate(curNode->leftChild);
    return rightRotate(curNode);
  }

  if (balance < -1 && keyNode->value < curNode->rightChild->value) {
    curNode->rightChild = rightRotate(curNode->rightChild);
    return leftRotate(curNode);
  }

  return curNode;
}

 node *insertBST(node *curNode, node *newNode){
   if (curNode == NULL){
     return newNode;
   }
   if(newNode->value > curNode->value){
     curNode->rightChild = insertBST(curNode->rightChild, newNode);
   }else if(newNode->value < curNode->value){
     curNode->leftChild = insertBST(curNode->leftChild, newNode);
   }
   return curNode;
 }

node *minValuenode(node *N) {
  node *current = N;

  while (current->leftChild != NULL)
    current = current->leftChild;

  return current;
}

void printOutput(int numberOfFullDepthLevels, int numberOfDepthLevels, int numberOfAccesiveNodes, int remainingNodes){
  printf("Output:\n");
  printf("Depth level of BST is %d\n", numberOfDepthLevels);
  int depthLevel;
  for (depthLevel = 0; depthLevel< numberOfFullDepthLevels; depthLevel++){
    printf("Depth level %d -> %d\n", depthLevel, (int)pow(2,depthLevel));
  }
  printf("Depth level %d -> %d\n", depthLevel++, numberOfAccesiveNodes);
  while(remainingNodes>0){
    printf("Depth level %d -> %d\n", depthLevel++, 1);
    remainingNodes--;
  }
  
}

node *findKey(node *currentNode, int key, int position, int depth){
  if(currentNode->value == key){
    currentNode->position = position;
    currentNode->depthLevel = depth;
    return currentNode;
  }else if (currentNode->value > key){
    return findKey(currentNode->leftChild, key, 2*position-1, depth+1);
  }else if (currentNode->value < key){
    return findKey(currentNode->rightChild, key, 2*position, depth+1);
  }
  return NULL;
}

void printPreOrder(node *root) {
  if (root != NULL) {
    printf("%d ", root->value);
    printPreOrder(root->leftChild);
    printPreOrder(root->rightChild);
  }
}
int main(void){
    FILE *inputFilePtr;
    node* root = NULL;
    int countnodes = 0;
    char currentNumber[11];

    node *arrayOfnodes = calloc(2, sizeof(node));

    // main function gets the dir of input file from command line
    if ((inputFilePtr = fopen("input.txt", "r")) != NULL) {

      // creates a linked list for multiplicand from input
      while (fscanf(inputFilePtr, " %10s", currentNumber) == 1)
      {   
          // check node, if less than zero
          if(atoi(currentNumber) < 0){
              printf("Input file contains values less than zero.\n");
              return -1;
          }
          // check node, if replicate node occurs
          for(int i=0; i < countnodes; i++){
              if (arrayOfnodes[i].value == atoi(currentNumber)){
                  printf("Input file contains replicated keys.\n");
                  return -1;
              }
          }

          node newnode;
          newnode.value = atoi(currentNumber);
          newnode.height = 1;
          newnode.position = 1;
          newnode.depthLevel = 0;
          newnode.leftChild = NULL;
          newnode.rightChild = NULL;
          arrayOfnodes[countnodes] = newnode; 
          countnodes++;
          arrayOfnodes = realloc(arrayOfnodes, countnodes+1 * sizeof(node));
      }
        
      // check number of nodes, give error if less than 16.
      if (countnodes < 16){
        printf("Input file contains less than 16 elements.\n");
        return -1;
      }

      // sort the array in descending order.
      insertionSort(arrayOfnodes, countnodes);

      int numberOfFullDepthLevels = (int)floor(log2(countnodes));
      int numberOfDepthLevels = 3*floor(log(countnodes)/log(4));
      int numberOfAccesiveNodes = countnodes - (int)pow(2, floor(log2(countnodes)))+1-numberOfDepthLevels+numberOfFullDepthLevels+1;
      int remainingNodes = countnodes-(int)pow(2, numberOfFullDepthLevels)+1-numberOfAccesiveNodes;
      printOutput(numberOfFullDepthLevels, numberOfDepthLevels, numberOfAccesiveNodes, remainingNodes);
      
      int i, j;
      for (i = 0; i < countnodes-remainingNodes; i++){
          root = insertAVL(root, &arrayOfnodes[i]);
          printf("node avl %d\n", arrayOfnodes[i].value);
      }

      for (j = 0; j < remainingNodes; j++)
      {
          insertBST(root, &arrayOfnodes[i+j]);
          printf("node remaining %d\n", arrayOfnodes[i+j].value);
      }
      
      printPreOrder(root);

      int input;
      while(input != 0){
        printf("\nKey value to be searched (Enter 0 to exit) :");
        scanf("%d", &input);
        node *keyNode = findKey(root, input, 1, 0);
        if(keyNode == NULL){
          printf("%d is not found in BST", input);
        }else{
          printf("At Depth level %d, %d. element", keyNode->depthLevel, keyNode->position);
        } 
      }
    }

    printf("Exit\n");
    free(arrayOfnodes);
    return 0;
}