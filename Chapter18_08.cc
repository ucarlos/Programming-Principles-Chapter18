/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/19/2020
 * 
 * Chapter18_08
 * Rewrite all the functions in §18.7 to use the approach of making a back-
 * ward copy of the string and then comparing; for example, take "home" ,
 * generate "emoh" , and compare those two strings to see that they are
 * different, so home isn’t a palindrome
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include <new>
#include <sstream>
#include <cstring>
using namespace std;

bool is_palindrome(const string &s){
    /// radar
    stringstream os;

    for (int i = s.length() - 1; i >= 0; i--){
        os << s[i];
    }

    return (os.str() == s);
}


bool is_palindrome(const char s[], int n){
    char test[n];
    
    for (int i = 0; i < n; i++)
	test[i] = s[n - 1 - i];


    return (!strncmp(s,test, n)); 
}


bool is_palindrome(const char *first, const char *last){
    char *test = new char[strlen(first)];

    char *p1 = test;
    for (char *p = (char *)last; p >= first; p--)
	*(p1++) = *(p);

    return (!strncmp(first, test, strlen(first)));

}


int main(void){
    cout << boolalpha;
    cout << "Results of testing \"Home\" (String): " << is_palindrome("Home") << endl;
    cout << "Results of testing \"Radar\" (String): " << is_palindrome("radar") << endl;
    

    const char test01[] = "Home";
    const char test02[] = "radar";
    
    int test01_len = strlen(test01);
    int test02_len = strlen(test02);


    cout << "Results of testing \"Home\" (Char 1): "
	 << is_palindrome(test01, test01_len)
	 << "\n";
    
    cout << "Results of testing \"Radar\" (Char 1): "
	 << is_palindrome(test02, test02_len)
	 << "\n";
    
    cout << "Results of testing \"Home\" (Char 2): "
	 << is_palindrome(test01, (test01 + test01_len - 1))
	 << "\n";
    
    cout << "Results of testing \"Radar\" (Char 2): "
	 << is_palindrome(test02, (test02 + test02_len - 1))
	 << "\n";
    


}
