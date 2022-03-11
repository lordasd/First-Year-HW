/* Ex5c: Histogram in array
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* This program 
*/
//------Include Section--------//
#include <iostream>
#include <cmath>
#include <cstdlib>
#include "histogram.h"

//-------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//--------Constant section-----//
const int N = 200;
const int DIVIDE_BY = 6;

//-------Prototypes------------//
void random_input_array(int rand_arr[], int hi, int lo);
void count_array(const int rand_arr[], int histo_arr[]);
bool prime_finder(const int rand_arr[], int i);

//-------Main Function---------//

int main()
{

    int rand_arr[N], histo_arr[DIVIDE_BY] = {0};
    int lo, hi;
    int i;

    cin >> lo >> hi;

    random_input_array(rand_arr, hi, lo);
    count_array(rand_arr, histo_arr);

    if (lo >= 2 && hi <= 10000){
        create_hist(30,
                    DIVIDE_BY * (COL_MIN_WIDTH + COL_MIN_SPACE),
                    DIVIDE_BY,
                    "primes and divide-by histo");

        for (i = 0; i < DIVIDE_BY; i++){
            char col_title[10];
            if (i == 0){
                add_col(i, histo_arr[i], 0, 0, "primes", '#');
                continue;
            }
            sprintf(col_title, "div-by-%d", i + 1);
            add_col(i, histo_arr[i], 0, 0, col_title, '#');
        }
    }

    draw_hist();

    return EXIT_SUCCESS;
}

//---------Random_Input_Array------------//
void random_input_array(int rand_arr[], int hi, int lo)
{
    srand(101);
    for (int i = 0; i < N; i++){
        rand_arr[i] = rand() % (hi - lo + 1) + lo;
    }
}

//------------------Count_Calc_Array-------------//
void count_array(const int rand_arr[], int histo_arr[]){

    int i;
    bool prime = false;

    //Finding and counting prime numbers.
    for (i = 0; i < N; i++){

        prime = prime_finder(rand_arr, i);

        if (prime){
            histo_arr[0]++;
        }
    }

    //counting numbers which divide by j(1-6)
    for (i = 1; i < DIVIDE_BY; i++){
        for (int j = 0; j < N; j++){
            if (rand_arr[j] % (i + 1) == 0){
                histo_arr[i]++;
            }
        }
    }
}

//-----------Prime_Finder------------//
bool prime_finder(const int rand_arr[], int i)
{
    for (int div = 2; div <= sqrt(rand_arr[i]); div++){
        if (rand_arr[i] % div == 0){
            return false;
        }
    }

    return true;
}
