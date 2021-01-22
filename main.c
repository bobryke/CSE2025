#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main(void){
    DIR *d;
    struct dirent *dir;
    d = opendir("./files");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return 0;
}