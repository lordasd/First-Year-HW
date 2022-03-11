/* Ex2b: Outputing the highest number.
*Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
*Program take 3 number inputs(but not decimal) and calculate with + and * the highest option:
* (a+b)*c
*If there is 2 possible ways to get the same highest number, it will search for the highest option without brackets:
* a*b+c
*/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){

    int num1, num2, num3; //input variables
    int op1, op2, op3, op4, op5, op6; //Caclulation option variables

    cin >> num1 >> num2 >> num3; //Inputs

    //Different calculation options
    op1 = (num1+num2)*num3; 
    op2 = (num1+num3)*num2;
    op3 = (num2+num3)*num1;
    op4 = num1*num2+num3;
    op5 = num1*num3+num2;
    op6 = num2*num3+num1;

    //If there are more than 1 option for the same result and it should be bigger than the 1 different result, go in.
    if((op1 == op2 && op1 > op3) || (op1 == op3 && op1 > op2) || (op2 == op3 && op2 > op1)){
            //If the result bigger than the other or equal to them, pring them.
            if(op4 >= op5 && op4 >= op6){
                cout << op4 << endl;
            }
            else if(op5 >= op4 && op5 >= op6){
                cout << op5 << endl;
            }
            else if(op6 >= op4 && op6 >= op5){
                cout << op6 << endl;
            }
    }
    else{ //else if there only one biggest result, than print it.
        if(op1 > op2 && op1 > op3){
            cout << op1 << endl;
        } 
        else if(op2 > op1 && op2 > op3){
            cout << op2 << endl;
        }
        else if(op3 > op1 && op3 > op2){
            cout << op3 << endl;
        }
    }

    return 0;
}