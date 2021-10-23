#include <stdio.h>

int main(void){
    int number = 8;
    printf("%d", (number /= 10)%10);
    // while(number > 0){
    //     printf("%d", number%10);
    //     number /= 10;
    // }
    return 0;
}