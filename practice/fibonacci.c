#include <stdio.h>
#include <stdlib.h>

//recursive fibonacci function
int fib(int number){
    if(number == 0){
        return 0;
    }else if (number == 1){
        return 1;
    }else{
        printf("%d\n", number);
        return (fib(number-1) + fib(number-2));        
    } 
}

//recursive fibonacci function implemented with cache
int fib_with_cache(int number, int* cache){
    if(number == 0){
        return 0;
    }else if (number == 1){
        return 1;
    }else if(cache[number] != 0){
        return cache[number];
    }else{
        cache[number] = (fib_with_cache(number-1, cache) + fib_with_cache(number-2, cache));
        return cache[number];
    } 
}

int main(void){
    int i, number, result;
    number = 500;
    int *cache = calloc(number, sizeof(int));
    result = fib(number);
    // for(i = 1; i<=number; i++){
    //     if (cache[i] == 0){
    //         cache[i] = cache[i-1]+cache[i-2];
    //     }else{
    //         result += cache[i];
    //     }
    // }
    printf("\nresult: %d", result);
    return 0;
}