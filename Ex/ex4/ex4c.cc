#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 8;

int main(){

    int arr[N]; //Main array for the input.
    int firstnum[N]; //Array of the loop
    int i, n, k, j; //Indexes.
    int first; // Saving first number.
    int count, times; // Counting
    bool occur[N] = {false}; //
    bool loop = false;
    bool firstfound = false;

    //Insert values into the array
    for(i = 0; i < N; i++){
        cin >> arr[i];
    }

    //Outer loop in charge to start from the next index if loop not found
    for(k = 0; k < N; k++){
        j = 0; //j index reset
        times = 0; //counter reset
        first = -1; /* first number reset to -1 because of an
        option last value 0 and first index 0*/
        count = 0;//counter for testing loop repeats
        //resets the bool array if not loop was found
        for(i = 0; i < N; i++){
            occur[i] = false;
        }
        //Inner loop to find the loop
        for(i = k, n = 0; i < N;){
            //If values between the array indexes(0-7) enter
            if(arr[i] >= 0 && arr[i] < N){
                //Saves the index so later to be found as first in the loop
                n = i;
                //Goes threw the loop, from value the the index
                i = arr[i];
                //Saves the index as true(to be part of the loop).
                occur[i] = true;
                //If we found the first number that is true, save it.
                if(occur[arr[i]] && times == 0){
                    first = i; //First number of the loop
                    firstfound = true;
                    times++;//makes sure that "first" saves only one time!
                }
                //If first number was found, start an array for the loop.
                if(firstfound){
                    firstnum[j] = i;
                    count++;
                    j++;
                }
                //If loop is finished quit the inner loop.
                if(arr[i] == first){
                    loop = true;
                    break;
                }
            }
            //If number > N or < 0 continue the next k.
            else{
                break;
            }
        }
        //if loop was found, exit the outer loop.
        if(loop){
            break;
        }
    }
    //Print the loop!
    for(i = 0; i < count; i++){
        cout << firstnum[i] << " ";
    }
    cout << endl;
    return EXIT_SUCCESS;
}
