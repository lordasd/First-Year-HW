/* Ex3b: Finding a pair of numbers 
*==================================
* Written by David Zaydenberg
*
* This program calculates how many pair of numbers that are the sum of
* power 2 equals to a number powered 3 and the oposite - the same pair
* of numbers that are the sum of power 3 equals to a number powered 2.
*/
//-----inlucde section-----
#include <iostream>

//-----using section-----
using std::cout;
using std::cin;
using std::endl;

//------main section------
int main(){

    int pwr2, pwr3, totalpwr2, totalpwr3; //Variables of the powers
    int nmpwr2, nmpwr3; //Variables for the sum of powers
    int condpwr2, condpwr3; //2 condition variables

    /*We seperate pwr3 & pwr2 for 2 loops to
    get both conditions with different numbers*/
    //pwr3 and pwr2 are given precise numbers to minimize computing time
    for(pwr3 = 1; pwr3 <= 35; pwr3++){
        for(pwr2 = 1; pwr2 <= 2048; pwr2++){
            //Total power calculation
            totalpwr3 = pwr3 * pwr3 * pwr3;
            totalpwr2 = pwr2 * pwr2;

            /*for loop for finding a pair of nums up to 1000
            that are equal to the totalpwr2/3*/
            for(nmpwr2 = 1, nmpwr3 = 1; nmpwr2 <= 1000; nmpwr2++, nmpwr3++){
                //Condition 1 for comparing nmpwr2 with totalpwr3
                condpwr2 = (nmpwr2*nmpwr2)*2; 
                //Condition 2 for comparing nmpwr3 with totalpwr2
                condpwr3 = (nmpwr3*nmpwr3*nmpwr3)*2;
                //If both conditions are true - print the pair of nums
                if(condpwr2 == totalpwr3 && condpwr3 == totalpwr2){
                    cout << nmpwr2 << " " << nmpwr2 << endl;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}