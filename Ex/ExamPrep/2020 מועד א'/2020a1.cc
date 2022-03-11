#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 6;

bool is_num_in_arr(const char arr[], int num);

int main(){

    char arr[N] = {'a', '7', 'b', '8', '3', 'c'};
    int num = 73;

    if(is_num_in_arr(arr, num)){
        cout << "Yes!" << endl;
    }
    else{
        cout << "No!" << endl;
    }

    return EXIT_SUCCESS;
}

//Checks if the pattern of num is in the array.
//other values in between won't matter.
//Runtime O(N) because it goes over the whole array.
bool is_num_in_arr(const char arr[], int num){

    int temp_num = num;

    for(int i = N-1; i >= 0; i--){
        if(arr[i] - '0' == temp_num % 10){
            temp_num /= 10;
        }
        if(temp_num == 0){
            return true;
        }
    }

    return false;
}