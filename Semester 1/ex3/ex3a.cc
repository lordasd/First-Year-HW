/* Ex3a: Average calculation and pos/neg number counting
*=======================================================
* Written by David Zaydenberg
*
* Program reads inputs of integer numbers until 0 is entered.
* It calculates how much numbers were entered,
* the average of the numbers and how many
* positive and negative numbers were entered.
*/

//----include section----
#include <iostream>

//----using section------
using std::cout;
using std::cin;
using std::endl;

//----main-------
int main(){

    int input, avg = 0, pos=0, neg=0; //Info variables that we want to collect
    int counter = 0; //Amount of numbers var

    cin >> input; //First input before loop

    while(input != 0){
        avg += input; //Adding up inputs to the total of the average numbers
        counter++; //Counting the amount of inputs/numbers
        if(input >= 0){//Checking if the number positive/negative
            pos++;
        }
        else{
            neg++;
        }
        cin >> input; //Continue input
    }
    avg = avg / counter; //Calculating average number
    //Print of the result
    cout << counter << " " << avg << " " << pos << " " << neg << endl;

    return EXIT_SUCCESS;
}