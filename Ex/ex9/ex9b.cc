/* Ex9b: Pattern Matching
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is finding a match for a pattern recursively.
* User inputs a string of characters and then a pattern to try and match.
* A char in the string has to be similar to the char in the pattern.
* ? - has to be any kind of single char.
* * - can be any char and as many chars as is can be until it reaches the next
* char in pattern which is normal char which should be similar to the one in
* the string.
* 
* Main - has str, and pattern array of chars. stri and patterni indexes.
* occured and finished bool for ending the recursive loop.
* main calls input function to input the string and the pattern.
* main calls validity_check to check if the string matches the pattern.
* If it matches, it will print "1", else print "0".
*
* input - input a string into str and a string into pattern.
*
* validity_check - Function will check for each option in pattern array,
* if it's '?' / '*' / normal char.
* if it matches the str it will call the function again with indexes + 1.
* for '?' - as long as the there is a letter in str it will call the function
* with +1 index for both arrays.
* for '*' - as long as the next pattern char isn't the same as the current
* char in str, it will call the function with +1 in str only.
* for normal chars, it will check if they are the same chars,
* else return false.
*
* if pattern reached the end of string, it will continue to check if the last
* char of both str and pattern aren't the same(if they are letters) and
* to check if the last char in pattern isn't '*', and of course that
* the patterns has reached the end of string(finished bool).
*
*==================================*/
//-------Include Section---------//
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

//-----------Using Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::setw;

//--------Const Section----------//
const int MAX_STR_LEN = 50;

//-------------Prototype Section-----------//
void input(char str[], char pattern[]);
bool validity_check(char str[], char pattern[],
                    int stri, int patterni, bool &occured, bool &finished);

/*has str, and pattern array of chars. stri and patterni indexes.
occured and finished bool for ending the recursive loop.
main calls input function to input the string and the pattern.
main calls validity_check to check if the string matches the pattern.
If it matches, it will print "1", else print "0".*/
//-------------Int main-------------//
int main(){

    char str[MAX_STR_LEN];
    char pattern[MAX_STR_LEN];
    int stri = 0, patterni = 0;
    bool occured = true;
    bool finished = false;

    input(str, pattern);

    occured = validity_check(str, pattern, stri, patterni, occured, finished);

    if(occured){
        cout << "1" << endl;
    }
    else{
        cout << "0" << endl;
    }

    return EXIT_SUCCESS;
}

//input a string into str and a string into pattern.
//------------Input--------------//
void input( char str[], char pattern[]){
    cin >> setw(MAX_STR_LEN) >> str;
    cin >> setw(MAX_STR_LEN) >> pattern;
}

/*Function will check for each option in pattern array,
if it's '?' / '*' / normal char.
if it matches the str it will call the function again with indexes + 1.
for '?' - as long as the there is a letter in str it will call the function
with +1 index for both arrays.
for '*' - as long as the next pattern char isn't the same as the current
char in str, it will call the function with +1 in str only.
for normal chars, it will check if they are the same chars,
else return false.

if pattern reached the end of string, it will continue to check if the last
char of both str and pattern aren't the same(if they are letters) and
to check if the last char in pattern isn't '*', and of course that
the patterns has reached the end of string(finished bool).*/
//----------------Validity_check-----------------//
bool validity_check(char str[], char pattern[],
                    int stri, int patterni, bool &occured, bool &finished){

    while(pattern[patterni] != '\0' && occured && !finished){

        if(pattern[patterni] == '?'){
            if(isalpha(str[stri])){
                validity_check(str, pattern, stri + 1, patterni + 1,
                                occured = true, finished = false);
            }
        }
        else if(pattern[patterni] == '*'){
            if(str[stri] == pattern[patterni+1]){
                validity_check(str, pattern, stri, patterni + 1,
                                occured = true, finished = false);
            }
            else{
                validity_check(str, pattern, stri + 1, patterni,
                                occured = true, finished = false);
            }
        }
        else{
            if(str[stri] == pattern[patterni]){
                validity_check(str, pattern, stri + 1, patterni + 1,
                                occured = true, finished = false);
            }
            else{
                return occured = false;
            }
        }
    }
    //Checking for last characters.
    if(finished && isalpha(str[strlen(str)-1]) &&
        isalpha(str[strlen(str)-1])){
        if(str[strlen(str)-1] != pattern[strlen(pattern)-1] &&
            pattern[strlen(pattern)-1] != '*'){
            return false;
        }
    }
    if(!occured){
        return false;
    }
    finished = true;
    return true;
}