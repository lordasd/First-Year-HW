#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 5;

void rotate_rec(int arr[]);
void rotate(int arr[], int index);

int main(){

    int arr[N] = {1, 2, 3, 4, 5};

    rotate_rec(arr);

    for(int i = 0; i < N; i++){
        cout << arr[i] << " ";
    }

    return EXIT_SUCCESS;
}

//Function gets array of numbers and 
//sends them to rotate function to move
//each number forward.
void rotate_rec(int arr[]){
    //index for the array.
    int index;
    rotate(arr, 0);
}

//rorate moves each number forward+last number goes
//back to first.
void rotate(int arr[], int index){
    int temp;
    if(index < N-1){
        temp = arr[N-1];
        arr[N-1] = arr[index];
        arr[index] = temp;
        //move to the next index.
        rotate(arr, index+1);
    }
}