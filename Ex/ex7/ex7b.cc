/* Ex7b: 
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program takes input of a number (1 = encode, 2 = decode).
* program takes input of a string(sentence) and you choose
* if you encode it or decode it.
*
* Each type has 3 functions that are to be done in order.
* Encoding order 1 > 2 > 3
* Decoding order 3 > 2 > 1
*
* n vaialbe will be defined randomly with an integer of 2-4.
*
* Each function will work with the n variable and change the string
* from function to function.
*
* Encoding: the string will go through 3 encoding methods:
* 1) Change each lower/upper case letter to the letter n distance from it.
* if it the letter is > z/Z it will return to a/A.
*
* 2) characters will be divided by n chars and be reflcted by each other.
* for example 1234 = 4321 | AbRKd = dKRbA. If at the end there will be left
* less than n, than they will stay as they are.
*
* 3) A random lower_case letter will be generated and will be inserted into
* the string each n times(add, not instead).
*
* Decoding: the string will go through 3 decoding methods:
* 1) Change each lower/upper case letter to the letter -n distance from it.
* if it the letter is < a/A it will return to z/Z.
*
* 2) characters will be divided by n chars and be reflcted by each other.
* for example 1234 = 4321 | AbRKd = dKRbA. If at the end there will be left
* less than n, than they will stay as they are.
*
* 3) A random lower_case letter will be generated and will be removed from
* the string each time it's found.
*
==================================*/
//--------Include Section--------//
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <random>

//--------Unsing Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::setw;

//----------Constants------------//
//Max length of the string
const int MAX_STR_LEN = 1000;
//Seed instructed by assingment.
const int SEED = 17;

//----------Prototypes-----------//
void encode(char str[], int n);
void decode(char str[], int n);
void n_dist_replace(char str[], int n);
void n_reflection(char str[], int n);
void n_rand_add(char str[], int n);
void n_dist_replace_undo(char str[], int n);
void n_reflection_undo(char str[], int n);
void n_rand_add_undo(char str[], int n);

//Main will let you input the choice of encoding or decoding
//and insert the sentence to make operations on.
//Random n value will be generated.
//-----------Main Func-----------//
int main(){

    srand(SEED);
    //Random generation from 2-4.
    int n = rand() % 3 + 2;
    //option(1 = encode 2 = decode)
    int option;
    char str[MAX_STR_LEN];
    
    cin >> option;
    //ignore the space at the beginning
    cin.ignore();
    cin.getline(str, MAX_STR_LEN);

    if(option == 1){
        encode(str, n);
    }
    else if(option == 2){
		//If decoding we get the n at the end of the sentence
        n = str[strlen(str)-1] - '0';
        decode(str, n);
    }

    return EXIT_SUCCESS;
}

//Encode will call 3 functions in order to make
//encoding operations on the string and print them
//out each time.
//--------Encode Function---------//
void encode(char str[], int n){

    n_dist_replace(str, n);
    cout << str << endl;

    n_reflection(str, n);
    cout << str << endl;

    n_rand_add(str, n);
    cout << str << n << endl;

}

//Decode will call 3 functions in opposite order to make
//decoding operations on the string and print them
//out each time.
//---------Decode Function---------//
void decode(char str[], int n){

    n_rand_add_undo(str, n);
    cout << str << endl;

    n_reflection_undo(str, n);
    cout << str << endl;

    n_dist_replace_undo(str, n);
    cout << str << endl;

}

//----------------------ENCODING FUNCTIONS--------------------//

//Change each lower/upper case letter to the letter n distance from it.
//if it the letter is > z/Z it will return to a/A.
//---------n_dist_replace----------//
void n_dist_replace(char str[], int n){

    int i;
    int temp;

    for(i = 0; str[i] != '\0'; i++){
        //if lower char
        if(islower(str[i])){
            //if char > z go back to a
            if(str[i] + n > 'z'){
                temp = str[i] + n;
                str[i] = temp - 26;
            }
            else{
                str[i] += n;
            }
        }
        //if upper char
        else if(isupper(str[i])){
            //if char > Z go back to A
            if(str[i] + n > 'Z'){
                temp = str[i] + n;
                str[i] = temp - 26;
            }
            else{
                str[i] += n;
            }    
        }    
    }
}

