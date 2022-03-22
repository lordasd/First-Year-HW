/* Ex1c: Adding rows
*==================================
* Written by David Zaydenberg
*
* Program is adding rows on demand.
* By pressing 0-2 in menu, you get different actions.
* 0 - Quit, 1 - Add row, 2 - Print data.
*
* Main - If you choose 1/2, lines_len and data is allocated automatically
* to prepare them for new rows and values.
* If you press 1, it will ask for length and then for values in input_values
* function. After that the new_line will add in add_line function.
*
* input_values - Input values each time you choose new line and length.
*
* add_line - Adds the new line to data. if find_identical_row is true,
* append values. if false, but identical, do nothing.
* if just false add a new line. If first time entering this functions,
* it will add the new_line.
*
* find_identical_row - Searches for identical values. if identical and
* new_line has more, return true and the index of the row too append
* values to the existing row. If values are the same and
* the same length, do nothing, else return false.
*
* realloc_lines_len - Reallocate lines_len to fit one more value(of length).
*
* realloc_data - Reallocate data to fit new row.
*
* realloc_exist_data - Reallocate existing row with new_line
*
* alloc_check_1d/2d - Check for allocation is succeded.
* (nullptr) if the array is nullptr > failed > exit(EXIT_SUCCESS).
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
int* input_values(int line_len);
void add_line(Data &var, const int new_line[], int line_len);
bool find_identical_row(const Data &var, const int new_line[],
                    int line_len, bool& ignore, int& index);
int* realloc_lines_len(Data &var, int line_len);
int** realloc_data(Data &var, const int new_line[] , int line_len);
int* realloc_exist_data(Data &var, const int new_line[], int line_len);
void alloc_check_1d(int* arr);
void alloc_check_2d(int** arr);
void print_data(const Data &var);
void free_arr_1d(int* arr);
void free_arr_2d(Data &var);

//Menu - input option 0-2. 0 - Quit, 1 - Add row, 2 - Print data.
//Prepare lines_len and data by allocating them.
//-------------Main-------------//
int main()
{
    Data d;
    int input, line_len;
    d._num_of_lines = 0;
    bool alloc_prep = false;

    cin >> input;

    while(input != 0)
    {
        //If first time, allocate a preparation.
        if(!alloc_prep){
            d._data = new (nothrow) int*[d._num_of_lines];
            alloc_check_2d(d._data);
            d._lines_len = new (nothrow) int[d._num_of_lines];
            alloc_check_1d(d._lines_len);
            alloc_prep = true;
        }
        //Add new line
        if(input == 1)
        {
            cin >> line_len;
            int* new_line;
            new_line = input_values(line_len);
            add_line(d, new_line, line_len);
        }
        //Print data
        else if(input == 2)
            print_data(d);

        cin >> input;
    }

    //Free memory only if it has been allocated.
    if(input == 0 && alloc_prep)
    {
        free_arr_1d(d._lines_len);
        free_arr_2d(d);
    }

    return EXIT_SUCCESS;
}

//Adds the new line to data.
//if find_identical_row is true, append values.
//if false, but identical, do nothing. if just false
//add a new line.
//---------------Add_Line------------------//
void add_line(Data &var, const int new_line[], int line_len)
{
    if(var._num_of_lines > 0)
    {
        int index;
        bool ignore = false;
        //If true, add up values to an existing row
        if(find_identical_row(var, new_line, line_len, ignore, index)){
            var._lines_len[index] = line_len;
            var._data[index] = realloc_exist_data(var, new_line, line_len);
        }
        else if(ignore)
        {
            ignore = false;
            delete[] new_line;
            return;
        }
        else{
            var._num_of_lines++;
            var._lines_len = realloc_lines_len(var, line_len);
            var._data = realloc_data(var, new_line, line_len);
        }
    }
    else
    {
        var._num_of_lines++;
        var._lines_len = realloc_lines_len(var, line_len);
        var._data = realloc_data(var, new_line, line_len);
    }
}

//Searches for identical values. if identical and new_line
//has more, return true and the index of the row too append
//values to the existing row. If values are the same and
//the same length, do nothing, else return false.
//------------------Find_Identical_Row-------------------//
bool find_identical_row(const Data &var, const int new_line[],
                    int line_len, bool& ignore, int& index)
{
    for(int row = 0; row < var._num_of_lines; row++)
    {
        for(int col = 0; col < var._lines_len[row]; col++)
        {
            //If values are the same
            if(var._data[row][col] == new_line[col])
            {
                //If data length is maxed but line_len is bigger than
                //existing len save index, return true and append values
                if(col == var._lines_len[row]-1 &&
                    line_len > var._lines_len[row])
                {
                    index = row;
                    return true;
                }
                //If we got the same length as the new_line
                //but the length of the data row is equal or
                //bigger the new_line length, ignore it and
                //continue searching for another row.
                else if(col == line_len-1 && 
                        (var._lines_len[row] == line_len ||
                        var._lines_len[row] > line_len) )
                {
                    ignore = true;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }

    return false;
}

//Reallocate lines_len to fit one more value(of length)
//---------------Realloc_lines_len---------------//
int* realloc_lines_len(Data &var, int line_len)
{
    int* new_line_len = new (nothrow) int[var._num_of_lines];
    alloc_check_1d(new_line_len);

    //Copy existing values if they already exist
    if(var._num_of_lines > 1)
    {
        for(int i = 0; i < var._num_of_lines-1; i++)
        {
            new_line_len[i] = var._lines_len[i];
        }
    }

    //last index equals to the new length
    new_line_len[var._num_of_lines-1] = line_len;

    delete[] var._lines_len;

    return new_line_len;
}

//Reallocate data to fit new row
//------------------Realloc_Data---------------------//
int** realloc_data(Data &var, const int new_line[] , int line_len)
{
    int** new_data = new (nothrow) int*[var._num_of_lines];
    alloc_check_2d(new_data);
    int* new_array = new (nothrow) int[line_len];
    alloc_check_1d(new_array);

    //copy values to a new allocated array/row.
    for(int i = 0; i < line_len; i++)
    {
        new_array[i] = new_line[i];
    }

    //Add already existing lines to data
    for(int i = 0; i < var._num_of_lines-1; i++)
    {
        new_data[i] = var._data[i];
    }

    //Add new line to data
    new_data[var._num_of_lines-1] = new_array;

    delete[] var._data;

    return new_data;
}

//Reallocate existing row with new_line
//---------------Realloc_exist_data-----------------//
int* realloc_exist_data(Data &var, const int new_line[], int line_len)
{
    int* new_arr = new (nothrow) int[line_len];
    alloc_check_1d(new_arr);

    for(int i = 0; i < line_len; i++)
    {
        new_arr[i] = new_line[i];
    }

    return new_arr;
}

//Input values into a new line
//--------Input_Values--------//
int* input_values(int line_len)
{
    int* new_line = new (nothrow) int[line_len];
    alloc_check_1d(new_line);

    for(int i = 0; i < line_len; i++)
    {
        cin >> new_line[i];
    }

    return new_line;
}

//Print data
//----------Print_Data------------//
void print_data(const Data &var)
{
    for(int i = 0; i < var._num_of_lines; i++)
    {
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