/* Ex7a: Basic operations on a string
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program takes input of a string and a string of unwanted characters.
* char_filter function turns all lower characters into upper characters,
* removing all numbers and puntuations.
* 
* char_removal removes all the characters that are inputed inside
* remove_chars string.
*
* Prints both outputs operations.
*
===================================*/
//------Include Section----------//
#include <iostream>
#include <cstdlib>
#include <iomanip>

//--------Unsing Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::setw;

//----------Constants------------//
char MAX_STR_LEN = 100;
//----------Prototypes-----------//
void char_input(char char_arr[], char remove_chars[]);

void char_filter(const char char_arr[], char char_arr_filtered[]);

void char_removal(const char char_arr[], const char remove_chars[],
                    char char_removed[]);

//Calls char_input to read strings into 2 char variables
//then calls for char_filter to filter out unwanted characters
//then calls for char_removal to remove out unwated
//(chosen in remove_chars variable) characters.
//Prints both results from these two functions.
//----------Main Func------------//
int main(){

    //main char string
    char char_arr[MAX_STR_LEN];
    //output string from char_filter func.
    char char_arr_filtered[MAX_STR_LEN];
    //string of unwanted chars to be removed
    //from char_arr in char_removal func.
    char remove_chars[MAX_STR_LEN];
    //cleaned/removed string from char_removal func.
    char char_removed[MAX_STR_LEN];

    char_input(char_arr, remove_chars);

    char_filter(char_arr, char_arr_filtered);

    char_removal(char_arr, remove_chars, char_removed);

    cout << char_arr_filtered << endl;
    cout << char_removed << endl;

    return EXIT_SUCCESS;
}

//Input into two char variables. char_arr and remove_chars
//to use them in the next functions
//--------char_arrays------------//
void char_input(char char_arr[], char remove_chars[]){

    //Input main "string" of chars
    cin >> setw(MAX_STR_LEN) >> char_arr;
    //Input chars to remove from main "string" of chars
    cin >> setw(MAX_STR_LEN) >> remove_chars;
}

//Turns lowercase chars into uppercase, removes numbers and punctuations.
//---------char_filter------------//
void char_filter(const char char_arr[], char char_arr_filtered[]){

    int i, j;
    //loop to go over the array of both strings.
    for(i = 0, j = 0; char_arr[i] != '\0'; i++){
        //searching for letters
        if(isalpha(char_arr[i])){
            //uppercase letter
            if(isupper(char_arr[i])){
                char_arr_filtered[j] = char_arr[i];
                j++;
            }
            //lowercase letter
            else if(islower(char_arr[i])){
                //calculation to transfrom lower to upper character
                char_arr_filtered[j] = char_arr[i] - 32;
                j++;
            }
        }
        //digit character
        else if(isdigit(char_arr[i])){
            continue;
        }
        //punctuation character
        else if(ispunct(char_arr[i])){
            continue;
        }
    }
    //end of array equals '\0' to be stopped
    char_arr_filtered[j] = '\0';
}

//removes characters chosen in remove_chars from char_arr into char_removed.
//--------Char_removal------------//
void char_removal(const char char_arr[], const char remove_chars[],
                    char char_removed[]){
    //indexes
    int i, j;
    int k = 0;
    //Bool to say if a char from remove_chars occured in char_arr
    bool remove_occur = false;

    for(i = 0; char_arr[i] != '\0'; i++){
        remove_occur = false;
        for(j = 0; remove_chars[j] != '\0'; j++){
            if(char_arr[i] == remove_chars[j]){
                remove_occur = true;
                continue;
            }
        }
        if(!remove_occur){
            char_removed[k] = char_arr[i];
            k++;
        }
    }
    //end of array equals '\0' to be stopped
    char_removed[k] = '\0'; 
}