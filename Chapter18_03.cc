/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_03 
 * 
 * Write a function, int strcmp(const char* s1, const char* s2) , that compares
 * C-style strings. Let it return a negative number if s1 is lexicographically
 * before s2 , zero if s1 equals s2 , and a positive number if s1 is lexicograph-
 * ically after s2 . Do not use any standard library functions. Do not use
 * subscripting; use the dereference operator * instead.
 * -----------------------------------------------------------------------------
 */

#include <cstdio>
unsigned int my_strlen(const char *s){
    char *p = (char *) s;
    
    for (p; *p; p++)
		continue;

    return (int)(p - s);
}


int strcmp(const char *s1, const char *s2){
    char *p1 = (char *)s1;
    char *p2 = (char *)s2;

    for (; *p1 && *p2; p1++, p2++){
		if (*(p1) < *(p2)) return -1; // Before
		else if (*(p1) > *(p2)) return 1; // After
		else
			continue;
    }

    // Now compare str_lengths
    // If s1 is shorter than s2, and they are mostly similar,
    // s1 is before s2.
    if (my_strlen(s1) < my_strlen(s2)) return -1;
    else return 0;

}


int main(void){
    char *string01 = "Hello";
    char *string02 = "Helloe";
    int result = strcmp(string01, string02);
    printf("Result of Comparing %s and %s: %d\n", string01, string02, result);

}
