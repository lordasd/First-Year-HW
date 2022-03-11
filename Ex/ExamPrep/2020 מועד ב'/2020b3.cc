#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int M = 3, N = 10;

bool short_in_long(const int short_arr[], const int long_arr[], int jump);
bool check(const int short_arr[], const int long_arr[],
            int jump, int shortindx, int longindx, bool &equal);

int main(){

    int short_arr[M] = {1, 2, 3};
    int long_arr[N] = {1, 7, 2, 7, 3, 8, 5, 8, 3, 17};
    int jump = 2;

    if(short_in_long(short_arr, long_arr, jump)){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }

    return EXIT_SUCCESS;
}

//Gets two arrays and sends them plus jump to check function
//to see if each jump the values are the same with shor and long arrays.
//Long array only jumping and short array going 1 forward each time.
//If first value isn't the same it won't go in check funtion.
bool short_in_long(const int short_arr[], const int long_arr[], int jump){
    int shortindx, longindx;
    bool equal = false;

    if(short_arr[0] == long_arr[0]){
        if(check(short_arr, long_arr, jump, 0, 0, equal = false)){
            return true;
        }
        else false;
    }
    return false;
}

//Checks if values are the same between short and long arrays each jump.
bool check(const int short_arr[], const int long_arr[],
            int jump, int shortindx, int longindx, bool &equal){
    if(longindx < N && shortindx < M){
        if(short_arr[shortindx] == long_arr[longindx]){
            check(short_arr, long_arr, jump, shortindx+1, longindx+jump, equal = true);
        }
        else{
            equal = false;
        }
    }
    return equal;
}