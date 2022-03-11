#include <iostream>

const int N = 10;

bool find_sum(const int arr[], int number, int &i1, int &i2);

int main(){

    int arr[N] = {1 , 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i1, i2;
    int number = 19;

    if(find_sum(arr, number, i1, i2)){
        std::cout << "Yes" << std::endl;
        std::cout << i1 << " " << i2 << std::endl;
    }
    else{
        std::cout << "No";
    }

    return EXIT_SUCCESS;
}

//Runtime is O(N^2) - Worst case scenario it will run over the whole
//array to try and find the pair and get to the end which is N-1 and N-1 indexes.
bool find_sum(const int arr[], int number, int &i1, int &i2){

    //arr[i] number to try and sum up with the arr[j] number.
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            //if we found the first pair, save indexes and quit the function.
            if(arr[i] + arr[j] == number){
                i1 = i;
                i2 = j;
                return true;
            }
        }
    }
    return false;
}