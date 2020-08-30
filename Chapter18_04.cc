/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Consider what happens if you give strdup() , findx() , and strcmp() an argu-
 * ment that is not a C-style string. Try it! First figure out how to get a
 * char* that doesn’t point to a zero-terminated array of characters and then
 * use it (never do this in real — non-experimental — code;
 * it can create havoc). Try it with free-store-allocated and stack-allocated
 * “fake C-style strings.” If the results still look reasonable, turn off debug
 * mode. Redesign and re-implement those three functions so that they take
 * another argument giving the maximum number of elements allowed in argument
 * strings. Then, test that with correct C-style strings and “bad” strings.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
using namespace std;

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


unsigned int my_strlen(const char *s){
    char *p = (char *) s;
    
    for (p; *p; p++)
	continue;

    return (int)(p - s);
}

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

void test_problem01(void){
// Testing Problem 01 with Char array:
    cout << "Testing with a char array (without null character)" << endl;
    char str[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    char *temp = stdup(str);
    cout << temp << endl;
    cout << "Now Testing with allocated array" << endl;

    char *string02 = new char[13]{'H', 'e', 'l', 'l', 'o'
				 , ' ', 'W', 'o', 'r', 'l', 'd', '!', '?'};

    char *temp2 = stdup(string02);
    cout << temp2 << endl;
    delete[] temp;
    delete[] string02;

}

void test_problem02(void){

    cout << "Testing with a char arrays allocated on stack and heap" << endl;
    char str[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};

    char *string02 = new char[12]{'H', 'e', 'l', 'l', 'o'
            , ' ', 'W', 'o', 'r', 'l', 'd', '!'};


    char *result = findx(str, string02);

    std::cout << "Is the string \"" << str << "\" in the string \""
              << string02 << "\" ? ";
    if (result == nullptr)
        std::cout << "NOPE\n";
    else
        std::cout << "Yes, at location " << &result << "\n";

    delete[] string02;



}

void test_problem03(void){

    cout << "Testing with a char arrays allocated on stack and heap" << endl;
    char str[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'};

    char *string02 = new char[12]{'H', 'e', 'l', 'l', 'o'
				 , ' ', 'W', 'o', 'r', 'l', 'd', '!'};

    
    int result = strcmp(str, string02);
    cout << "Result: " << result << "\n";
    delete[] string02;



}


int main(void){
    cout << "\nProblem 01 ---" << endl;
    test_problem01();
    cout << "\nProblem 02 ---" << endl;
    test_problem02();
    cout << "\nProblem 03 ---" << endl;
    test_problem03();

    cout << "\nSo it seems that Problem01 works, but Problem02 and Problem03 are broken because of it.";
    
}



