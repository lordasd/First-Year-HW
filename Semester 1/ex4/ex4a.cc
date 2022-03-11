/* Ex4a: Divides the left and divides by the right 
*==================================
* Written by David Zaydenberg
*
* This program inputs 6 numbers into a 1D Array and searches
* for a number that can divide the left number without modulu and be
* divided by the right number without modulu and tells how many of them.
*/

//-----include section------//
#include <iostream>
#include <cstdlib>

//-----const section--------//
const int ARRAY = 6;

//-----using section--------//
using std::cout;
using std::cin;
using std::endl;

//-----main section---------//
int main(){

    int input[ARRAY];
    int i, counter = 0;

    //for loop for input into the 1d array.
    for(i = 0; i < ARRAY; i++){
        cin >> input[i];
    }
    for(i = 0; i < ARRAY; i++){
        //if the number is not on the sides, continue
        if(i > 0 && i < ARRAY-1){
            //Checks if the value is 0, because the number cant
            //be devided by 0.
            if(input[i-1] != 0 && input[i] != 0){
                //the math for the left and right numbers
                if((input[i]%input[i-1] == 0) && (input[i+1]%input[i] == 0)){
                    counter++;//counter for the amount we found
            }
            }
            
        }
    }
    cout << counter << endl;

    return EXIT_SUCCESS;
}
