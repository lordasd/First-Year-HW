/* Ex1b: Short rows removal
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
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
int** read_data_2d(struct Data &d);
int* read_data(int length);
void aloc_check_1d(int* arr);
void aloc_check_2d(int** arr);
void print_data(const struct Data &d);
void free_arr_1d(struct Data &d);
void free_arr_2d(struct Data &d);

//-------------Main-------------//
int main()
{
    struct Data d;
    cin >> d._num_of_lines;

    d._data = read_data_2d(d);

    print_data(d);

    free_arr_1d(d);
    free_arr_2d(d);

    return EXIT_SUCCESS;
}

//2d array and lines_len allocation
//------------------Read_Data_2D-------------------//
int** read_data_2d(struct Data &d)
{
    int length;
    
    d._lines_len = new(nothrow) int[d._num_of_lines];
    aloc_check_1d(d._lines_len);
    d._data = new(nothrow) int*[d._num_of_lines];
    aloc_check_2d(d._data);

    //Populating each row and saving row length
    //in lines_len array
    for(int i = 0; i < d._num_of_lines; i++)
    {
        cin >> length;
        d._lines_len[i] = length;
        d._data[i] = read_data(length);
    }
    return d._data;
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

void print_data(const struct Data &d)
{
    for(int i = 0; i < d._num_of_lines; i++)
    {
        for(int j = 0; j < d._lines_len[i]; j++)
        {
            cout << d._data[i][j] << " ";
        }
    }
}

//Free 1D array memory
//------Free_Arr_1D------//
void free_arr_1d(struct Data &d)
{
    delete[] d._lines_len;
}

//Free 2D array memory
//-------Free_Arr_2D------//
void free_arr_2d(struct Data &d)
{
    for(int i = 0; i < d._num_of_lines; i++){
        delete[] d._data[i];
    }
    delete[] d._data;
}