/* Ex7c: Password Check
*==================================
* Written by David Zaydenberg
*
* Program gets passwords and criterias for valid passwords.
* program searches for valid passwords that meet the criterias and
* send then prints them out.
*
* Main - Takes input of the amount of passwords to input and sends 
* you to input passwords in "password_input" in 2d array.
* Than takes input for how many criterias there is and then sends you
* to input them into a second 2d array(terms_input).
*
* Password_input - Takes input of the passwords up to the amount we
* set before.
*
* terms_input - Takes input of the terms that the password should meet
* up until the amount we set before.
*
* Validity_check - function gets all parameters of arrays and the amout
* of them: inp_passwd, mandatory, out_passwd, inp_passwd_amount,
* mandat_amount, out_passwd_amount. and than compares between characters
* of the passwords and the terms.(4 loops(2d arrays)).
* Each time it finds a password that meets all the terms it send it to
* the out_passwd array.
* 
* print_out_passwd - Prints out all the valid passwords that meet the terms.
*
==================================*/
//--------Include Section--------//
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>

//--------Unsing Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::setw;

//----------Constants------------//
const int MAX_STRS = 10;
const int MAX_STR_LEN = 100;

//----------Prototypes-----------//
void password_input(char inp_passwd[][MAX_STR_LEN], int passwd_amount);
void terms_input(char mandatory[][MAX_STR_LEN], int mandat_amount);
void validity_check(const char inp_passwd[][MAX_STR_LEN],
                    const char mandatory[][MAX_STR_LEN],
                    char out_passwd[][MAX_STR_LEN],
                    int inp_passwd_amount, int mandat_amount,
                    int& out_passwd_amount);
void print_out_passwd(const char out_passwd[][MAX_STR_LEN],
                    int out_passwd_amount);

/*Takes input of the amount of passwords to input and sends 
you to input passwords in "password_input" in 2d array.
Than takes input for how many criterias there is and then sends you
to input them into a second 2d array(terms_input).*/
//-----------Main Func-----------//
int main(){

    //2D array strings
    char inp_passwd[MAX_STRS][MAX_STR_LEN];
    char out_passwd[MAX_STRS][MAX_STR_LEN];
    char mandatory[MAX_STRS][MAX_STR_LEN];
    //Amount of in each array/rows.
    int inp_passwd_amount, mandat_amount, out_passwd_amount = 0;

    cin >> inp_passwd_amount;
    password_input(inp_passwd, inp_passwd_amount);

    cin >> mandat_amount;
    terms_input(mandatory, mandat_amount);

    validity_check(inp_passwd, mandatory, out_passwd,
                  inp_passwd_amount, mandat_amount, out_passwd_amount);

    print_out_passwd(out_passwd, out_passwd_amount);

    return EXIT_SUCCESS;
}

/*Takes input of the passwords up to the amount we
set before.*/
//----------password_input----------//
void password_input(char inp_passwd[][MAX_STR_LEN], int inp_passwd_amount){

    for(int i = 0; i < inp_passwd_amount; i++){
        cin >> setw(MAX_STR_LEN) >> inp_passwd[i];
    }
}

/*Takes input of the terms that the password should meet
up until the amount we set before.*/
//--------------terms_input-----------------//
void terms_input(char mandatory[][MAX_STR_LEN], int mandat_amount){

    for(int i = 0; i < mandat_amount; i++){
        cin >> setw(MAX_STR_LEN) >> mandatory[i];
    }
}

/*function gets all parameters of arrays and the amout
of them: inp_passwd, mandatory, out_passwd, inp_passwd_amount,
mandat_amount, out_passwd_amount. and than compares between characters
of the passwords and the terms.(4 loops(2d arrays)).
Each time it finds a password that meets all the terms it send it to
the out_passwd array.*/
//-------------validity_check-----------//
void validity_check(const char inp_passwd[][MAX_STR_LEN],
                    const char mandatory[][MAX_STR_LEN],
                    char out_passwd[][MAX_STR_LEN],
                    int inp_passwd_amount, int mandat_amount,
                    int& out_passwd_amount){

    //Indexes for 2-2D Array of strings(inp_passwd,mandatory)
    int i,j,k,l;
    //index for out_passwd array
    int out_row = 0;
    //Boolean for finding the same character
    bool occured = false;
    //Amount of times a term was found
    int counter = 0;
    //boolean array for checking the occurance in a term
    //so it won't go over a term again.
    bool mandat_occured[mandat_amount] = {false};

    //4 forloops. the term is changing on each character.
    //rows for strings
    for(i = 0; i < inp_passwd_amount; i++){
        //going through each char in the string
        for(j = 0; inp_passwd[i][j] != '\0'; j++){
            //rows for terms
            for(k = 0; k < mandat_amount; k++){
                //If a term already occured skip the row.
                if(mandat_occured[k]){
                    continue;
                }
                //reset occured
                occured = false;
                //going over each character comparing equality.
                for(l = 0; mandatory[k][l] != '\0'; l++){
                    if(inp_passwd[i][j] == mandatory[k][l]){
                        occured = true;
                        break;
                    }
                }
                //if there were equality, add to the counter and save
                //the location in the mandat_occured boolean.
                if(occured){
                    counter++;
                    mandat_occured[k] = true;
                    break;
                }
            }
            //If the counter equal to the amount of rules(rows)
            //add to the amount of out_passwd passwords and send
            //the string to the out_passwd array.
            if(counter == mandat_amount){
                out_passwd_amount++;
                strcpy(out_passwd[out_row], inp_passwd[i]);
                out_row++;
                counter = 0;
                break;
            }          
        }
        //After finishing a string, reset all boolean that were switched true.
        for(int f = 0; f < mandat_amount; f++){
            mandat_occured[f] = false;
        }
        counter = 0;
    }
}

/*Prints out all the valid passwords that meet the terms.*/
//--------------print_out_passwd---------------//
void print_out_passwd(const char out_passwd[][MAX_STR_LEN],
                    int out_passwd_amount){

    for(int i = 0; i < out_passwd_amount; i++){
        cout << out_passwd[i] << endl;
    }
}