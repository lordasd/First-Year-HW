/* Ex0a: File Encryption
*==================================
* Written by David Zaydenberg
*
* Program encrypts file.
* Input: 3 files -
* 1) File that holds the key to encryption.
* 2) File to be encrypted.
* 3) File to export all the encrypted data to.
*
* Main calls all the functions to read filenames, open the files,
* checks if they are opened, encrypts them and close the files.
*
* Encryption funtion encrypts the file with the key file provided by changing each
* character that appears in key_file to the next one near it. 
* all the key provided is transfered to a str_key array.
*
*==================================*/
//----------Include Section------------//
#include <iostream>
#include <fstream>
#include <iomanip>

//---------Using Section-----------//
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::cerr;

//------------Consts------------//
const int MAX_LEN = 100;

//----------Prototypes------------//
void read_open_files(ifstream &inp1, ifstream &inp2, ofstream &out,
                char file_key[], char file_encrypt[]
                ,char file_encrypted[]);
void encrypt(ifstream &inp1, ifstream &inp2, ofstream &out, char file_key[],
                char file_encrypt[], char file_encrypted[]);
void str_key_arr(ifstream &inp1, char str_key[]);
void close_files(ifstream &inp1, ifstream &inp2, ofstream &out);

//Calls all functions for file encryption.
//------------Main--------------//
int main(){

    ifstream inp1;
    ifstream inp2;
    ofstream out;
    char file_key[MAX_LEN];
    char file_encrypt[MAX_LEN];
    char file_encrypted[MAX_LEN];

    //Read name inputs for the files and opens them.
    read_open_files(inp1, inp2, out, file_key, file_encrypt, file_encrypted);
    //Opens files
    encrypt(inp1, inp2, out, file_key, file_encrypt, file_encrypted);
    //Closes files
    close_files(inp1, inp2, out);
    return EXIT_SUCCESS;
}
//Reads file names from the user and opens them
//+ checks if they are opened.
//----------Read_open_files------------//
void read_open_files(ifstream &inp1, ifstream &inp2, ofstream &out,
                char file_key[], char file_encrypt[]
                ,char file_encrypted[]){

    cin >> setw(MAX_LEN) >> file_key;
    inp1.open(file_key);
    if(!inp1.is_open()){
        cerr << "Key file not found" << endl;
        exit(EXIT_FAILURE);
    }

    cin >> setw(MAX_LEN) >> file_encrypt;
    inp2.open(file_encrypt);
    if(!inp2.is_open()){
        cerr << "input file to encrypt was not found" << endl;
        exit(EXIT_FAILURE);
    }

    cin >> setw(MAX_LEN) >> file_encrypted;
    out.open(file_encrypted);
}
//Encrypts the file with the key file provided by changing each
//character that appears in key_file to the next one near it.
//--------------Encrypt----------------//
void encrypt(ifstream &inp1, ifstream &inp2, ofstream &out, char file_key[],
             char file_encrypt[], char file_encrypted[]){
    char str_key[MAX_LEN];
    char str_encrypt;
    bool found = false;
    //Send str_key array to transfer all the keys
    //to the array.
    str_key_arr(inp1, str_key);
    //While Input of the file we want to ecrypt
    //won't end:
    while(!inp2.eof()){
        str_encrypt = inp2.get();
        //We move +3 index each time for the first value
        //we need to compare between the key in ecryption file
        //and the str_key array.
        for(int i = 0; str_key[i] != '\0'; i += 3){
            if(str_encrypt == str_key[i] && islower(str_encrypt)){
                //transfer the char and print it out.
                out << str_key[i+1];
                cout << str_key[i+1];
                found = true;
                break;
            }
        }
        //If the character wansn't found in the key, transfer it and print.
        if(!found && !inp2.eof()){
            out << str_encrypt;
            cout << str_encrypt;
        }
        found = false;
    }
}
//transfering key_file to an array.
//---------------str_key_arr------------------//
void str_key_arr(ifstream &inp1, char str_key[]){
    
    int i;

    for(i = 0; !inp1.eof(); i++){
        str_key[i] = inp1.get();
    }
    str_key[i-1] = '\0';
}
//Close all files
//-------------Close_files--------------//
void close_files(ifstream &inp1, ifstream &inp2, ofstream &out){
    inp1.close();
    inp2.close();
    out.close();
}