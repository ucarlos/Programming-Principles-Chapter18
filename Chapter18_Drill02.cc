#include <iostream>
#include <new>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> gv = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};

void function_f(vector<int> list){
    vector<int> lv(gv.size());
    std::copy(gv.begin(), gv.end(), lv.begin());
    for (int i : lv)
	cout << i << " " ;
    cout << endl;

    vector<int> lv2(list.size());
    std::copy(list.begin(), list.end(), lv2.begin());

    for (int i : lv2)
	cout << i << " ";
    cout << endl;
    

}

int factorial(int n){
    if (n < 0) return -1; // Not possible.
    int val = 1; // For 0!

    for (int i = n; i > 0; i--)
	val *= i;

    return val;
}


int main(void){
    function_f(gv);
    
    vector<int> vv(10);

    for (int i = 0; i < vv.size(); i++)
        vv[i] = factorial(i);

    function_f(vv);

}
