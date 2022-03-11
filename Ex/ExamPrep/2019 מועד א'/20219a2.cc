#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int ROWS = 4, COLS = 7;

void uniq_num(const int arr[][COLS]);
bool check_rows(const int arr[][COLS], int &max_amount, int row, int col);

int main(){

    int arr[ROWS][COLS] = {17, 17, 5, 4, 3,  2,  1,
                           9,  9,  9, 9, 17, 17, 17,
                           9,  9,  9, 1, 2,  3,  4,
                           6,  4,  5, 4, 6,  6,  5};

    uniq_num(arr);

    return EXIT_SUCCESS;
}

//Function gets array and searches for a value
//in each row that is most common and sends it to check_row
//to see if the value appears more times in different rows.
//Runtime - O(ROWS(COLS+ROWS*COLS)) = ROWS*COLS(ROWS+1) = 
//ROWS^2COLS + ROWSCOLS = COLS*ROWS(ROWS+1) = COLS*ROWS^2
void uniq_num(const int arr[][COLS]){
    int i, j;
    //amount of appearance start with 1
    //because we compare the current and next value.
    int amount = 1;
    //max amount of appearance of a cirtain value.
    int max_amount = 0;
    int row, col;

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(arr[i][j] == arr[i][j+1]){
                amount++;
            }
            else{
                if(amount > max_amount){
                    max_amount = amount;
                    row = i; col = j-1;
                }
                amount = 1;
            }
        }
        if(check_rows(arr, max_amount, row, col)){
            cout << row << " " << arr[row][col] << " " << max_amount << endl;
        }
        max_amount = 0;
    }
}
//Boolian check_rows checks the value sent, if there is another row
//that the value appears more times.
bool check_rows(const int arr[][COLS], int &max_amount, int row, int col){

    int i, j;
    int count = 0;

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            if(arr[i][j] == arr[row][col]){
                count++;
            }
        }
        //if we counter more than max_ amount from prev
        //function than fix the amount.
        if(i == row && count > max_amount) {
            max_amount = count;
            return true;
        }
        //If we found that a different row has more amount  
        //or the same row has the same amount return false
        //and don't print.
        if(count > max_amount){
            return false;
        }
        count = 0;
    }
    return true;
}