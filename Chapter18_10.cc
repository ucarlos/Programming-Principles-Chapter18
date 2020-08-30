/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/19/2020
 * 
 * Chapter18_10
 * Look at the “array solution” to the palindrome problem in §18.7.2. Fix it
 * to deal with long strings by (a) reporting if an input string was too long
 * and (b) allowing an arbitrarily long string. Comment on the complexity
 * of the two versions.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <cstring>
#include <new>
#include <sstream>
#include <stdexcept>
using namespace std;
constexpr int max_chars = 256; // Can be aributary at this point.

bool is_palindrome(const char s[], int len){
    // Same implementation as in the book
    int first = 0;
    int last = len - 1;
    while (first < last){
        if (s[first] != s[last]) return false;
        first++;
        last--;
    }
    
    return true;
}




istream& read_word(istream &is, char *buffer, int max){
    // Read at most max - 1 characters from is into buffer
    is.width(max);
    is >> buffer;
    
    return is;

}

void solution1(void){ // This isn't a good solution.
    // First, write to os, and check the size. If the size is larger than
    // max_char, flush, and print error message. Otherwise, proceed.
    char s[max_chars];
    string temp;
    cin >> temp;
    if (temp.length() + 1 > max_chars){
        ostringstream oss;
        oss << "String Exceeded the max character limit of "
            << max_chars << " characters.\n";
        throw length_error(oss.str());
    }
    else {
        temp.append("\0");
        copy(temp.begin(), temp.end(), s);
        // Now call the function
        bool result = is_palindrome(s, temp.length());
        cout << boolalpha;
        cout << "\"" << s << "\" is a palindrome? : ";
        cout << result << endl;
    }
   

}

void solution2(void){
    string temp;
    cin >> temp;
    temp.append("\0");
    char *c_string = new char[temp.length()];
    copy(temp.begin(), temp.end(), c_string);
    bool result = is_palindrome(c_string, temp.length());
    cout << boolalpha;
    cout << "\"" << temp.c_str() << "\" is a palindrome? : ";
    cout << result << endl;



}

int main(void){
    cout << "Solution 1...\n";
    solution1();
    cout << "Solution 2...\n";
    solution2();

    return 0;


}
