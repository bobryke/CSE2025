#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


int main(void){
    // get keyword
    char keyword[100];
    printf("Enter a keyword: ");
    scanf("%s", keyword);

    // open folder and read files
    DIR *d;
    FILE *documentPtr;
    struct dirent *dir;
    d = opendir("./files");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char input[500], directory[50];
            int keywordCount = 0;
            sprintf(directory,"./files/%s", dir->d_name); // make a full path to file

            if ((documentPtr = fopen(directory, "r")) !=NULL) {
                printf("%s: ",dir->d_name);

                while (fscanf(documentPtr, "%s", input) != EOF){
                    int index = 0;
                    for(;index<strlen(input);index++ ){
                        input[index] = tolower(input[index]); // All characters lowered.
                    }
                    if(ispunct(input[strlen(input)-1])){ // delete punctuation if there is at end of word.
                        input[strlen(input)-1] = '\0';
                    }

                    if(strcmp(keyword, input) == 0){
                        keywordCount++;
                    }
                }
                printf("%d \n", keywordCount);
                keywordCount = 0;
            }
        }
        closedir(d);
    }

    return 0;
}