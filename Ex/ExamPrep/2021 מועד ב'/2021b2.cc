#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int ROWS = 7, COLS = 9;

int diamond_searcher(const int arr[][COLS], int &row, int &col, int &len);
bool check_validity(const int arr[][COLS], int i, int j, int &size);

int main(){

    int arr[ROWS][COLS] = {1, 2, 3, 4, 5,  17, 7, 8, 9,
                           3, 4, 5, 6, 17, 38, 17, 2, 1,
                           2, 1, 7, 17, 38, 0, 38, 17, 0,
                           2, 99, 17, 38, 8, 2, 4, 38, 17,
                           99, 0, 99, 17, 38, 9, 38, 17, 0,
                           1, 99, 4, 2, 17, 38, 17, 4, 6,
                           1, 2, 3, 4, 5, 17, 2, 3, 6};
    int row, col, len, amount;

    amount = diamond_searcher(arr, row, col, len);

    cout << row << " " << col << " " << len << " " << endl << amount << endl;

    return EXIT_SUCCESS;
}

//Searches for starting point(top corner of a diamond).
//If the top is equal to the lower two parts,
//enter the check_validity function.
//Run-time - O(N^2).
int diamond_searcher(const int arr[][COLS], int &row, int &col, int &len){

    int amount = 0;
    int i = 0, j = 0;
    int size = 0;
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            //Region which a diamond can be in.
            if(i < ROWS-3 && j > 0 && j < COLS-2){
                if(arr[i][j] == arr[i+1][j-1] &&
                   arr[i][j] == arr[i+1][j+1]){
                    //If a dimons is found, amount++.
                    if(check_validity(arr, i, j, size = 1)){
                        //If the diamond is bigger then anyone else
                        //save indexes and length.
                        if(size > len){
                            len = size;
                            row = i;
                            col = j;
                        }
                        amount++;
                    }
                    else{
                        continue;
                    }
                }
            }
        }
    }
    return amount;
}

//Boolian check if a diamond is found.
//Function is splitting to two sides of the diamond and compares
//to the top value until it reaches the bottom tip of the diamond.
bool check_validity(const int arr[][COLS], int i, int j, int &size){

    //boolian for the while loop.
    bool valid = true;
    //indexes for left and right sides.
    int k = i; int m = i;
    int l = j; int n = j;

    while(valid){
        //Checks towards the outside.
        if(arr[i][j] == arr[k+1][l-1] &&
           arr[i][j] == arr[m+1][n+1]){
            //Borders which the diamond can't escape(array).
            if(k < ROWS-1 && l >= 0 && m < ROWS-1 && n < COLS){
                k++;l--;
                m++;n++;
                //Only adding when going outside.
                size++;
            }
        }
        //If the size of the trianlge is at least, 2 it can
        //continue towards the inside.
        else if(size >= 2 &&
                arr[i][j] == arr[k+1][l+1] &&
                arr[i][j] == arr[m+1][n-1]){
            //Borders which the diamond can't escape(array).
            if(k < ROWS-1 && l >= 0 && m < ROWS-1 && n < COLS){
                k++;l++;
                m++;n--;
            }
        }
        else{
            valid = false;
        }
        //If we got to the tip, and the indexes are equal,
        //and of course we are not at the same position as the
        //starting point, return true and we found the diamond!
        if(k == m && l == n && k != i){
            return true;
        }
    }
    return false;
}