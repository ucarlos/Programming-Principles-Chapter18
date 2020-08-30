#include <iostream>
#include <new>
#include <cstdlib>
#include <cstdio>

int ga[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
#define GA_SIZE (10)

void function_f(int *list, int list_length){
    int la[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("Printing out values of la:\n");
    for (int i = 0; i < list_length; i++){
	la[i] = ga[i];
	printf("%d ", la[i]);
    }
    puts("");
    
    int *list2 = new int[list_length];
    printf("Now printing out list2:\n");
    for (int i = 0; i < list_length; i++){
	list2[i] = list[i];
	printf("%d ", list2[i]);
    }
    
    puts("");
    
    delete[] list2;
    
}

int factorial(int n){
    if (n < 0) return -1; // Not possible.
    int val = 1; // For 0!

    for (int i = n; i > 0; i--)
	val *= i;

    return val;
}

int main(void){
    function_f(ga, GA_SIZE);
    int *list = new int[GA_SIZE];
    
    for (int i = 0; i < GA_SIZE; i++)
	list[i] = factorial(i);

    function_f(list, GA_SIZE);

}
