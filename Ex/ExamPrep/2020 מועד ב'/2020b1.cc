#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 5;

bool max_oddity(const int arr[], int &startindex, int &endindex);

int main(){

    int arr[N*2] = {1, 2, 2, 6, 4, 4, 9, 9, 1, 6};
    int startindex, endindex;

    max_oddity(arr, startindex, endindex);

    cout << startindex << " " << endindex << endl;

    return EXIT_SUCCESS;
}

//Finding a streak of pairs of odds and evens.
//if the streak is finished mid array, it will stop and return true
// + save the first starting index and last index.
//Runtime - O(N*2) Worst case.
bool max_oddity(const int arr[], int &startindex, int &endindex){
    int counter = 0;
    bool found = false;
    bool foundfirst = false;
    bool foundlast = false;
    startindex = -1;
    endindex = -1;

    for(int i = 0; i < N*2; i += 2){
        //Checking if 2 values beside each other are even or odd.
        if( (arr[i] % 2 == 0 && arr[i+1] % 2 == 0)||
            (arr[i] % 2 != 0 && arr[i+1] % 2 != 0) ){
            //first index found check
            if(!foundfirst){
                startindex = i;
                foundfirst = true;
            }
            //found a streak check
            found = true;
            //goes up 2 indexes each time.
            counter += 2;
        }
        //If the streak is over before array is finished,
        //check the last index.
        else if(found && !foundlast){
            endindex = i-1;
            foundlast = true;
            break;
        }
    }
    //If the array finished and there was a streak,
    //but last index wasn't registered, check up.
    if(found && !foundlast){
        endindex = (N*2)-1;
        foundlast = true;
    }
    return found;
}