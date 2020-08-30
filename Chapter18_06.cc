/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_06
 * Modify cat_dot() from the previous exercise to take a string to be used as
 * the separator (rather than dot) as its third argument.
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>

using namespace std;

string cat_dot(const string &s1, const string &seperator, const string &s2){
    return s1 + seperator + s2;
}


int main(void){
    string s1  = "Niels";
    string s2 = "Bohr";
    string s3 = cat_dot(s1,".", s2);

    cout << "String01: " << s1 << "\nString02: " << s2
         << "\nString03: " << s3 << endl;


}
