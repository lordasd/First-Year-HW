/* Ex5a: Divides the left and divides by the right
*==================================
* Written by David Zaydenberg
*
* Program calls a function and takes input of numbers into
* an array of 6 cells.
* Another function is called to check the statements - which
* are called to be checked in a third function.
* If a number can divide the left and be divided by the right
* without modulo, than the statement is true.
* The program outputs the amount of cells that make the statement true.
*/

//-----Include Section------//
#include <iostream>
#include <cstdlib>

//-----Using Section--------//
using std::cout;
using std::cin;
using std::endl;

//-----Constant Section------//
//Array cells
const int N = 6;

//-----Prototypes------//
//Function for number input into an array.
void input_array(int arr[]);
//Function for adding counter in the statement is true after
//calling the bool statement function.
int divide_d_array(const int arr[]);
//Function being called by "divide_d_array" func to check
//if statement true/false and return the bool.
bool tr_fl_cell_array(const int arr[], int i);

//------Main---------//
int main(){

    //Array of numbers
    int arr[N];
    //Input number into array
    input_array(arr);
    //Print the cells that the statement fulfills
    cout << divide_d_array(arr) << endl;

    return EXIT_SUCCESS;
}

//--------Input_Array Function----------//
void input_array(int arr[]){
    //Input numbers into array
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

//---------Divide/Divided_Array_Function------//
int divide_d_array(const int arr[]){
    //Index
    int i;
    //Counter for the amount of cells that fulfills the statement
    int divide_count = 0;
    //Bool for checking if statement fulfilled
    bool celltruth = false;

    //Loop goes through the array and check the statements
    for(i = 0; i < N; i++){
        //Number must start from 1 up to N-1, so it will have
        //a number from the left and the right to check the statement.
        if(i > 0 && i < N-1)
        {
            //Bool reset each time a cell fulfilled the statements.
            celltruth = false;
            //Calls the function to check the main statements.
            celltruth = tr_fl_cell_array(arr, i);
            //If the statement is true(bool true) add 1 to the counter.
            if(celltruth){
                //fulfilled cell counter
                divide_count++;
            }
        }
    }
    return divide_count;
}

//---------True_False_Cell_Array_Function-------//
bool tr_fl_cell_array(const int arr[], int i){
    //If a cell to the left and itself are not 0 than continue.
    if(arr[i-1] != 0 && arr[i] != 0){
        //If a cell divides the left and divided by the right
        //without modulo, then return true(Statement fulfilled)
        if(arr[i]%arr[i-1] == 0 && arr[i+1]%arr[i] == 0){
            return true;
        }
    }
    return false;
}