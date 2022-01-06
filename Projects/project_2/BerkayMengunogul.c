// Author Berkay Mengunogul
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//max macro
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// node structure
typedef struct Node{
    int value;
    int height;
    int position;
    int depthLevel;
    struct Node* leftChild; 
    struct Node* rightChild; 
} node;


// for sorting the nodes by their values in descending order
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

// get height, it is necessary to handle empty childs giving errors
int getHeight(node *curNode) {
  if (curNode == NULL)
    return 0;
  return curNode->height;
}

// right rotate (L/L Case single rotation)
node *rightRotate(node *k2) {
  node *k1 = k2->leftChild;
  node *y = k1->rightChild;

  k1->rightChild = k2;
  k2->leftChild = y;

  // update heights
  k2->height = MAX(getHeight(k2->leftChild), getHeight(k2->rightChild)) + 1;
  k1->height = MAX(getHeight(k1->leftChild), getHeight(k1->rightChild)) + 1;

  return k1;
}

// left rotate (R/R case single rotation)
node *leftRotate(node *k1) {
  node *k2 = k1->rightChild;
  node *y = k2->leftChild;

  k2->leftChild = k1;
  k1->rightChild = y;

  k1->height = MAX(getHeight(k1->leftChild), getHeight(k1->rightChild))+ 1;
  k2->height = MAX(getHeight(k2->leftChild), getHeight(k2->rightChild))+ 1;

  return y;
}

// check balance of nodes
int checkBalance(node *curNode) {
  if (curNode == NULL)
    return 0;
  return getHeight(curNode->leftChild) - getHeight(curNode->rightChild);
}

// Insert node like an AVL tree, nodes are inserted in AVL manner till compelete BST is achieved.
node *insertAVL(node *curNode, node *keyNode) {
  // Find the correct position to insertNode the node and insertNode it
  if (curNode == NULL)
    return keyNode;

  // find the right place to insert the node
  if (keyNode->value < curNode->value)
    curNode->leftChild = insertAVL(curNode->leftChild, keyNode);
  else if (keyNode->value > curNode->value)
    curNode->rightChild = insertAVL(curNode->rightChild, keyNode);
  else
    return curNode;

  // Update the height of the nodes
  curNode->height = MAX(getHeight(curNode->leftChild), getHeight(curNode->rightChild))+1;

  // apply rotations to balance the tree
  int balanceCondition = checkBalance(curNode);
  // L/L case
  if (balanceCondition > 1 && keyNode->value < curNode->leftChild->value)
    return rightRotate(curNode);
  // R/R case
  if (balanceCondition < -1 && keyNode->value > curNode->rightChild->value)
    return leftRotate(curNode);
  // R/L case
  if (balanceCondition > 1 && keyNode->value > curNode->leftChild->value) {
    curNode->leftChild = leftRotate(curNode->leftChild);
    return rightRotate(curNode);
  }
  // L/R case
  if (balanceCondition < -1 && keyNode->value < curNode->rightChild->value) {
    curNode->rightChild = rightRotate(curNode->rightChild);
    return leftRotate(curNode);
  }

  // return new root node
  return curNode;
}

// Insert node like an BST tree, remaining nodes after complete BST are inserted in BST manner.
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


void printOutput(int numberOfFullDepthLevels, int numberOfDepthLevels, int numberOfExcessiveNodes, int remainingNodes, int getCase){
  printf("Output:\n");
  printf("Depth level of BST is %d\n", numberOfDepthLevels);
  // show nodes in depth levels for case 1
  if (getCase == 1){
    int depthLevel;
    for (depthLevel = 0; depthLevel< numberOfFullDepthLevels; depthLevel++){
      printf("Depth level %d -> %d\n", depthLevel, (int)pow(2,depthLevel));
    }
    printf("Depth level %d -> %d\n", depthLevel++, numberOfExcessiveNodes);
    while(remainingNodes>0){
      printf("Depth level %d -> %d\n", depthLevel++, 1);
      remainingNodes--;
    }
  // show depth levels for case 2. (Borrow nodes from Complete BST of the tree.)
  }else if(getCase == 2){
    int depthLevel;
    for (depthLevel = 0; depthLevel< numberOfFullDepthLevels-1; depthLevel++){
      printf("Depth level %d -> %d\n", depthLevel, (int)pow(2,depthLevel));
    }

    // took one node from last full depth level
    // and gave it to excessive depth level (one below of complete binary tree)
    printf("Depth level %d -> %d\n", depthLevel, (int)pow(2,depthLevel)-1);
    printf("Depth level %d -> %d\n", ++depthLevel, numberOfExcessiveNodes=1);
    while(remainingNodes>0){
      printf("Depth level %d -> %d\n", ++depthLevel, 1);
      remainingNodes--;
    }
  }
}
// find the key and update its information about depth and position.
node *findKey(node *currentNode, int key, int position, int depth){
  if(currentNode != NULL){
    if(currentNode->value == key){
      currentNode->position = position;
      currentNode->depthLevel = depth;
      return currentNode;
    }else if (currentNode->value > key){
      return findKey(currentNode->leftChild, key, 2*position-1, depth+1);
    }else if (currentNode->value < key){
      return findKey(currentNode->rightChild, key, 2*position, depth+1);
    }
  }
  return NULL;
}

