#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

int main() {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir("/")) == NULL)
        perror("opendir() error");
    else {
        puts("contents of root:");
        while ((entry = readdir(dir)) != NULL)
            printf("  %s\n", entry->d_name);
        closedir(dir);
    }
}