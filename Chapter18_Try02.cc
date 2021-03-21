/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 01/15/2020
 * 
 * Chapter18 Try02
 * -----------------------------------------------------------------------------
 */

#include <iostream>
#include <new>
#include <cstdio>
using namespace std;

class vector{
    int size;
    double *elem;
public:
    explicit vector (int size){
		this->size = size;
		elem = new double[size];

    }
    
    vector(initializer_list<double> list):
		size{list.size()}, elem{new double[size]}{
	    copy(list.begin(), list.end(), elem);
	}
    
    double& operator[](int n){ return elem[n];}

    ~vector(){
		delete[] elem;
    }

    int length(){ return size;}
};


int main(void){
    vector temp = {3, 2, 1};
    temp[0] = 1;
    temp[1] = 2;
    temp[2] = 3;

    for (int i = 0; i < temp.length(); i++)
		cout << "temp[" << i << "] : " << temp[i]
			 << "\n";

    return 0;
}
