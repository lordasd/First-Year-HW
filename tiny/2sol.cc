//--------------include section----------------------- 
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <fstream>

//---------------using section------------------------
using std::cin;  
using std::cout;
using std::endl;

int *allocate_and_read_array(int size);
void count_even_and_odd( int *arr, int size);

//------------------main section----------------------
int main ()
{
    int *arr;
    int num;
    
    cin >> num;
    arr = allocate_and_read_array( num);
    count_even_and_odd(arr, num);
    delete [] arr;
    return EXIT_SUCCESS;
} 

int *allocate_and_read_array(int size)
{
    int *arr = new (std::nothrow) int[size];
    for (int i = 0; i < size; i++)
        cin >> arr[i];
        
    return arr;
}

void count_even_and_odd( int *arr, int size)
{
    int num_even = 0;
    for (int i = 0; i < size; i++)
        if (arr[i]%2 == 0)
            num_even++;
            
    cout << num_even << " " << size-num_even << endl;
}