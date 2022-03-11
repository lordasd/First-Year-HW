/* Ex6a: Finding highest summed row&col
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* This program take input into an array of 4x5 and searches
* for the highest summed row and column and prints them out.
*
*/

//-------Include Section-------//
#include <iostream>
#include <cstdlib>

//--------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//----------Constant------------//
const int ROWS = 4;
const int COLS = 5;

//----------Prototypes----------//
void input_arr(int arr[][COLS]);
int find_highest_sum(const int arr[][COLS], int& highest_col);

//Main calls for input_arr to read values into an array
//Call find_highest_sum to find the highest summed row&col
//Prints at the end the highest summed row&col.
//------------Main--------------//
int main(){

    int arr[ROWS][COLS];
    int highest_row, highest_col;

    input_arr(arr);

    highest_row = find_highest_sum(arr, highest_col);

    cout << highest_row << " " << highest_col << endl;

    return EXIT_SUCCESS;
}

//Reads input into an array of 4x5
//-----------Input_arr----------//
void input_arr(int arr[][COLS]){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cin >> arr[i][j];
        }
    }
}

//Finding the highest summed row&col in the array.
int find_highest_sum(const int arr[][COLS], int& highest_col){

    int rowsum = 0, colsum = 0, temp;
    int hirow;
    int i, j;

    //Finding the highest summed row.
    for(i = 0; i < ROWS; i++){
        temp = 0;
        for(j = 0; j < COLS; j++){
            temp += arr[i][j];
        }
        if(temp > rowsum){
            rowsum = temp;
            hirow = i;
        }
    }

    //Finding the highest summed column.
    for(i = 0; i < COLS; i++){
        temp = 0;
        for(j = 0; j < ROWS; j++){
            temp += arr[j][i];
        }
        if(temp > colsum){
            colsum = temp;
            highest_col = i;
        }
    }

    return hirow;
}