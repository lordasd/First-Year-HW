#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

void str_in_str(char pattern[], char str[]);
int search_index(char pattern[], char str[], int indx1, int indx2, bool &found);

int main(){

    char pattern[4] = {'a', 'b', 'c', '\0'};
    char str[7] = {'g', 'f', 'a', 'b', 'c', 'h', '\0'};

    str_in_str(pattern, str);

    return EXIT_SUCCESS;
}

//Getting two char arrays from main and sending them
//To search_index to find the first index that the pattern starts.
void str_in_str(char pattern[], char str[]){

    int indx1, indx2;
    int strtindex;
    bool found = false;

    cout << search_index(pattern, str, 0 , 0, found = false) << endl;
}

//Searching for the first index in str for the pattern that matcher pattern char.
int search_index(char pattern[], char str[], int indx1, int indx2, bool &found){
    int strtindex;
    //If indx1 came to the end, it means it found the pattern.
    //found = true to skip index being set to -1.
    if(indx1 == strlen(pattern)){
        found = true;
        //return the index calculated.
        return strtindex = indx2 - strlen(pattern);
    }
    //if same values found continue to next indexes
    else if(pattern[indx1] == str[indx2]){
        strtindex = search_index(pattern, str, indx1+1, indx2+1, found);
    }
    //If nothing found, move to the next index only in str.
    else{
       strtindex = search_index(pattern, str, indx1, indx2+1, found);
    }
    //If pattern wasn't found return starting index = -1.
    if(indx1 != strlen(pattern) && !found){
        return strtindex = -1;
    }
    return strtindex;
}
