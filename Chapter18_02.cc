/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_02
 * Write a function, char* findx(const char* s, const char* x) , that finds the
 * first occurrence of the C-style string x in s . Do not use any standard li-
 * brary functions. Do not use subscripting; use the dereference operator *
 * instead.
 * -----------------------------------------------------------------------------
 */


#include <iostream>
#include <cstring>

unsigned int my_strlen(const char *s);

char* findx(const char *s, const char *x){
    if (my_strlen(x) > my_strlen(s)) return nullptr;

    //Otherwise, go through this O(N^2) function
    bool valid;
    char *pointer = (char *) s;
    
    for (pointer; *pointer; pointer++){
		char *p1 = pointer;
		valid = true;
		for (char *p2 = (char *) x; *p2; p2++){
			if (*(p1++) == *(p2))
				continue;
			else {
				valid = false;
				break;
			}
		}
	
		if (valid) return pointer;
    }
    
    return nullptr; // If not found.

}

unsigned int my_strlen(const char *s){
    char *p = (char *) s;
    
    for (p; *p; p++)
		continue;

    return (unsigned int)(p - s);
}

int main(void){
    const char *string01 = "Hello World!?";
    const char *test = "Hello World!";

    char *result = findx(string01, test);
    
    std::cout << "Is the string \"" << test << "\" in the string \""
			  << string01 << "\" ? ";
    if (result == nullptr)
		std::cout << "NOPE\n";
    else
		std::cout << "Yes, at location " << &result << "\n";
	

}
