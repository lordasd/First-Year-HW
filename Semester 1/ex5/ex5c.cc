/* Ex5c: Histogram in array
*==================================
* Written by David Zaydenberg
* 
* Program shows a histogram of 6 columns which shows the amount
* of prime numbers and the amount of 2-6 diviable numbers.
* 
* This program takes input of lo and hi(max & min) numbers
* which should be between 2 and 10000.
* random_input_array chooses 200 randomly numbers between 2 and 10000
* from a (101) seed into rand_arr.
* count_array will count the amount of numbers that are primes and
* can be divided by 2 up to 6 and inserted into histo_arr by order.
* Counter numbers will be inserted into each column of the histogram:
* first col is prime numbers, second to sixth are numbers that are divided
* by 2 - 6.
* In main we have function that are taken from an outsource file that let's
* build a histogram.
* We call create_hist to build a new histogram with 30 rows.
* We call add_col in a loop to insert the histo_arr in order and build the
* histogram and show all the "#".
*  
*/

//------Include Section--------//
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "histogram.h" //Outsource file

//-------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//--------Constant section-----//
//Amount of numbers
const int N = 200; 
//Divide by up to 6;
const int DIVIDE_BY = 6; 

//-------Prototypes------------//
void random_input_array(int rand_arr[], int hi, int lo);
void count_array(const int rand_arr[], int histo_arr[]);
bool prime_finder(const int rand_arr[], int i);

//Main function will take lo and hi number inputs
//and call for a function to insert rand numbers into
//rand_arr. Then call count_array to count the amount
//of numbers that satisfy the statements.
//-------Main Function---------//
int main(){

    //array of random numbers
    int rand_arr[N];
    //array of counted numbers
    int histo_arr[DIVIDE_BY] = {0};
    //Minimum and maximum numbers
    int lo, hi;
    int i;//index

    cin >> lo >> hi;

    //Call random_input_array to insert random numbers into array.
    random_input_array(rand_arr, hi, lo);
    
    //Call count_array to count the numbers that satisfy the statements.
    count_array(rand_arr, histo_arr);

    //As long as the input is valid lo >= 2 and hi <= 10000 continue.
    if(lo >= 2 && hi <= 10000){
        //Create histogram
        create_hist(30,
                    DIVIDE_BY * (COL_MIN_WIDTH + COL_MIN_SPACE),
                    DIVIDE_BY,
                    "primes and divide-by histo");
        cout << endl;

        //Loop that creates collumns for the histogram
        for(i = 0; i < DIVIDE_BY; i++){
            char col_title[10];
            //Only for first col, we want to call it "primes"
            if(i == 0){
                add_col(i, histo_arr[i], 0, 0, "primes", '#');
                continue;//skip one loop.
            }
            //for each col from 2-6 call it by i(1-6)
            sprintf(col_title, "div-by-%d", i+1); 
            add_col(i, histo_arr[i], 0, 0, col_title, '#'); 
        }
    }

    //Draw the histogram.
    draw_hist();

    return EXIT_SUCCESS;
}

//Random_Input_Array will insert random number between lo and hi
//that are taken from 101 seed into rand_arr.
//---------Random_Input_Array------------//
void random_input_array(int rand_arr[], int hi, int lo){
    srand(101);//seed that was asked by the assignment.
    for(int i = 0; i < N; i++){
        //insertion of a random number into rand_arr[i].
        rand_arr[i] = rand() % (hi-lo + 1) + lo;
    }
}

//Count_Array will count that amount of prime numbers and that are 
//divided by 2 to 6 and inserted into histo_arr. 
//------------------Count_Array-------------//
void count_array(const int rand_arr[], int histo_arr[]){
    
    int i;
    bool prime = false;

    //Counting prime numbers and calling Prime_Finder to check if
    //a number is prime.
    for(i = 0; i < N; i++){
        prime = prime_finder(rand_arr, i);
        if(prime){
            //add only to the first cell(col of the histogram)
            histo_arr[0]++;
        }
    }
    //counting numbers which divide by 2-6, i+1(1-6)
    for(i = 1; i < DIVIDE_BY; i++){
        for(int j = 0; j < N; j++){
            if(rand_arr[j] % (i+1) == 0){
                histo_arr[i]++;
            }
        }
    }
}

//Prime number finder. If number is prime return true, else
//return false.
//-----------Prime_Finder------------//
bool prime_finder(const int rand_arr[], int i){

    for(int div = 2; div <= sqrt(rand_arr[i]); div++){
        if(rand_arr[i] % div == 0){
            return false;
        }
    }
    return true;
}
