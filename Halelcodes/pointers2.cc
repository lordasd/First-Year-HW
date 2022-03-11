/* Sums 2 arrays into 1.*/
#include <iostream>
#include <cstdlib>
#include <new>
//------------------------------------
int** read_data_2d(int rows);
int* readData();
int** merge_array_2d(int** arr1, int** arr2, int rows);
int* resize_array(int* old_array, int old_size, int new_size);
int* merge_array_1d(int* arr1, int* arr2);
void copy_array(int* dst, int* src, int start, int end);
int max(int n1, int n2);
int search_size(int* arr);
void print_p_mat(int** arr, int rows);
void free_mat(int** mat, int rows);
//---------------------------------------

int main()
{   
	int **arr1, **arr2, **arr3, rows;

	std::cin >> rows;

	arr1 = read_data_2d(rows);
	arr2 = read_data_2d(rows);

	arr3 = merge_array_2d(arr1, arr2, rows);

	print_p_mat(arr3, rows);

	free_mat(arr1, rows);
	free_mat(arr2, rows);
	free_mat(arr3, rows);

	return EXIT_SUCCESS;
}

//Read data into a 2D array
int** read_data_2d(int rows)
{
	int** res;

	res = new (std::nothrow) int*[rows];
	if(res == NULL)
	{
		std::cerr << "can't allocate\n";
		exit(EXIT_FAILURE);
	}

    //Read data for each row
	for(int i = 0; i < rows; i++)
	{
		res[i] = readData();
	}

	return res;
}

//Reads data into an array and dynamicaly upsizes the array
//size_arr*2.
int* readData()
{
	int* arr;
	int size_array = 1;
	int size_data = 0;
	arr = new (std::nothrow) int[1];

	std::cin >> arr[size_data];
	size_data++;

	while(arr[size_data - 1] != 0)
	{
		if(size_data == size_array)
		{
			arr = resize_array(arr, size_array, size_array * 2);
			size_array *= 2;
		}
		std::cin >> arr[size_data];
		size_data++;
	}

	if(size_data != size_array)
	{
		arr = resize_array(arr, size_array, size_data);
	}

	return arr;
}

//Resizing array each time it reaches maximum size until input 0.
//Alocating new memory, transfering all data to new memory and
//freeing old memory.
int* resize_array(int* old_array, int old_size, int new_size)
{
	int* new_array = new (std::nothrow) int[new_size];

	for(int i = 0; i < new_size && i < old_size; i++)
		new_array[i] = old_array[i];

	delete [] old_array;

	return new_array;
}

//Create a new 2D array-mem alocation
int** merge_array_2d(int** arr1, int** arr2, int rows)
{
	int** res = new (std::nothrow) int*[rows];

	for(int i = 0; i < rows; i++)
		res[i] = merge_array_1d(arr1[i], arr2[i]);

	return res;
}

//
int* merge_array_1d(int* arr1, int* arr2)
{
	int* res;
	int i;
	int size1 = search_size(arr1);
	int size2 = search_size(arr2);
	int max_size = max(size1, size2);

	res = new (std::nothrow) int[max_size];

	for(i = 0; i < size1 && i < size2; i++)
	{
		res[i] = arr1[i] + arr2[i];
	}

	if(i < size1)
	{
		copy_array(res, arr1, i, size1);
	}
	else
	{
		copy_array(res, arr2, i, size2);
	}

	return res;
}

int search_size(int* arr)
{
	int i;
	for(i = 0; arr[i] != 0; i++);

	return i + 1;
}

int max(int n1, int n2)
{
	return n1 > n2 ? n1: n2;
}

void copy_array(int* dst, int* src, int start, int end)
{
	for(int i = start; i < end; i++)
		dst[i] = src[i];
}

void print_p_mat(int** arr, int rows)
{
	for(int row = 0; row < rows; row++)
	{
		for(int col = 0; arr[row][col] != 0; col++)
			std::cout << arr[row][col] << " ";

		std::cout << std::endl;
	}
}

void free_mat(int** mat, int rows)
{
	for(int i = 0; i < rows; i++)
		delete [] mat[i];

	delete [] mat;
}