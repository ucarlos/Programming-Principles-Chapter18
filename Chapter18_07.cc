/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_07
 * Write versions of the cat_dot() s from the previous exercises to take
 * C-style strings as arguments and return a free-store-allocated C-style string
 * as the result. Do not use standard library functions or types in the im-
 * plementation. Test these functions with several strings. Be sure to free
 * (using delete ) all the memory you allocated from free store (using new ).
 * Compare the effort involved in this exercise with the effort involved for
 * exercises 5 and 6.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstdio>
#include <new>
using namespace std;


unsigned int my_strlen(const char *s){
    char *p = (char *) s;
    
    for (p; *p; p++)
	    continue;

    return (unsigned int)(p - s);
}

char * cat_dot(const char *str1, const char *str2){
    int str1_len = my_strlen(str1);
    int str2_len = my_strlen(str2);

    char *concat = new char[str1_len + str2_len + 1];
    
    for (int i = 0; i < str1_len; i++)
	    concat[i] = str1[i];

    concat[str1_len] = '.';
    
    for (int i = 0; i < str2_len; i++){
	    concat[str1_len + 1 + i] = str2[i];
    }
    
    return concat;

}

char * cat_dot(const char *str1, const char *seperator, const char *str2){
    int str1_len = my_strlen(str1);
    int str2_len = my_strlen(str2);
    int sep_len = my_strlen(seperator);
    
    char *concat = new char[str1_len + str2_len + sep_len];
    
    for (int i = 0; i < str1_len; i++)
	    concat[i] = str1[i];

    for (int i = 0; i < sep_len; i++){
	    concat[str1_len + i] = seperator[i];
    }
    
    for (int i = 0; i < str2_len; i++){
	    concat[str1_len + sep_len + i] = str2[i];
    }
    
    return concat;
    
}

int main(void){
    const char *string01 = "Niel";
    const char *string02 = "Bohr";
    const char *string03 = cat_dot(string01, string02);
    cout << "Combining \"" << string01 << "\" and \""
	 << string02 << ": \""
	 << string03 << "\"\n";

    
    const char *string04 = "Donald";
    const char *string05 = "Trump";
    const char *string06 = cat_dot(string04, " J. ", string05);

    cout << "Combining \"" << string04 << "\" and \""
	 << string05 << "\" : \"" << string06 << "\"\n";
    
    delete[] string03;
    delete[] string06;

}
