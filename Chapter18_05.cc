/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/18/2020
 * 
 * Chapter18_05
 *
 * Write a function, string cat_dot(const string& s1, const string& s2) ,
 * that concatenates two strings with a dot in between. For example, cat_
 * dot("Niels", "Bohr") will return a string containing Niels.Bohr .
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>


using namespace std;

string cat_dot(const string &s1, const string &s2){
    return s1 + "." + s2;
}


int main(void){
    string s1  = "Niels";
    string s2 = "Bohr";
    string s3 = cat_dot(s1, s2);

    cout << "String01: " << s1 << "\nString02: " << s2
         << "\nString03: " << s3 << endl;


}
