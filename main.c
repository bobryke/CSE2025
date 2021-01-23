#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>


typedef struct heapNode {
    char docName[50];
    int value;
}heapNode;

void swap(heapNode *parent, heapNode *child)
{
    heapNode temp = *parent;
    *parent = *child;
    *child = temp;
}

void increaseKey(heapNode *arr,int index){
    int parent = (index-1)/2;
    int leftChild = (index*2)+1;
    int rightChild = (index*2)+2;
    //printf("parent %d, left %d, right %d\n", parent, leftChild, rightChild);
    if (parent >= 0 || index > 0){
        if(arr[index].value > arr[parent].value){
            swap(&arr[parent], &arr[index]);
            increaseKey(arr, parent);
        }
    }
}

void decreaseKey(heapNode *arr,int index, int lastElement){
    int parent = (index-1)/2;
    int leftChild = (index*2)+1;
    int rightChild = (index*2)+2;
    //printf("parent %d, left %d, right %d\n", parent, leftChild, rightChild);
    if(leftChild <= lastElement && rightChild <= lastElement){
        if(arr[leftChild].value > arr[rightChild].value){
            swap(&arr[index], &arr[leftChild]);
            decreaseKey(arr, leftChild, lastElement);
        }else{
            swap(&arr[index], &arr[rightChild]);
            decreaseKey(arr, leftChild, lastElement);
        }
    }else if(leftChild <= lastElement){
        swap(&arr[index], &arr[leftChild]);
        decreaseKey(arr, leftChild, lastElement);

    }else if(rightChild <= lastElement){
        swap(&arr[index], &arr[rightChild]);
        decreaseKey(arr, leftChild, lastElement);
    }
}

void removeKey(heapNode *arr,int index, int *lastElement){
    swap(&arr[(*lastElement)], &arr[index]); // last element and indexed elements are swapped.
    (*lastElement)--; // since int lastElement at the same time represents the size of the array, it is decremented by one.
    decreaseKey(arr, index,  (*lastElement));
}

void insertNode(char *name, int value, heapNode *arr, int index){
    strcpy(arr[index].docName, name);
    arr[index].value = value;
    increaseKey(arr, index);
}

void printTopFive(heapNode *arr){
    printf("The relevance order is: ");
    FILE *documentPtr;
    char input[500], docPath[50];
    int index = 0;
    for(; index < 5; index++){
        if(arr[index].value > 0) printf("%s(%d), ", arr[index].docName, arr[index].value);
    }
    printf("\n");
    for(index = 0; index < 5; index++){
        if(arr[index].value > 0) {
            printf("%s(%d): ", arr[index].docName, arr[index].value);
            sprintf(docPath,"./files/%s", arr[index].docName); // make a full path to file
            if ((documentPtr = fopen(docPath, "r")) !=NULL) {
                while (fscanf(documentPtr, "%s", input) != EOF){
                    printf("%s ", input);
                }
            }
            printf("\n\n");
        }
    }
}
int main(void){
    // get keyword
    char keyword[100];
    printf("Enter a keyword: ");
    scanf("%s", keyword);

    heapNode heapArray[50];
    // open folder and read files
    DIR *d;
    FILE *documentPtr;
    struct dirent *dir;
    d = opendir("./files");
    if (d)
    {
        int docIndex = 0;
        while ((dir = readdir(d)) != NULL)
        {
            char input[500], directory[50];
            int keywordCount = 0;
            sprintf(directory,"./files/%s", dir->d_name); // make a full path to file

            if ((documentPtr = fopen(directory, "r")) !=NULL) {
               if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) continue;// skip parent and current directory sign.

                while (fscanf(documentPtr, "%s", input) != EOF){
                    int charIndex = 0;
                    for(;charIndex<strlen(input);charIndex++ ){
                        input[charIndex] = tolower(input[charIndex]); // All characters lowered for read words
                    }
                    for(charIndex = 0;charIndex<strlen(keyword);charIndex++ ){
                        keyword[charIndex] = tolower(keyword[charIndex]); // All characters lowered for keyword
                    }
                    if(ispunct(input[strlen(input)-1])){ // delete punctuation if there is at end of word.
                        input[strlen(input)-1] = '\0';
                    }
                    //printf("%s ", input);
                    if(strcmp(keyword, input) == 0){
                        keywordCount++;
                    }
                }
                insertNode(dir->d_name, keywordCount, heapArray, docIndex);
                keywordCount = 0;
                docIndex++;
            }
        }
        closedir(d);
    }
    printTopFive(heapArray);
    return 0;
}