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
void terms_input(char mandatory[][MAX_STR_LEN], int num_of_mandatory);
int check_passwd(const char passwd_in[][MAX_STR_LEN],
                 char passwd_out[][MAX_STR_LEN],
                 const char mandatory_chars[][MAX_STR_LEN],
                 int num_of_mandatory);
void validity_check(const char passwd_in[][MAX_STR_LEN],
                    char passwd_out[][MAX_STR_LEN],
                    const char mandatory_chars[][MAX_STR_LEN],
                    int num_of_mandatory, int &amount);

//-----------Main Func-----------//
int main(){

    char passwd_in[MAX_STRS][MAX_STR_LEN];
    char passwd_out[MAX_STRS][MAX_STR_LEN];
    char mandatory_chars[MAX_STRS][MAX_STR_LEN];
    int inp_passwd_amount, num_of_mandatory;

    inp_passwd_amount = 5;
    password_input(passwd_in, inp_passwd_amount);

    num_of_mandatory = 3;
    terms_input(mandatory_chars, num_of_mandatory);

    cout << check_passwd(passwd_in, passwd_out,
                         mandatory_chars, num_of_mandatory) << endl;

    return EXIT_SUCCESS;
}


//----------password_input----------//
void password_input(char inp_passwd[][MAX_STR_LEN], int inp_passwd_amount){

    for(int i = 0; i < inp_passwd_amount; i++){
        cin >> setw(MAX_STR_LEN) >> inp_passwd[i];
    }
}

//--------------terms_input-----------------//
void terms_input(char mandatory[][MAX_STR_LEN], int num_of_mandatory){

    for(int i = 0; i < num_of_mandatory; i++){
        cin >> setw(MAX_STR_LEN) >> mandatory[i];
    }
}

//Run-time - O(N^4) because we have 4 arrays inside each other.
//Check password sends chars to validity_check function
//To check how many valid passwords there is and returns the amount.
int check_passwd(const char passwd_in[][MAX_STR_LEN],
                 char passwd_out[][MAX_STR_LEN],
                 const char mandatory_chars[][MAX_STR_LEN],
                 int num_of_mandatory){

    int amount = 0;
    validity_check(passwd_in, passwd_out, mandatory_chars,
                   num_of_mandatory, amount);

    return amount;
}

//Validity check each char in a password if it meets the mandatory
//requierment. If it's met/ or not go to the next char.
//If the whole mandat was met, copy the password to passwd_out and
//continue to the next password.
void validity_check(const char passwd_in[][MAX_STR_LEN],
                    char passwd_out[][MAX_STR_LEN],
                    const char mandatory_chars[][MAX_STR_LEN],
                    int num_of_mandatory, int &amount){

    //passwd_in and mandatory_chars indexes.
    int i, j, k, l;
    //index for passwd_out.
    int m = 0;
    //counter to compare to the amount of mandatory rows.
    int count = 0;
    //boolian array to check if a pattern was met.
    bool occured[MAX_STR_LEN] = {0};

    //passwd_in
    for(i = 0; i < MAX_STRS; i++){
        for(j = 0; passwd_in[i][j] != '\0'; j++){
            //mandatory_chars
            for(k = 0; k < num_of_mandatory; k++){
                for(l = 0; mandatory_chars[k][l] != '\0'; l++){
                    //if mandat row wasn't met yet, enter
                    if(!occured[k]){
                        //If we found a match, remeber in occrured and
                        //count++ and break from this row of mandatory.
                        if(passwd_in[i][j] == mandatory_chars[k][l]){
                            occured[k] = true;
                            count++;
                            break;
                        }
                    }
                }
            }
            //If the count is equal to the amount to rows of mandatory,
            //we found a valid password. copy it to passwd_out and add
            //to the amount of valid passwords.
            if(count == num_of_mandatory){
                amount++;
                strcpy(passwd_out[m], passwd_in[i]);
                m++;
                break;
            }
        }
        //reset counter each password.
        count = 0;
        //reset each password occured validation.
        for(j = 0; j < num_of_mandatory; j++){
            occured[j] = false;
        }
    }
}