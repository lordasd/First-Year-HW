/* Ex9a: Max 9 digit divide by 11
*==================================
* Written by David Zaydenberg
*
* Program is searching for the highest 9 different digits number
* that can be divided by 11. We start with an array with 9 values
* 9,8,7,6,5,4,3,2,1 as the highest starting point that we can have.
* We go down until we find the highest number that has 9 different
* digits and can be divided by 11.
* 
* Main calls a boolian(divide_check) to check if a number is valid
* and divides by 11. If it comes back true, it prints the number.
* 
* divide_check - Calls for validity_check to check if the number
* is valid(9 different digits). Then calls for oddeven_sum to check
* if the number is divded by 11. If any of these two fails, it calls
* for subtract func, to subtract -1 from the number.
* 
* subtract - transforms the array of numbers to long long variable
* to subtract 1 from it, and then it transforms it back to call 
* divide_check recursively.
*
* OddEven_sum - If subtraction of the sum of odd indexes and sum of even
* indexes is divided by 11 > whole number can be divided by 11.
*
* Validity_check - creates a new array to compare to. saves all the values
* from the original array and compares. if there are more then 1 same values
* in the array, the array is invalid and it needs to return false and go
* to subtract function.
*
*==================================*/
//-------Include Section---------//
#include <iostream>
#include <cstdlib>

//-----------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//--------Const Section----------//
const int N = 9;

//---------------Prototype Section---------------//
bool divide_check(int arr[]);
int oddeven_sum(int const arr[], int &oddsum, int &evensum);
void subtract(int arr[]);
bool validity_check(const int arr[]);

/*calls a boolian(divide_check) to check if a number is valid
and divides by 11. If it comes back true, it prints the number.*/
//-------------Int main-------------//
int main(){

    int arr[N] = {9,8,7,6,5,4,3,2,1};

    if(divide_check(arr)){
        cout << "SUCCESS: ";
        for(int i = 0; i < N; i++){
            cout << arr[i];
        }
        cout << endl;
    }

    return EXIT_SUCCESS;
}

/*Calls for validity_check to check if the number
is valid(9 different digits). Then calls for oddeven_sum to check
if the number is divded by 11. If any of these two fails, it calls
for subtract func, to subtract -1 from the number.*/
//---------------Divide_check------------------//
bool divide_check(int arr[]){
    int oddsum = 0;
    int evensum = 0;
    int res;

    if(validity_check(arr)){
        if((res = oddeven_sum(arr, oddsum, evensum)) % 11 == 0 &&
                res != 0){
            return true;
        }
    }
    subtract(arr);
    return true;
}

/*transforms the array of numbers to long long variable
to subtract 1 from it, and then it transforms it back to call 
divide_check recursively.*/
//------------Subtract-------------//
void subtract(int arr[]){
    int i,j;
    long long num = 0;

    //Transform array to long lon
    for(i = 0; i < N; i++){
        num += arr[i];
        if(i == N-1){
            break;
        }
        num *= 10;
    }
    //subtract -1 from the number
    num--;
    //Transform the number back to an array.
    for(j = N-1; j >= 0; j--){
        arr[j] = num % 10;
        num /= 10;
    }
    divide_check(arr);
}
/*If subtraction of the sum of odd indexes and sum of even
indexes is divided by 11 > whole number can be divided by 11.*/
//------------------OddEven_sum----------------------//
int oddeven_sum(int const arr[], int &oddsum, int &evensum){
    for(int i = 0; i < N; i++){
        if(i % 2 == 0){
            evensum += arr[i];
        }
        else{
            oddsum += arr[i];
        }
    }
    return oddsum - evensum;
}

/*creates a new array to compare to. saves all the values
from the original array and compares. if there are more then 1 same values
in the array, the array is invalid and it needs to return false and go
to subtract function.*/
//-----------Validity_Check--------------//
bool validity_check(const int arr[]){
    int array[N] = {0};
    int i, j;
    int count;

    for(i = 0; i < N; i++){
        array[i] = arr[i];
    }
    
    for(i = 0; i < N; i++){
        count = 0;
        for(j = 0; j < N; j++){
            if(arr[i] == array[j]){
                count++;
                if(count >= 2){
                    return false;
                }
            }
        }
    }
    return true;
}
