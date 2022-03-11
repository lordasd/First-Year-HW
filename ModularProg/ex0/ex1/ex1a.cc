/* Ex1a: Sum 2D array values
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is allocation 2D array and sums all the values and prints it.
*
* Main - Asks for number of lines and calls functions.
*
* Read_data_2d is allocating memory for the 2d array and saves the length
* of a row. row length saves into lines_len arr and calls read_data.
* read_data allocates memory to a row(1d array) and inputs values.
*
* sum_values - Sums up all values in the arr and prints out.
*
* Free_arr_1D & free_arr_2d freeing memory.
*
*==================================*/
//-------Include_Section---------//
#include <iostream>
#include <new>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::nothrow;
using std::cerr;

//---------------Prototype_Section---------------//
int** read_data_2d(int num_of_lines, int*& lines_len);
int* read_data(int length);
int sum_values(int** arr, int* lines_len, int num_of_lines);
void aloc_check_1d(int* arr);
void aloc_check_2d(int** arr);
void free_arr_1d(int* arr);
void free_arr_2d(int** arr, int num_of_lines);

//Asks for number of lines and calls functions
//-------------Main-------------//
int main()
{
    int** arr;
    int* lines_len;
    int num_of_lines;

    cin >> num_of_lines;

    arr = read_data_2d(num_of_lines, lines_len);

    cout << sum_values(arr, lines_len, num_of_lines) << endl;

    free_arr_1d(lines_len);
    free_arr_2d(arr, num_of_lines);

    return EXIT_SUCCESS;
}

//2d array and lines_len allocation
//------------------Read_Data_2D-------------------//
int** read_data_2d(int num_of_lines, int*& lines_len)
{
    int length;
    
    lines_len = new(nothrow) int[num_of_lines];
    aloc_check_1d(lines_len);
    int** res = new(nothrow) int*[num_of_lines];
    aloc_check_2d(res);

    //Populating each row and saving row length
    //in lines_len array
    for(int i = 0; i < num_of_lines; i++)
    {
        cin >> length;
        lines_len[i] = length;
        res[i] = read_data(length);
    }

    return res;
}

//Reads input values into a row
//------------Read_Data-------------//
int* read_data(int length)
{
    int* res = new(nothrow) int[length];
    aloc_check_1d(res);

    for(int i = 0; i < length; i++)
    {
        cin >> res[i];
    }
    
    return res;
}

//Sums up all values in arr
//---------------Sum_Values----------------//
int sum_values(int** arr, int* lines_len, int num_of_lines)
{
    int sum = 0;

    for(int i = 0; i < num_of_lines; i++)
    {
        for(int j = 0; j < lines_len[i] ; j++)
        {
            sum += arr[i][j];
        }
    }
    
    return sum;
}

//Allocation check for 1D array
//-------Aloc_Check_1D-------//
void aloc_check_1d(int* arr)
{
    if(arr == nullptr)
    {
        cerr << "Can't allocate memory\n";
        exit(EXIT_FAILURE);
    }
}

//Allocation check for 2D array
//--------Aloc_Check_2D--------//
void aloc_check_2d(int** arr)
{
    if(arr == nullptr)
    {
        cerr << "Can't allocate memory\n";
        exit(EXIT_FAILURE);
    }
}

//Free 1D array memory
//------Free_Arr_1D------//
void free_arr_1d(int* arr)
{
    delete[] arr;
}

//Free 2D array memory
//-------Free_Arr_2D------//
void free_arr_2d(int** arr, int num_of_lines)
{
    for(int i = 0; i < num_of_lines; i++){
        delete[] arr[i];
    }
    delete[] arr;
}