/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_01
 *
 * Write a function, char* strdup(const char*) , that copies a C-style string
 * into memory it allocates on the free store. Do not use any standard li-
 * brary functions. Do not use subscripting; use the dereference operator *
 * instead.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <cstring>

char* stdup(const char *str){
    char *pointer = const_cast<char*>(str);
    // char *pointer = (char *)str; // C-style cast
    int length;
    for (pointer; *pointer; pointer++)
		continue;
    
    length = (pointer - str);

    char *temp = new char[length];
    for (int i = 0; i < length; i++)
		*(temp + i) = *(str + i);

    return temp;
}


int main(void){
    char *test = "Hello World!";
    
    char *string0 = stdup(test);

    std::cout << string0 << std::endl;

    return 0;
}
