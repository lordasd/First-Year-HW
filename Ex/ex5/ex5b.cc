/* Ex5b: Zigzag Array
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Worse Case runtime: N*(N-1)
*
* Program take input from the user into an array of 6 cells
* Program is searching for the longest zigzag and saves the
* cell is started from.
*
* 4 Functions:
* Main() - Calls for input_array() to read the values into the array 
* Then calls for find_zigzag_cell to get the zigzag length as return
* and get the first cell of the longest zigzag and then prints the
* first cell of the longest zigzag and the longest zigzag.
*
* input_array() - Getting called by main and reads values into an array
* of N(6) numbers.
* 
* Find_zigzag_cell() - Function is finding a starting cell for the
* longest zigzag and returning zigzag length from the function
* "Find_zigzag_length" which sends an index from a loop each time
*
* Find_Zigzag_length() - Function is getting and index to start from
* to find a zigzag. Each time it returns the length of the current zigzag
* which it started from the index that was sent from Find_zigzag_cell().
*/

//---------Include Section---------//
#include <iostream>
#include <cstdlib>

//-----------Using Section----------//
using std::cout;
using std::cin;
using std::endl;

//--------Constant Section-----------//
//Constant number for array
const int N = 6;

//----------Prototypes Section-------//
void input_array(int arr[]);
int find_zigzag_cell(const int arr[], int& zigzag_cell);
int find_zigzag_length(const int arr[], int i);

//---------Main Section-------------//
int main(){

    //array variable
    int arr[N];
    //Zigzag cell variable
    int zigzag_cell;
    //Zigzag length variable
    int zigzag_length;

    //Calls input array function
    input_array(arr);

    //Calls for a function to get zigzag length back
    zigzag_length = find_zigzag_cell(arr, zigzag_cell);

    //Print out zigzag cell and length
    cout << zigzag_cell << " " << zigzag_length << endl;

    return EXIT_SUCCESS;
}

//Input array function reads input into the array from the user
//---------Input_Array------------//
void input_array(int arr[]){

    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

//Function is getting a reference variable "zigzag_cell" and 
//finding a starting cell for the longest zigzag
//and returning zigzag length from the function "Find_zigzag_length"
//-----------Find_ZigZag_Cell---------//
int find_zigzag_cell(const int arr[], int& zigzag_cell){

    //Temporary and main variable
    //that start from their base number.
    int temp_zigzag_length = 1;
    int zigzag_length = 1;
    zigzag_cell = 0;

    //Loop for finding the first cell for the longest zigzag
    for(int i = 0; i < N; i++){
        //Calling a function to find the length from the current index
        temp_zigzag_length = find_zigzag_length(arr, i);
        //If temporery length is higher than original length
        if(temp_zigzag_length > zigzag_length){
            //Original equals to temp length
            zigzag_length = temp_zigzag_length;
            //Highest cell updated
            zigzag_cell = i;
        }
    }
    //Return zigzag length
    return zigzag_length;
}

//Function for finding the length of the current index it gets
//and returning zigzag_length
//-------------Find_Zigzag_Length-------------//
int find_zigzag_length(const int arr[], int i){

    //Zigzag length always starts with 1
    int zigzag_length = 1;
    //Boolians for checking if a statement happend already
    bool smaller = true; //for i smaller than i+1 
    bool bigger = false; //for i bigger than i+1

    //Loop that gets the index from the find_zigzag_cell function
    //and if a statemnt is true, add 1 to the counter of the zigzag length
    for(; i < N-1; i++){
        //If the first value is smaller than the next one >
        if(arr[i] < arr[i+1] && smaller && !bigger){
            //boolians are reversed to make sure it won't go inside the
            //same statement
            smaller = false;
            bigger = true;
            //Add length
            zigzag_length++;
        }
        //If the first number smaller thean the next one,
        //but the boolians does not meet the requierments,
        //break from the loop
        else if(arr[i] < arr[i+1] && !smaller && bigger){
            break;
        }
        //if the first value is bigger than the next one
        //(only valid after the first statement of the loop)
        else if(arr[i] > arr[i+1] && bigger && !smaller){
            smaller = true;
            bigger = false;
            //Add length
            zigzag_length++;
        }
        //If nothing is meeting the requierments, break from the loop
        else{
            break;
        }
    }

    //Return the length of the current zigzag
    return zigzag_length;
}
