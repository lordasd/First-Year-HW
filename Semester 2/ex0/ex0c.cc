/* Ex0c: Files combination
*==========================
* Written by David Zaydenberg
*
* Program is combining 2 files that have names and grades into
* one file.
*
* read_file_names takes input of file names to combine and and outfile name.
*
* open_files opens the files
*
* file_to_array check if a file is empty and
* transfers the data 2 2 2d arrays ;)
*
* merge_arrays is going array over array and looks for similar name.
* each time it sends the array for name check in "similar" function.
* If it returns true, it will save the info from the first array and
* skip the name in the second array and save the other grades.
* If no similar name found, it will save the values and continue
* to the next name. Each time a similar name is found from file2
* it will save the index of the row in bool array.
* After it finishes merging first file, it will go over the second
* file and merge all names that weren't similar with the first file.
*
* sort_by_name sorts all the array by name from a-z. and each time
* it compares name that are generated from insert_name function.
*
* Out_files will print out the array and send all the info to outfile.
*
* At the end program is closing the files.
*
*==========================*/
//--------Inlcude Section--------//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

//---------Using Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::setw;

//------------Consts------------//
const int MAX_FILE_LEN = 100;
const int STUDENT = 50, GRADE = 100;

//----------Prototypes------------//
void read_file_names(char file1_in[], char file2_in[], char file_out[]);
void open_files(ifstream &inp1, ifstream &inp2, ofstream &out,
                const char file1_in[], const char file2_in[],
                const char file_out[]);
int file_to_arr(ifstream &inp, char file_arr[][GRADE]);
int merge_arrays(const char file1_arr[][GRADE], const char file2_arr[][GRADE],
                 char combined_arr[][GRADE], int file1_students,
                 int file2_students);
bool similar(const char file1_arr[][GRADE],
             const char file2_arr[][GRADE], int i, int j);
void sort_by_name(char combined_arr[][GRADE], int max_students);
void insert_name(const char combined_arr[][GRADE], char name[STUDENT], int index);
void out_file(ofstream &out, const char combined_arr[][GRADE],
              int max_students);
void close_files(ifstream &inp1, ifstream &inp2, ofstream &out);

//Calls functions
//------------Main-------------//
int main() {

    ifstream inp1;
    ifstream inp2;
    ofstream out;
    char file1_in[MAX_FILE_LEN], file2_in[MAX_FILE_LEN], file_out[MAX_FILE_LEN];
    char file1_arr[STUDENT][GRADE], file2_arr[STUDENT][GRADE];
    char combined_arr[STUDENT][GRADE];
    int file1_students, file2_students;
    int max_students;

    read_file_names(file1_in, file2_in, file_out);
    open_files(inp1, inp2, out, file1_in, file2_in, file_out);
    file1_students = file_to_arr(inp1, file1_arr);
    file2_students = file_to_arr(inp2, file2_arr);
    max_students = merge_arrays(file1_arr, file2_arr, combined_arr,
                                file1_students, file2_students);
    sort_by_name(combined_arr, max_students);
    out_file(out, combined_arr, max_students);
    close_files(inp1,inp2,out);

    return EXIT_SUCCESS;
}

//Reads file names
//------------Read_File_Names--------------//
void read_file_names(char file1_in[], char file2_in[], char file_out[]) {
    cin >> setw(MAX_FILE_LEN) >> file1_in;
    cin >> setw(MAX_FILE_LEN) >> file2_in;
    cin >> setw(MAX_FILE_LEN) >> file_out;
}

//Opens files
//-------------Open_Files----------------//
void open_files(ifstream& inp1, ifstream& inp2, ofstream& out,
                const char file1_in[], const char file2_in[], const char file_out[]) {
    inp1.open(file1_in);
    inp2.open(file2_in);
    out.open(file_out);
}

//Transfers file data to arrays
//----------------File_To_Arr----------------//
int file_to_arr(ifstream &inp, char file_arr[][GRADE]) {
    int file_students = 0;
    //Check if the file is empty
    if(inp.peek() != std::ifstream::traits_type::eof()) {
        for (int i = 0; !inp.eof(); i++) {
            if(isalpha(inp.peek())){
                inp.getline(file_arr[i], STUDENT);
                file_students++;
            }
        }
    }
    return file_students;
}

