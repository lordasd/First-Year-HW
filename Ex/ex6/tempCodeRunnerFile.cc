/* Ex6b: Isosceles triangle in a 2D-Array
*========================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* This program
* 
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
//------------Main--------------//
int main(){

    int arr[ROWS][COLS];
    
    input_arr(arr);

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

//Finding a starting point for a trianlge
//----------Find_Triangle----------//
void find_triangles(const int arr[][COLS]){

    int i,j;
    int row, col;
    int value;
    bool exist_triangle = false;
    int triangle_length;
    int longest_triangle = 0;
    int longest_amount = 0;

    for(i = 0; i < ROWS; i++){
        for(j = 0; j < COLS; j++){
            //If the there are standing and inverted triangles
            //from this point check them both.
            if( (arr[i][j] == arr[i+1][j+1]) && 
                (arr[i][j] == arr[i+1][j-1]) && 
                (arr[i][j] == arr[i-1][j-1]) &&
                (arr[i][j] == arr[i-1][j+1]) &&
                 i < ROWS-2 && j >= 2 && j < COLS-2 &&
                 i >= 2 && j >= 2 && j < COLS-2){
                //Save value
                value = arr[i][j];
                //Save starting point
                row = i; col = j;
                exist_triangle = true;
                //Check and count the length of the triangle in the function
                triangle_length = standing_triangle(arr, exist_triangle, i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 1;
                        longest_triangle = triangle_length;
                    }
                    longest_amount++;
                    cout << row << " " << col << ": " << triangle_length << " standing." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }
                //Now do check the inverted triangle
                triangle_length = inverted_triangle(arr, exist_triangle, i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    cout << row << " " << col << ": " << triangle_length << " inverted." << " Value: " << value << endl;
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
                triangle_length = standing_triangle(arr, exist_triangle, i, j);
                
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    cout << row << " " << col << ": " << triangle_length << " standing." << " Value: " << value << endl;
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
                triangle_length = inverted_triangle(arr, exist_triangle, i, j);
                if(triangle_length > 0){
                    //Save each time the longest length triangle and reset
                    //the amount of them.
                    if(triangle_length > longest_triangle){
                        longest_amount = 0;
                        longest_triangle = triangle_length;
                    }
                    if(longest_triangle == triangle_length){
                        longest_amount++;
                    }
                    cout << row << " " << col << ": " << triangle_length << " inverted." << " Value: " << value << endl;
                }
                else{
                    exist_triangle = false;
                }
            }
            else{
                exist_triangle = false;
                continue;
            }
        }
    }
    cout << longest_amount << " " << longest_triangle << endl;
}

//Counting a standing triangle
//----------Standing_Triangle----------//
int standing_triangle(const int arr[][COLS],
                      bool start_triangle, int i, int j){

    int value = arr[i][j];
    bool finished_triangle = false;
    int triangle_counter = 1;
    int k = i;
    int l = j;
    int start_row = i;

    //While trianle still exist, continue calculating
    while(start_triangle){
        //If both sides are equal and still have the same starting value.
        if(arr[i+1][j-1] == arr[k+1][l+1] && arr[i+1][j-1] == value){
                triangle_counter++;
                i++;k++;
                j--;l++; 
        }
        else{
            start_triangle = false;
        }
    }
    if(triangle_counter >= 3){
    
        finished_triangle = stand_triangle_base(arr, i, j, k ,l, start_row, triangle_counter);
        if(triangle_counter >= 3){
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

//Counting an inverted triangle
//-------------Inverted_Triangle---------//
int inverted_triangle(const int arr[][COLS],
                      bool start_triangle, int i, int j){
    
    int value = arr[i][j];
    bool finished_triangle = false;
    int triangle_counter = 1;
    int k = i;
    int l = j;
    int start_row = i;

    while(start_triangle){
        if(arr[i-1][j-1] == arr[k-1][l+1] && arr[i-1][j-1] == value){
            triangle_counter++;
            i--;k--;
            j--;l++;
        }
        else{
            start_triangle = false;
        }
    }
    if(triangle_counter >= 3){
        finished_triangle = invert_triangle_base(arr, i, j, k, l, start_row, triangle_counter);
        if(triangle_counter >= 3){
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

    int numvalue = arr[i][j];
    bool fullbase = true;

    while(j <= l){
        if(arr[i][j] == numvalue){
            j++;
            fullbase = true;
        }
        else{
            fullbase = false;
            break;
        }
    }
    while(!fullbase && ((i+1)-start_row) >= 3){
        i--;j++;
        l--;
        triangle_counter--;
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

    int numvalue = arr[i][j];
    bool fullbase = true;

    while(j <= l){
        if(arr[i][j] == numvalue){
            j++;
            fullbase = true;
        }
        else{
            fullbase = false;
            break;
        }
    }
    while(!fullbase && (start_row - (i-1) >= 3)){
        i++;j++;
        l--;
        triangle_counter--;
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