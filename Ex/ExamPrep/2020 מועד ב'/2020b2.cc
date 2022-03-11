#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int ROWS = 5, COLS = 5;

int find_mirror(const int arr[][COLS], int &length);

enum mirr_pattern_t
{
    NO_MPT, HORIZ_MPT, VERT_MPT
};

int main(){

    int found;
    int lenght;
    int arr[ROWS][COLS] = {1, 1, 1, 4, 3,
                           2, 4, 2, 5, 4,
                           1, 2, 3, 2, 1,
                           2, 1, 2, 5, 3,
                           3, 3, 1, 4, 3};

    found = find_mirror(arr, lenght);

    if(found == 0){
        cout << lenght << "Nothing found" << endl;
    }
    else if(found == 1){
        cout << lenght << " Horizontal found" << endl;
    }
    else if(found == 2){
        cout << lenght << " Vertical found" << endl;
    }

    return EXIT_SUCCESS;
}

//Runtime - O(COLS*ROWS).
int find_mirror(const int arr[][COLS], int &length){

    int i,j;
    int counterup = 0;
    int counterdown = 0;
    int maxcountrows = 0;
    int maxcountcols = 0;
    bool found_hor = false;
    bool found_vert = false;

    //Rows check
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            //going up
            if(j < COLS/2){
                if(arr[i][j] + 1 == arr[i][j+1] && (j+1) < (COLS)){
                    counterup++;
                }
            }
            //going down
            else if(j > COLS/2){
                if(arr[i][j] - 1 == arr[i][j+1] && (j+1) < (COLS)){
                    counterdown++;
                }
            }
            //middle number.
            if(j == COLS/2 && arr[i][j] - 1 == arr[i][j+1]){
                counterdown++;
            }
        }
        //If we found the same pattern of going up and down
        //and the length is more than 1, so we found a mirror.
        if(counterup == counterdown && counterup > 1){
            found_hor = true;
            if(counterup+counterdown > maxcountrows){
                maxcountrows = counterup+counterdown+1;
            }
        }
        //reset counter each row.
        counterup = 0;
        counterdown = 0;
    }
    //Cols check
    for(j = 0; j < COLS; j++){
        for(i = 0; i < ROWS; i++){
            //going up
            if(i < ROWS/2){
                if(arr[i][j] + 1 == arr[i+1][j] && (i+1) <= (ROWS)){
                    counterup++;
                }
            }
            //going down
            else if(i > ROWS/2){
                if(arr[i][j] - 1 == arr[i+1][j] && (i+1) <= (ROWS)){
                    counterdown++;
                }
            }
            //midle number.
            if(i == ROWS/2 && arr[i][j] - 1 == arr[i+1][j]){
                counterdown++;
            }
        }
        //If we found the same pattern of going up and down
        //and the length is more than 1, so we found a mirror.
        if(counterup == counterdown && counterup > 1){
            found_hor = true;
            if(counterup+counterdown > maxcountrows){
                maxcountcols = counterup+counterdown+1;
            }
        }
        //reset counters each collumn
        counterup = 0;
        counterdown = 0;
    }

    //Statements to decide what type of enum to return.
    //If it was horizontal, vertical or both(horizontal) or nothing.
    //Plus save the length of the longest streak.
    if(maxcountrows > maxcountcols){
        length = maxcountrows;
        return HORIZ_MPT;
    }
    else if(maxcountrows < maxcountcols){
        length = maxcountcols;
        return VERT_MPT;
    }
    else if(maxcountrows == maxcountcols && maxcountrows > 1){
        length = maxcountcols;
        return HORIZ_MPT;
    }
    length = 0;
    return NO_MPT;
}