//characters will be divided by n chars and be reflcted by each other.
//for example 1234 = 4321 | AbRKd = dKRbA. If at the end there will be left
//less than n, than they will stay as they are.
//-------------n_reverse-----------//
void n_reflection(char str[], int n){
    
    size_t i, j;
    char temp;
    //len index that goes back as j goes forward
    int len = n;

    for(i = 0; str[i] != '\0'; i += n){
        //reset len each time
        len = n;
        //if next step will be larger than the length of the string, break.
        if((i + n) > (strlen(str))){
            break;
        }
        //save and insert values to reverse the string
        for(j = i; n/2+1 < len; j++, len--){
            temp = str[i];
            str[j] = str[j+len-1];
            str[j+len-1] = temp;
        }
    }
}

//A random lower_case letter will be generated and will be inserted into
//the string each n times(add, not instead).
//----------n_rand_add------------//
void n_rand_add(char str[], int n){

    int i;
    //place holder to remember where you started moving all
    //characters forward.
    int place_holder;
    //Random generation of letters between a-z.
    char rand_char = rand() % ('z' -'a'+1) + 'a';
    char temp1, temp2;
    
    //each n times insert a rand_char inside
    for(i = n; str[i] != '\0'; i += n+1){
        temp1 = str[i];
        //insert random char
        str[i] = rand_char;
        place_holder = i;

        //After insertion, move everone 1 forward
        for(; str[i] != '\0'; i++){
            temp2 = str[i+1];
            str[i+1] = temp1;
            temp1 = temp2;
        }
        i = place_holder;
        
        //If last i+n is last char add the random
        //char after it.
        if(str[i+n+1] == '\0'){
            str[i+n+1] = rand_char;
            str[i+n+2] = '\0';
            break;
        }
    }
}

//---------------DECODING FUNCTIONS------------------//

//Change each lower/upper case letter to the letter -n distance from it.
//if it the letter is < a/A it will return to z/Z.
//----------n_rand_add_undo----------//
void n_rand_add_undo(char str[], int n){
    
    int i;
    int place_holder;
    char rand_char = str[n];

	//i=n to miss all letters that equal to rand_char before first n.
    for(i = n; str[i] != '\0'; i++){
        //remembers the starting point
        place_holder = i;
        //if random char found, move all chars 1 place back.
        if(str[i] == rand_char){
            //each char is going 1 back to fill the removed random char
            for(; str[i] != '\0'; i++){
                str[i] = str[i+1];
            }
            //back to the place we found the random char.
            i = place_holder;    
        }
    }
    //remove the n var from the sentence at the end.
    str[strlen(str)-1] = '\0';
}

//characters will be divided by n chars and be reflcted by each other.
//for example 1234 = 4321 | AbRKd = dKRbA. If at the end there will be left
//less than n, than they will stay as they are.
//----------n_reverse_undo-----------//
void n_reflection_undo(char str[], int n){

    size_t i, j;
    char temp;
    //len index that goes back as j goes forward
    int len = n;

    for(i = 0; str[i] != '\0'; i += n){
        //reset len each time
        len = n;
        //if next step will be larger than the length of the string, break.
        if((i + n) > (strlen(str))){
            break;
        }
        //save and insert values to reverse the string
        for(j = i; n/2+1 < len; j++, len--){
            temp = str[i];
            str[j] = str[j+len-1];
            str[j+len-1] = temp;
        }
    }
}

//A random lower_case letter will be generated and will be removed from
//the string each time it's found.
//---------n_dist_replace_undo----------//
void n_dist_replace_undo(char str[], int n){

    int i;
    int temp;

    for(i = 0; str[i] != '\0'; i++){
        //if lower letter
        if(islower(str[i])){
            //if < a move to z
            if(str[i] - n < 'a'){
                temp = str[i] - n;
                str[i] = temp + 26;
            }
            else{
                str[i] -= n;
            }
        }
        //if upper letter
        else if(isupper(str[i])){
            //if < A move to Z.
            if(str[i] - n < 'A'){
                temp = str[i] - n;
                str[i] = temp + 26;
            }
            else{
                str[i] -= n;
            }    
        }    
    }
}
