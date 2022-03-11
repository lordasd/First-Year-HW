#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){

    //Variables
    int num1, num2, num3, num4 ,oddcount = 0, evencount = 0, zero = 0, positive = 0, negative = 0;

    cin >> num1 >> num2 >> num3 >> num4; //Input variables(number).

    //Statments for counting how many even and odd numbers have been inputed.
    if(num1%2 > 0 || num1%2 < 0)
    {
        oddcount ++;
    }
    else
    {
        evencount ++;
    }
    if(num2%2 > 0 || num2%2 < 0)
    {
        oddcount ++;
    }
    else
    {
        evencount ++;
    }
    if(num3%2 > 0 || num3%2 < 0)
    {
        oddcount ++;
    }
    else
    {
        evencount ++;
    }
    if(num4%2 > 0 || num4%2 < 0)
    {
        oddcount ++;
    }
    else
    {
        evencount ++;
    }

    cout << oddcount << evencount << endl; //print odd and even numbers

    //Statments to count how many zeros have been inputed 
    if(num1 == 0)
    {
        zero ++;
    }
    if(num2 == 0)
    {
        zero ++;
    }
    if(num3 == 0)
    {
        zero ++;
    }
    if(num4 == 0)
    {
        zero ++;
    }
    //Statments to count how many positive numbers have been inputed
    if(num1 > 0)
    {
        positive ++;
    }
    if(num2 > 0)
    {
        positive ++;
    }
    if(num3 > 0)
    {
        positive ++;
    }
    if(num4 > 0)
    {
        positive ++;
    }    
    if(num1 < 0)
    {
        negative ++;
    }
    //Statments to count how many negative numbers have been inputed
    if(num2 < 0)
    {
        negative ++;
    }
    if(num3 < 0)
    {
        negative ++;
    }
    if(num4 < 0)
    {
        negative ++;
    }
   
    cout << negative << positive << zero << endl;//Prints out how many negative, positive and zero numbers

    return 0;
}