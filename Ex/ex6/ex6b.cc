/* Ex6b: Isosceles triangle in a 2D-Array
*========================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Worst case scenerio runtime is : (N*M)*L^2*B;
* N = ROWS; M = COLS; L*L = The max length that we can get; B = Base
*
* This program tries to find all the longest triangles that have length of 3+.
* Main function calls for 2 functions:
* input_arr = Function to input values into array
* find_triangles = Function that finds a triangle and gets info from
* 4 different functions to print out the result of a found triangle.
* Find_triangle is looking for a point to start from the search,
* It can find standing and inverted triangles seperatly and at the same time.
* It will go to a function standing_triangle / inverted_triangle to find the
* length of the triangle. If it manages to find a length of more then 3 it 
* will search for the base the triangle in a seperate function for standing
* and inverted triangle : stand_triangle_base/invert_triangle_base.
* If it won't find a base it will shrink in length and try the shorter base
* until it reaches a base or not. If it reaches a full equal valued base,
* it will return true and the find_triangle will print the index of the tip
* of the triangle, the length and if it's standing or inverted and the value
* of the triangle.
* At the end after finding all triangles find_triangle also searched for the
* longest triangle and the amount of them and it will print it as well.
*
*/

//-------Include Section-------//
#include <iostream>
#include <cstdlib>

//--------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//----------Constant------------//
const int ROWS = 10;
const int COLS = 15;

//----------Prototypes----------//
void input_arr(int arr[][COLS]);
void find_triangles(const int arr[][COLS]);
int standing_triangle(const int arr[][COLS],
                      bool exist_triangle, int i, int j);
int inverted_triangle(const int arr[][COLS],
                      bool exist_triangle, int i, int j);
bool stand_triangle_base(const int arr[][COLS],
                   int i, int j, int k, int l,
                   int start_row, int& triangle_counter);
bool invert_triangle_base(const int arr[][COLS],
                   int i, int j, int k, int l,
                   int start_row, int& triangle_counter);

//Main calls for input_arr to read values into an array
//Then it call a find_triangles that finds a triangle and gets info
//from 4 different functions to print out the result of a found triangle
//------------Main--------------//
int main(){

    int arr[ROWS][COLS];
    
    //Function to input values into array
    input_arr(arr);

    //Function that finds a triangle and gets info
    //from 4 different functions to print out the result
    //of a found triangle
    find_triangles(arr);

    return EXIT_SUCCESS;
}

//Reads input into an array of 10x15
//-----------Input_arr----------//
void input_arr(int arr[][COLS]){

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS; j++){
            cin >> arr[i][j];
        }
    }
}

//Function that finds a triangle and gets info
//from 4 different functions to print out the result
//of a found triangle
//----------Find_Triangle----------//
void find_triangles(const int arr[][COLS]){

    //indexes
    int i,j;
    //saved indexes to print out
    int row, col;
    //trianlge starting point value
    int value;
    //Boolian check if a point is activated
    bool exist_triangle = false;
    //Length of a triangle
    int triangle_length;
    //Longest length of a triangle to be printed out
    int longest_triangle = 0;
    //The amount of the longest lengthed triangles
    int longest_amount = 0;

    //For loop that goes over the whole 2d-array
    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            //If the there are standing and inverted triangles
            //from this point check them both.
            if( (arr[i][j] == arr[i+1][j+1]) && 
                (arr[i][j] == arr[i+1][j-1]) && 
                (arr[i][j] == arr[i-1][j-1]) &&
                (arr[i][j] == arr[i-1][j+1]) &&
                 i < ROWS-2 && j >= 2 && j < COLS-2 &&
                 i >= 2 && j >= 2 && j < COLS-2){//borders of the array
                //Save value
                value = arr[i][j];
                //Save starting point
                row = i; col = j;
                exist_triangle = true;
                //Check and count the length of the triangle in the function
                triangle_length = standing_triangle(arr, exist_triangle,
                                                    i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    //if the longest triangle found again, add to the amount
                    //of them.
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    //Print the triangle.
                    cout << row << " " << col << ": " << triangle_length
                    << " standing." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }
                //Now do check the inverted triangle
                triangle_length = inverted_triangle(arr, exist_triangle,
                                                    i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    //if the longest triangle found again, add to the amount
                    //of them.
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    //Print the triangle.
                    cout << row << " " << col << ": " << triangle_length
                    << " inverted." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }

            }
            //If a start of a standing triangle is found go into function
            else if( (arr[i][j] == arr[i+1][j+1]) && 
                (arr[i][j] == arr[i+1][j-1]) &&
                 i < ROWS-2 && j >= 2 && j < COLS-2){
                //Save value
                value = arr[i][j];
                //Save starting point
                row = i; col = j;
                exist_triangle = true;
                //Check and count the length of the triangle in the function
                triangle_length = standing_triangle(arr, exist_triangle, 
                                                    i, j);
                
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    //if the longest triangle found again, add to the amount
                    //of them.
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    //Print the triangle.
                    cout << row << " " << col << ": " << triangle_length
                    << " standing." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }
            }
            //If a start of an inverted triangle is found go into function
            else if( (arr[i][j] == arr[i-1][j-1]) &&
                     (arr[i][j] == arr[i-1][j+1]) && 
                      i >= 2 && j >= 2 && j < COLS-2){//In borders
                //Save value
                value = arr[i][j];
                //Save starting point
                row = i, col = j;
                exist_triangle = true;
                //Check and count the length of the triangle in the function
                triangle_length = inverted_triangle(arr, exist_triangle,
                                                    i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    //if the longest triangle found again, add to the amount
                    //of them.
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    //Print the triangle.
                    cout << row << " " << col << ": " << triangle_length
                    << " inverted." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }
            }
            //else continue the loop.
            else{
                exist_triangle = false;
                continue;
            }
        }
    }
    //When the loop/array is finished, print the amount of times
    //the longest triangle appeard.
    cout << longest_amount << " " << longest_triangle << endl;
}

