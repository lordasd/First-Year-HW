/* Ex1b: Short rows removal
*==================================
* Written by David Zaydenberg
*
* Program is transfering data which are shorter than threshold
* to an array and prints the array and the new data.
*
* Main - takes input of number of line and threshold and calls functions.
*
* Read_data_2d - Allocates 2D array and _lines_len with _num_of_lines
* and then user input the length of a row and sends the length to
* Read_data to allocate the array with this length and input values.
* at the same time the length is saved in _lines_len[i].
*
* Merge_arrays - takes input of threshold in main and uses it to find
* the rows in data that are less than threshold length.
* the new allocated array with length is getting resized with the length
* of the row we found with resize_arr function and copies values in the
* resized arr. Then we call struct_cleanup function which resizes the 
* _data and _lines_len(Cleans up the the rows < threshhold).
* 
* Resize_arr - Creates new array and transfers values deletes old arr
* and returns new arr.
*
* Copy_values - Copy the rest values to fill up the free spots in the array.
*
* Struct_Cleanup - finds new amount of rows for data and lines len.
* Cleans _data and _lines_len and updates _num_of_lines.
*
* Cleaned_rows - Finds the new amount of rows
*
* Clean_Data - Reallocates data with relevant rows(higher than threshold)
* and deletes unnesesery rows and the array itself.
*
* Clean_Lines_len - Reallocates lines_len with rows and 
* relevant lengths(higher than threshold)
*
* Print_Data - Print new array that has values of lower than threshold
* lengths than print length + newdata values
*
* alloc_check_1d/2d - Check for allocation is succeded. (nullptr)
* if the array is nullptr > failed > exit(EXIT_SUCCESS).
*
* free_arr_1d/2d - Frees up memory.
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

//---------Structures_Section---------//
struct Data{
    int** _data;
    int _num_of_lines;
    int* _lines_len;
};

//---------------Prototype_Section---------------//
int** read_data_2d(Data &var);
int* read_data(int length);
int* merge_arrays(Data &var, int threshold, int &length);
int* resize_arr(int* old, int size, int length);
void copy_values(int** from_arr, int* dest_arr, int& res_index, int row,
                 int length);
void struct_cleanup(Data &d, int threshold);
int cleaned_rows(Data &var, int threshold);
int** clean_data(Data &d, int rows, int threshold);
int* clean_lines_len(Data &d, int rows, int threshold);
void alloc_check_1d(int* arr);
void alloc_check_2d(int** arr);
void print_data(const Data &var, const int* arr, int length);
void free_arr_1d(int* arr);
void free_arr_2d(Data &var);

//takes input of number of line and threshold
//and calls functions.
//-------------Main-------------//
int main()
{
    Data d;

    int threshold, length = 0;
    int* arr;

    cin >> d._num_of_lines;

    d._data = read_data_2d(d);

    cin >> threshold;
    arr = merge_arrays(d, threshold, length);

    print_data(d, arr, length);

    free_arr_1d(arr);
    free_arr_1d(d._lines_len);
    free_arr_2d(d);

    return EXIT_SUCCESS;
}

//2d array and lines_len allocation
//------------------Read_Data_2D-------------------//
int** read_data_2d(Data &var)
{
    int length;

    var._lines_len = new(nothrow) int[var._num_of_lines];
    alloc_check_1d(var._lines_len);
    var._data = new(nothrow) int*[var._num_of_lines];
    alloc_check_2d(var._data);

    //Populating each row and saving row length
    //in lines_len array
    for(int i = 0; i < var._num_of_lines; i++)
    {
        cin >> length;
        var._lines_len[i] = length;
        var._data[i] = read_data(length);
    }
    return var._data;
}

//Reads input values into a row
//------------Read_Data-------------//
int* read_data(int length)
{
    int* res = new(nothrow) int[length];
    alloc_check_1d(res);

    for(int i = 0; i < length; i++)
    {
        cin >> res[i];
    }
    return res;
}

//Transfers all values of arrays that are lower than
//threshold to a 1d array. and then resizes Data struct
//-----------Merge_Arrays-------------//
int* merge_arrays(Data &var, int threshold, int &length)
{
    int res_index = 0;
    int* res = new (nothrow) int[length];
    alloc_check_1d(res);

    for(int i = 0; i < var._num_of_lines; i++)
    {
        if(var._lines_len[i] < threshold)
        {
            res = resize_arr(res, var._lines_len[i], length);
            //length grows each time with the new size of 
            //lines_len[i].
            length += var._lines_len[i];
            copy_values(var._data, res, res_index, i, length);
        }
    }
    //Resize the struct with threshold>=length of arrays
    struct_cleanup(var, threshold);

    return res;
}

//Creates new array and transfers values
//deletes old arr and returns new arr
//----------Resize_Arr----------//
int* resize_arr(int* old, int size, int length)
{
    int* new_arr = new(nothrow) int[size+length];
    alloc_check_1d(new_arr);

    //start transfering values if length of old
    //is bigger than 0.
    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
            new_arr[i] = old[i];
        }
    }
    delete[] old;

    return new_arr;
}

//Copy the rest values to fill up the free spots in the array.
//------------Copy_Values-------------//
void copy_values(int** from_arr, int* dest_arr, int& res_index, int row,
                 int length)
{
    for(int col = 0; res_index < length; col++){
        dest_arr[res_index++] = from_arr[row][col];
    }
}

//finds new amount of rows for data and lines len.
//Cleans _data and _lines_len and updates _num_of_lines.
//------------Struct_Cleanup----------//
void struct_cleanup(Data &d, int threshold)
{
    int rows = cleaned_rows(d, threshold);

    d._data = clean_data(d, rows, threshold);
    d._lines_len = clean_lines_len(d, rows, threshold);
    d._num_of_lines = rows;
}

//Finds the new amount of rows
//-------------Cleaned_Rows-------------//
int cleaned_rows(Data &var, int threshold)
{
    int rows = var._num_of_lines;
    for(int i = 0 ; i < var._num_of_lines; i++)
    {
        if(var._lines_len[i] < threshold)
        {
            rows--;
        }
    }

    return rows;
}

//Reallocates data with relevant rows(higher than threshold)
//and deletes unnesesery rows and the array itself.
//------------Clean_Data------------//
int** clean_data(Data &d, int rows, int threshold)
{
    int** new_data = new (nothrow) int*[rows];
    alloc_check_2d(new_data);
    int row = 0;

    for(int i = 0; i < d._num_of_lines; i++)
    {
        if(d._lines_len[i] >= threshold)
        {
            new_data[row++] = d._data[i];
        }
        else{
            delete[] d._data[i];
        }
    }
    delete[] d._data;

    return new_data;
}

//Reallocates lines_len with rows and 
//relevant lengths(higher than threshold)
//--------------Clean_Lines_Len--------------//
int* clean_lines_len(Data &d, int rows, int threshold)
{
    int* new_l_l = new (nothrow) int[rows];
    alloc_check_1d(new_l_l);
    int row = 0;

    for(int i = 0; i < d._num_of_lines; i++)
    {
        if(d._lines_len[i] >= threshold)
        {
            new_l_l[row++] = d._lines_len[i];
        }
    }
    delete[] d._lines_len;

    return new_l_l;
}

//Print new array that has values of lower than threshold lengths
//than print length + newdata values
//----------Print_Data------------//
void print_data(const Data &var, const int* arr, int length)
{
    int row = 0;

    for(int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl << var._num_of_lines << endl;

    for(int i = 0; i < var._num_of_lines; i++)
    {
        cout << var._lines_len[row++] << " ";
        for(int j = 0; j < var._lines_len[i]; j++)
        {
            cout << var._data[i][j] << " ";
        }
        cout << endl;
    }
}

//Allocation check for 1D array
//-------Alloc_Check_1D-------//
void alloc_check_1d(int* arr)
{
    if(arr == nullptr)
    {
        cerr << "Can't allocate memory\n";
        exit(EXIT_FAILURE);
    }
}

//Allocation check for 2D array
//--------Alloc_Check_2D--------//
void alloc_check_2d(int** arr)
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
void free_arr_2d(Data &var)
{
    for(int i = 0; i < var._num_of_lines; i++){
        delete[] var._data[i];
    }
    delete[] var._data;
}