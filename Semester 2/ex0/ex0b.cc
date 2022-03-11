/* Ex0b: File Decryption
*==================================
* Written by David Zaydenberg
*
* Program decrypts the encrypted file from ex0a.
* 
* Program opens 2 input files: Encrypted file to decrypt and a meaningless
* file that will be out key for decryption.
*
* Main calls to read names of the files, opens them and checks if the names
* are valid(existing files).
* File contents are transfered to arrays and files closed.
* The file content arrays are sent to the decryption function.
* 
* Decrypt function - main task of this function to creat two arrays
* of frequencies that go from high to low so it compares them and know
* that the same level of occurrence are replaced(key file char replaces
* encrypted file char(as long as its lower chars a-z)).
* first sends to filter the arrays so only lower chars will be in the arrays.
* Then sends the filtered arrays to frequency_sort to get sorted by the
* amount of occurrences. Indexes(0-25) are acting as the a-z(26 chars). and
* the values in them are the amount of times they occurred in the filtered
* arrays. Then the counted arrays are sent to the sort_by_freq function
* to sort the arrays from highest frequencys to the lowest.
* (frequency/index) (frequency - amount appeared)
* (index - the char).
*
* After getting the last arrays to be worked on the are compared
* and over each char from the main encrypted_arr to check if 
* the char is to be encrypted. if it has a key(~same level of occurrence)
* it will be changed by the key character.
* if there is no occurrence, the character will be replaced by the first
* char of the abc that has not being used.
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
using std::setw;

//------------Consts------------//
const int MAX_NAME_LEN = 100;
const int MAX_STR_LEN = 100;
const int ABC_LEN = 26;

//----------Prototypes------------//
void read_file_names(char encrypted_file[], char key_file[]);
void open_files(ifstream& inp1, ifstream& inp2,
                const char encrypted_file[], const char key_file[]);
void files_to_arrays(ifstream& inp1, ifstream& inp2,
                     char encrypted_arr[], char key_arr[]);
void close_files(ifstream& inp1, ifstream& inp2);
void decrypt(ifstream& inp1, ifstream& inp2,
             const char encrypted_arr[], const char key_arr[]);
void filter_a_z(const char arr[], char filtered[]);
void frequency_sort(const char sorted[], int freqency[]);
void sort_by_freq(const int freq[], int sorted[]);

//Main only calls functions.
//------------Main--------------//
int main() {

    ifstream inp1;
    ifstream inp2;
    char encrypted_file[MAX_NAME_LEN];
    char key_file[MAX_NAME_LEN];
    char encrypted_arr[MAX_STR_LEN];
    char key_arr[MAX_STR_LEN];

    read_file_names(encrypted_file, key_file);
    open_files(inp1, inp2, encrypted_file, key_file);
    files_to_arrays(inp1, inp2, encrypted_arr, key_arr);
    close_files(inp1, inp2);
    decrypt(inp1, inp2, encrypted_arr, key_arr);

    return EXIT_SUCCESS;
}

//Reads names of the files
//---------------Read_File_Names-----------------//
void read_file_names(char encrypted_file[], char key_file[]) {
    cin >> setw(MAX_NAME_LEN) >> encrypted_file;
    cin >> setw(MAX_NAME_LEN) >> key_file;
}

//Opens files
//--------------Opens_Files---------------//
void open_files(ifstream& inp1, ifstream& inp2,
                const char encrypted_file[], const char key_file[]) {
    inp1.open(encrypted_file);
    inp2.open(key_file);
}

//Transfering all data from files to arrays.
//--------------Files_to_arrays---------------//
void files_to_arrays(ifstream& inp1, ifstream& inp2,
                     char encrypted_arr[], char key_arr[]) {
    int i;

    for(i = 0; !inp1.eof(); i++){
        encrypted_arr[i] = inp1.get();
    }
    if(inp1.eof()){
        encrypted_arr[i-1] = '\0';
    }

    for(i = 0; !inp2.eof(); i++){
        key_arr[i] = inp2.get();
    }
    if(inp2.eof()){
        key_arr[i-1] = '\0';
    }
}

//Closes files
//-----------Close_Files--------------//
void close_files(ifstream& inp1, ifstream& inp2) {
    inp1.close();
    inp2.close();
}

//Decrypts the file and prints out the result
//------------Decrypt---------------//
void decrypt(ifstream& inp1, ifstream& inp2,
             const char encrypted_arr[], const char key_arr[]) {
    char encrypted_filtered[MAX_STR_LEN];
    char key_filtered[MAX_STR_LEN];
    int freq_enc[ABC_LEN] = {0};
    int freq_key[ABC_LEN] = {0};
    int enc_sorted[ABC_LEN*2];
    int key_sorted[ABC_LEN*2];
    bool decrypted[ABC_LEN] = {0};
    bool found = false;

    //Filter arrays a-z.
    filter_a_z(encrypted_arr, encrypted_filtered);
    filter_a_z(key_arr, key_filtered);
    //Sort arrays by frequency(0-25(a-z) & values = appearance).
    frequency_sort(encrypted_filtered, freq_enc);
    frequency_sort(key_filtered, freq_key);
    //Sort by frequency(From highest to lowest (Freq,index(char)) ).
    sort_by_freq(freq_enc, enc_sorted);
    sort_by_freq(freq_key, key_sorted);

    for(int i = 0; encrypted_arr[i] != '\0'; i++){
        if(islower(encrypted_arr[i])){
            for(int j = 0; j < ABC_LEN*2; j += 2){
                //If the values(characters) are equal[j+1] is the place
                //of the value and +97 is the lowest char(a). and the value
                //of the enc_sorted[j] isn't 0 so there was appearance.
                if(encrypted_arr[i] == char(enc_sorted[j+1]+97) &&
                   enc_sorted[j] != 0){
                    //If also the key_sorted[j] isn't 0, print the decryption
                    //character and save the index in decrypted bool array.
                    if(key_sorted[j] != 0){
                        cout << char(key_sorted[j + 1] + 97);
                        decrypted[key_sorted[j + 1]] = true;
                        break;
                    }
                    //If it's a char that has not decryption equal in
                    //frequency, go over the abc and check if a char wasn't
                    //decrypted already and use the first one we find.
                    //and print it of course.
                    else{
                        for(int k = 0; k < ABC_LEN; k++){
                            if (!decrypted[k]){
                                cout << char(k + 97);
                                //save the decrypted char.
                                decrypted[k] = true;
                                //Place them in the existing key_sorted
                                //array so the can decrypt the same char
                                //if the find it again!
                                key_sorted[j] = 1;
                                key_sorted[j + 1] = k;
                                found = true;
                                break;
                            }
                        }
                    }
                }
                //If we found the char that wasn't decrypted by
                //the frequency, but by the availability of
                //the character that hasn't been decrypted yet.
                if(found){
                    break;
                }
            }
        }
        //If it's not a lower case char, print as it is.
        else{
            cout << encrypted_arr[i];
        }
    }
}

//Filters the arrays for a-z chars
//-------------Filter_a_z---------------//
void filter_a_z(const char arr[], char filtered[]){
    int i,j;

    for (i = 0, j = 0; arr[i] != '\0'; i++) {
        if(islower(arr[i])) {
            filtered[j++] = arr[i];
        }
    }
    //Place '\0' in filtered array when the filtering is complete.
    if(arr[i] == '\0'){
        filtered[j] = '\0';
    }
}

//Counts the frequency of each char
//indexes 0-25 / a-z.
//------------frequency_Sort------------//
void frequency_sort(const char sorted[], int freqency[]){

    for(int i = 0; sorted[i] != '\0';i++){
        if(islower(sorted[i])){
            //adding amount to the index
            //index is calculated by the value
            //of sorted[i] char - 97.
            //97 is a(first number). a-97 = 0.
            freqency[int(sorted[i] - 97)]++;
        }
    }
}

//Sorting by frequency(freq,char).
//----------------Sort_By_Freq--------------------//
void sort_by_freq(const int freq[], int sorted[]){
    bool occurred[ABC_LEN] = {0};
    bool found = false;
    //sorted index
    int max_value;
    int max_index;

    //freq over freq array
    for(int i = 0, k = 0; i < ABC_LEN; i++){
        //if a char(index 0-26) isn't found
        if(!occurred[i]){
            //by default save max value and index if there won't
            //be found a higher amount of appearance.
            max_value = freq[i];
            max_index = i;
            //Go over the frequncy array and save highest
            //value(amount of appearance) and his index(char).
            for(int j = 0; j < ABC_LEN; j++){
                //If the max value is smaller then the value in the array,
                //and it wansn't appeared yet OR if the value is equal but
                //the index is bigger it means we found the same level of
                //occurrence just missed it before(and it wasn't occurred).
                if( (max_value < freq[j] && !occurred[j])
                   || (max_value <= freq[j] && i > j && !occurred[j]) ){
                    max_value = freq[j];
                    max_index = j;
                    found = true;
                }
            }
            //If we found the maximum valid values,
            //insert into the sorted array(value, index).
            if(found){
                sorted[k++] = max_value;
                sorted[k++] = max_index;
                occurred[max_index] = true;
                found = false;
            }
        }
    }
}