//Counting the length of a standing triangle
//----------Standing_Triangle----------//
int standing_triangle(const int arr[][COLS],
                      bool start_triangle, int i, int j){
    //value saved for comparison
    int value = arr[i][j];
    //Boolian for a finished triangle after base check
    bool finished_triangle = false;
    //triangle length
    int triangle_counter = 1;
    //saving new indexes for comparison
    int k = i;
    int l = j;
    //saving the starting row to send to the basefunction
    int start_row = i;

    //While trianle still exist, continue calculating
    while(start_triangle){
        //If both sides are equal and still have the same starting value.
        if(arr[i+1][j-1] == arr[k+1][l+1] && arr[i+1][j-1] == value
           && j-1 >= 0 && l+1 < COLS && i+1 < ROWS){//Inside the 
            //add length   
            triangle_counter++;
            //move to the next spot
            i++;k++;
            j--;l++; 
        }
        else{
            start_triangle = false;
        }
    }
    //if the length is 3 or more then continue
    if(triangle_counter >= 3){
        //Go check the base if it's valid
        finished_triangle = stand_triangle_base(arr, i, j, k ,l,
                                                start_row, triangle_counter);
        //If the length is still 3+ after checking the base, continue.
        if(triangle_counter >= 3){
            //If a base have been found return the length.
            if(finished_triangle){
                return triangle_counter;
            }
            else{
                return 0;
            }    
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

//Counting the length of an inverted triangle
//-------------Inverted_Triangle---------//
int inverted_triangle(const int arr[][COLS],
                      bool start_triangle, int i, int j){
    //value saved for comparison
    int value = arr[i][j];
    //Boolian for a finished triangle after base check
    bool finished_triangle = false;
    //triangle length
    int triangle_counter = 1;
    //saving new indexes for comparison
    int k = i;
    int l = j;
    //saving the starting row to send to the basefunction
    int start_row = i;

    //While trianle still exist, continue calculating
    while(start_triangle){
        //If both sides are equal and still have the same starting value.
        if(arr[i-1][j-1] == arr[k-1][l+1] && arr[i-1][j-1] == value
            && j-1 >= 0 && l+1 < COLS && i-1 >= 0){
            //add length
            triangle_counter++;
            //move to the next spot
            i--;k--;
            j--;l++;
        }
        else{
            start_triangle = false;
        }
    }
    //if the length is 3 or more then continue
    if(triangle_counter >= 3){
        //Go check the base if it's valid
        finished_triangle = invert_triangle_base(arr, i, j, k, l,
                                                 start_row, triangle_counter);
        //If the length is still 3+ after checking the base, continue.
        if(triangle_counter >= 3){
            //If a base have been found return the length.
            if(finished_triangle){
                return triangle_counter;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
    }
    else{
        return 0;
    }
}

//Checking if the value of the whole base is equal
//-------------Triangle_Base-----------//
bool stand_triangle_base(const int arr[][COLS],
                   int i, int j, int k, int l,
                   int start_row, int& triangle_counter){

    //Starting value to compare
    int numvalue = arr[i][j];
    //Bool to check if a base exist
    bool fullbase = true;

    //While the numbers go from the left to the right until
    //it reaches the end continue
    while(j <= l){
        //if the starting value equals to the value in ij.
        if(arr[i][j] == numvalue){
            //contiue right
            j++;
            fullbase = true;
        }
        else{
            fullbase = false;
            break;
        }
    }
    //If base is not complete and the length is 3+ continue
    while(!fullbase && ((i+1)-start_row) >= 3){
        //go to a smaller base
        i--;j++;
        l--;
        //lower the length of the triangle
        triangle_counter--;
        //if the starting value equals to the value in ij.
        if(arr[i][j] == numvalue){
            j++;
            fullbase = true;
        }
        else{
            fullbase = false;
        }
    }
    return true;
}

//Checking if the value of the whole base is equal
//-------------Triangle_Base-----------//
bool invert_triangle_base(const int arr[][COLS],
                   int i, int j, int k, int l,
                   int start_row, int& triangle_counter){
    
    //Starting value to compare
    int numvalue = arr[i][j];
    //Bool to check if a base exist
    bool fullbase = true;
    //Length of the base until hits a dead end
    int col_count = 0;

    //While the numbers go from the left to the right until
    //it reaches the end continue
    while(j <= l){
        //if the starting value equals to the value in ij.
        if(arr[i][j] == numvalue){
            //contiue right
            j++;
            fullbase = true;
            //add length of the base
            col_count++;
        }
        else{
            fullbase = false;
            break;
        }
    }
    //If base is not complete and the length is 3+ continue
    while(!fullbase && (start_row - (i-1) >= 3)){
        //go to a smaller base
        i++;
        j -= col_count;
        j++;
        l--;
        //lower the length of the triangle
        triangle_counter--;
        col_count = 0;
        //While the numbers go from the left to the right until
        //it reaches the end continue
        while(j <= l){
            //if the starting value equals to the value in ij.
            if(arr[i][j] == numvalue){
                j++;
                fullbase = true;
                col_count++;
            }
            else{
                fullbase = false;
                break;
            }
        }
    }
    return true;
}