/* Ex3c: Natural Roots 
*==================================
* Written by David Zaydenberg
*
* This program takes an input of a number and searches for numbers
* that are powered by 2-9 which gives the closest number to the input,
* from the highest to lowest.
*/

//-----include section------
#include <iostream>

//----using section------
using std::cout;
using std::cin;
using std::endl;

//---main section-----
int main(){

    //input and calculation var integers
    int input, total, numresult = 0;
    //numberholders
    int mainholder, seconderyholder;
    //indexes for the loops
    int i, j, k;

    cin >> input;

    if(input >= 0){
        //main loop to get 9 different options for power
        for(j = 2; j <= 9; j++){
            mainholder = input; /*holder holds default number each time
            and waits to be changed*/

            /*middle loop for all the calculations
            and searching for apropriate numbers*/
            for(i = input; i >= 1; i--){
                total = i; /*each time starts from one "i" so the inner loop
                can do the calculation again for the apropriate power*/
                for(k = 2; k <= j; k++){//inner loop for the power calculation
                    total *= i;
                }
                /*calculates the substraction and makes sure the number is 
                positive and inserts into a holder*/
                if(input-total >= 0){
                    seconderyholder = input-total;
                }
                /*exactly the same the other
                way if the total is bigger than the input*/
                else if(total-input >= 0){
                    seconderyholder = total-input;
                }
                //inseartion into the mainholder if secondery is bigger.
                if(seconderyholder < mainholder){
                    mainholder = seconderyholder;
                    //"i" of the holder becomes the number we search for
                    numresult = i;
                }
            }
            cout << numresult << " ";
        }
    }
    cout << endl;
    
    return EXIT_SUCCESS;
}