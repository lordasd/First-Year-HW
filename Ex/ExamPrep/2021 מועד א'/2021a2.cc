#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int ROWS = 5, COLS = 4;

int find_nums(const int arr[][COLS]);
bool check_cols(const int arr[][COLS], int i, int j);

int main(){

    int arr[ROWS][COLS] = { 0, 17, 3879, 6,
                            17, 17, 17, 3879,
                            3879, 17, 17, 3879,
                            3879, 6, 17, 6,
                            17, 1, 2, 3879 };
    cout << find_nums(arr) << endl;

    return EXIT_SUCCESS;
}

//Runtime O(N^4) - worst case scenario if it has to go over the whole array
//when values are all different so it can't compare.

//Searches for the amount of rows that has all values around each row.
//Sends a value into "check_cols" and does a whole search on the 2d arr.
int find_nums(const int arr[][COLS]){

    int rows = 0;
    int i, j;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            //If the value is found in all rows
            //rows++.
            if(check_cols(arr, i, j)){
                if(j == COLS-1){
                    rows++;
                }
                continue;
            }
            //else, row is not valid so continue to next row.
            else{
                break;
            }
        }
    }
    
    return rows;
}

//Gets the the value to compare to by indexes i, j and
//goes over the whole 2d array. Once a value is found
//in a row, it goes to the next row. If it finishes
//all rows, the value is valid.
bool check_cols(const int arr[][COLS], int i, int j){

    int k, l;
    int rows = 0;

    //Goes each row to find a value that equal.
    for(i, k = 0; k < ROWS; k++){
        //Skips searching for nothing
        //if a row was not valid.
        if(rows < k){
            break;
        }
        //searches for the equality of values
        //in each column.
        for(j, l = 0; l < COLS; l++){
            if(arr[i][j] == arr[k][l]){
                rows++;
                break;
            }
        }
    }
    //If found all rows, return true.
    if(rows == ROWS){
        return true;
    }
    return false;
}