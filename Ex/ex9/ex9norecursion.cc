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
bool validity_check(int num);

//-------------Int main-------------//
int main(){

    //Starts from the highest number.
    long long num = 987654321;
    
    //Goes down until finds the highest number that divides by 11.
    for(int i = num; num >= 123456789; num--){
        //Checking validity for 9 different digits
        if(validity_check(num)){
            if(num % 11 == 0){
                cout << num << endl;
                break;
            }
        }
    }
}

//Validates if all 9 digits are different.
//-----------Validity_Check--------------//
bool validity_check(int num){
    int array[N] = {0};
    int i, j;
    int count;
    long long temp = num;

    //Prepares an array to compare to the number.
    for(i = N-1; i >= 0; i--){
        array[i] = temp % 10;
        temp /= 10;
    }
    //Copys num to temp to make changes
    temp = num;
    for(i = N-1; i >= 0; i--){
        count = 0;
        for(j = N-1; j >= 0; j--){
            if(temp%10 == array[j]){
                count++;
            }
        }
        //If there are 2 or more same number, send false.
        if(count >= 2){
            return false;
        }
        temp /= 10;
    }
    return true;
}