#include <iostream>
#include <new>

using std::cout;
using std::cin;
using std::endl;
using std::nothrow;

int* aloc(int size);
void read_number(int* arr, int size);
int even_odd(int* arr, int size);

int main()
{
    int* arr;
    int size;
    int even;

    cin >> size;

    arr = aloc(size);

    read_number(arr, size);

    even = even_odd(arr, size);

    delete[] arr;

    cout << even << " " << size-even << endl;

    return EXIT_SUCCESS;
}

int* aloc(int size)
{
    int* arr = new (nothrow) int[size];
    if(arr == nullptr){
        std::cerr << "Couldn't allocate memory" << endl;
        exit(EXIT_FAILURE);
    }

    return arr;
}

void read_number(int* arr, int size)
{
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }
}

int even_odd(int* arr, int size)
{
    int even = 0;

    for(int i = 0; i < size; i++){
        if(arr[i] % 2 == 0){
            even++;
        }
    }
    return even;
}