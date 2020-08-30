//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 1/26/20 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------

#include <iostream>
#include <new>
#include <random>
using namespace std;

void generate_rand_number(int *num_list, const int list_length, int value){

    static std::random_device rd;
    static std::mt19937 gen(rd());
    uniform_int_distribution<> dis(0, value);
    for (int i = 0; i < list_length; i++){
        num_list[i] = dis(gen);
    }

}

int main(void){
    int length = 5;
    int *list = new int[length];
    generate_rand_number(list, length, 10);
    for (int i = 0; i < length; i++)
        cout << list[i] << " ";
    cout << endl;
    return 0;
}