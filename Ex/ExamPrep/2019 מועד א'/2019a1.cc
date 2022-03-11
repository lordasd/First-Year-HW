#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int SHORT = 3, LONG = 12;

int jumps(const int short_arr[], const int long_arr[], int jump);

int main(){

    int short_arr[SHORT] = {19, 11, 17};
    int long_arr[LONG] = {17, 20, 19, 18, 11, 11, 77, 12, 17, 10, 5, 3879};
    int jump = 3;

    cout << jumps(short_arr, long_arr, jump) << endl;

    return EXIT_SUCCESS;
}

//Function jumps in indexes in long_arr and checks if values
//are equal between long and short arr. short_arr jumps 1 index each time.
//Runtime - Worst case - O(LONG)
int jumps(const int short_arr[], const int long_arr[], int jump){

    //indexes for both arrays.
    int i, j = 0;
    //boolian if found first index.
    bool found = false;
    //Save first index.
    int firstindex;

    //Start with -1 because the first jump won't count first index.
    for(i = -1; i < LONG; i+= jump){
        //If long_arr isn't finished but short_arr is.
        if(j == SHORT){
            return firstindex;
        }
        if(short_arr[j] == long_arr[i]){
            if(!found){
                firstindex = i;
                found = true;
            }
            j++;
            continue;
        }
        //If first number is found, but it stuck in middle
        //of the array, restart the search.
        else if(found && short_arr[j] != long_arr[i]){
            found = false;
            j = 0;
        }
    }
    //If long_arr finished and short_arr also.
    if(j == SHORT){
        return firstindex;
    }
    return -1;
}