//Merge arrays into one array
//------------Merge_arrays---------------//
int merge_arrays(const char file1_arr[][GRADE], const char file2_arr[][GRADE],
                 char combined_arr[][GRADE], int file1_students,
                 int file2_students){

    //Boolian to make sure we don't print
    //again at the end when printing 2nd file.
    bool file2_occurred[STUDENT] = {false};
    bool found_similar = false;
    //Counting students
    int max_students = 0;
    //combined_arr index
    int comb_i;
    //file1 & 2 indexes. k for column use.
    int i, j, k;

    for(i = 0; i < file1_students; i++){
        for (j = 0; j < file2_students; j++) {
            //Compare student names
            if (similar(file1_arr, file2_arr, i, j)) {
                //If name in file2 wasn't used yet >
                if (!file2_occurred[j]) {
                    max_students++;
                    file2_occurred[j] = true;
                    found_similar = true;
                }
                //Save values into combined_arr
                for (k = 0; file1_arr[i][k] != '\0'; k++) {
                    combined_arr[i][k] = file1_arr[i][k];
                }
                comb_i = k;
                //Transfer the left over grades from the same
                //student from file1 to the combined_arr.
                //Skip the name transfer.
                for (k = 0; file2_arr[j][k] != '\0'; k++) {
                    if (isalpha(file2_arr[j][k])) {
                        continue;
                    } else {
                        combined_arr[i][comb_i++] = file2_arr[j][k];
                    }
                }
                break;
            }
        }
        //Skip normal transfer if we found
        //in file1 & file2 similar names.
        if(found_similar){
            found_similar = false;
            continue;
        }
        //If no similar names are found ->
        for(k = 0; file1_arr[i][k]; k++){
            combined_arr[i][k] = file1_arr[i][k];
        }
        max_students++;
    }

    //Save the other students from file2
    //that hasn't appeared in file1.
    for (j = 0; j < file2_students; j++) {
        if (!file2_occurred[j]) {
            for (k = 0; file2_arr[j][k] != '\0'; k++) {
                combined_arr[i][k] = file2_arr[j][k];
            }
            max_students++;
            i++;
        }
    }
    return max_students;
}

//Checks if the name of the two files are the same
//--------------Similar-------------------//
bool similar(const char file1_arr[][GRADE],
             const char file2_arr[][GRADE], int i, int j){
    int k = 0;
    while(file1_arr[i][k] == file2_arr[j][k]){
        //Run until spaces are found at the same time.
        if(file1_arr[i][k] == ' ' && file2_arr[j][k] == ' '){
            return true;
        }
        k++;
    }
    return false;
}

//Sorting the array by name from a-z
//-------------Sort_By_Name----------------//
void sort_by_name(char combined_arr[][GRADE], int max_students){
    char temp_char[STUDENT+GRADE];
    char name1[STUDENT], name2[STUDENT];
    //last valued char+1(z+1)
    int min_value = 123;
    int min_index;
    int temp_value;
    //i & j rows for the array and k for cols.
    int i, j, k;
    bool found = false;

    for(i = 0; i < max_students; i++){
        insert_name(combined_arr, name1, i);
        for(j = i+1, k = 0; j < max_students; j++){
            //Find the lowest charachter to swap with combined_arr[i]
            if(combined_arr[i][k] > combined_arr[j][k]){
                found = true;
                temp_value = combined_arr[j][k];
                if(temp_value < min_value){
                    min_value = temp_value;
                    min_index = j;
                }
            }
        }
        //max_students-1 last swap.
        if(i < max_students-1 && found) {
            insert_name(combined_arr, name2, min_index);
            //If the main name bigger than the second name,
            //swap the whole lines(Name+Grades)
            if (strcmp(name1, name2) > 0) {
                strcpy(temp_char, combined_arr[i]);
                strcpy(combined_arr[i], combined_arr[min_index]);
                strcpy(combined_arr[min_index], temp_char);
            }
            //reset min_value
            min_value = 123;
            found = false;
        }
    }
}

//Inserts a name into a name array.
//---------Insert_Name---------------//
void insert_name(const char combined_arr[][GRADE], char name[STUDENT], int index){
    if(isalpha(combined_arr[index][0])){
        for(int word_i = 0; word_i < STUDENT; word_i++){
            if(combined_arr[index][word_i] == ' '){
                break;
            }
            else{
                name[word_i] = combined_arr[index][word_i];
            }
        }
    }
}

//Transfers the combined array to an out file
//--------------Out_file------------------//
void out_file(ofstream &out, const char combined_arr[][GRADE],
              int max_students){
    for(int i = 0; i < max_students; i++){
        cout << combined_arr[i] << endl;
        out << combined_arr[i] << endl;
    }
}

//Closes files
//--------------Close_files---------------//
void close_files(ifstream &inp1, ifstream &inp2, ofstream &out){
    inp1.close();
    inp2.close();
    out.close();
}