int main(void){
    FILE *inputFilePtr;
    node* root = NULL;
    int countnodes = 0;
    char currentNumber[11]; // it can read 11 digits at once to represent one number.

    node *arrayOfnodes = calloc(2, sizeof(node));

    // main function gets the dir of input file
    if ((inputFilePtr = fopen("input.txt", "r")) != NULL) {

      // while reading numbers, creates nodes and puts it into an array
      while (fscanf(inputFilePtr, " %10s", currentNumber) == 1)
      {   

          // check if node is less than or equal to zero
          int zeroFL = 0; // flag for node <= 0
          int replicatedFL = 0; // flag for replicated node

          if(atoi(currentNumber) <= 0){
              printf("[ERROR]: Input file contains values less than or equal to zero. %d not inserted to BST.\n", atoi(currentNumber));
              zeroFL = 1;
          }
          // check if replicated node occurs
          for(int i=0; i < countnodes; i++){
              if (arrayOfnodes[i].value == atoi(currentNumber)){
                  printf("[ERROR]: Input file contains replicated keys. %d not inserted to BST.\n", atoi(currentNumber));
                  replicatedFL = 1;
              }
          }
          
          // if no negative value and no replicated key then create the node.
          if (zeroFL == 0 && replicatedFL == 0){
            node newnode;
            newnode.value = atoi(currentNumber);
            newnode.height = 1;
            newnode.position = 1;
            newnode.depthLevel = 0;
            newnode.leftChild = NULL;
            newnode.rightChild = NULL;
            // increase the size of the array
            arrayOfnodes = realloc(arrayOfnodes, countnodes * (sizeof(node)+1));
            arrayOfnodes[countnodes] = newnode; 
            countnodes++;
          }
      }
        
      // check number of nodes, give error if less than 16.
      if (countnodes < 16){
        printf("Input file contains less than 16 elements.\n");
        return -1;
      }

      // sort the array in descending order.
      insertionSort(arrayOfnodes, countnodes);
    
      //check if number of created nodes are power of 2
      int checkCase = ((ceil(log2(countnodes)) == floor(log2(countnodes)))? 2 : 1);
      
      //get the depth level of BST part
      int numberOfFullDepthLevels = (int)floor(log2(countnodes));
      // get total depth levels
      int numberOfDepthLevels = 3*floor(log(countnodes)/log(4));
      // get the number nodes after BST. it is mentioned as Excessive Nodes in the lecture.
      int numberOfExcessiveNodes = countnodes - (int)pow(2, floor(log2(countnodes)))+1-numberOfDepthLevels+numberOfFullDepthLevels+1;
      // get the remaining nodes considering calculations above
      int remainingNodes = countnodes-(int)pow(2, numberOfFullDepthLevels)+1-numberOfExcessiveNodes;
      printOutput(numberOfFullDepthLevels, numberOfDepthLevels, numberOfExcessiveNodes, remainingNodes, checkCase);

      //check if it is case 1 or case 2.
      if(checkCase == 1){
        //case 1
        int i, j;
        for (i = 0; i < countnodes-remainingNodes; i++){
            root = insertAVL(root, &arrayOfnodes[i]);
        }

        for (j = 0; j < remainingNodes; j++)
        {
            insertBST(root, &arrayOfnodes[i+j]);
        }

      } else {
        // case 2
        int i, j;
        // take one node from Compelete BST
        for (i = 0; i < countnodes-remainingNodes-1; i++){
            root = insertAVL(root, &arrayOfnodes[i]);
        }
        // give it to lower level
        for (j = 0; j < remainingNodes+1; j++)
        {
            insertBST(root, &arrayOfnodes[i+j]);
        }
      }

      //find key section
      int input = 1;
      while(input > 0){
        printf("\nKey value to be searched (Enter 0 to exit) :");
        scanf("%d", &input);
        node *keyNode = findKey(root, input, 1, 0);
        if(input <= 0){
          printf("Exit\n");
          return -1;
        }else if(keyNode == NULL && input != 0){
          printf("%d is not found in BST", input);
        }else{
          printf("At Depth level %d, %d. element", keyNode->depthLevel, keyNode->position);
        } 
      }
    }
    free(arrayOfnodes);
    return 0;
}