#include <iostream>
#include <cstdlib>

using std :: cout;
using std :: cin;
using std :: endl;

void user_input (int arr[]);
void longest_zigzag (int arr1[], int &count, int &num);
void cont_search (int arr2[], int i, int &numcount);

const int N = 6;

int main()
{
	int arr_nums[N];
	int counter, numbers;
  
	counter= 0;
	numbers= 0;
  
	user_input(arr_nums);
	longest_zigzag (arr_nums, counter, numbers);
	cout << numbers << " " << counter<< endl;
    
	return EXIT_SUCCESS;
}
void user_input (int arr[]) {
		for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}
}

void longest_zigzag (int arr1[], int &count, int &num) {
	
	int j = 0;
	int temp = 0;
	
	for (int cell =0; cell< N; cell++)
	{
		cont_search(arr1,cell,count); 
		if (count > j)
		{
			j= count;
			temp = cell;
		}
	}
	count = j;
	num = temp;
}
void cont_search (int arr2[], int i, int &numcount) {
	numcount = 1;
	if (arr2[i] < arr2[i +1])
	{
		numcount ++;
		for (int index = i +1; index< N-1; index++)
		{
			if (numcount %2 == 0)
			{
				if (arr2[index] > arr2[index +1])
				{
					numcount++;
				}
				else
				break;
			}
			else if (numcount %2 != 0)
			{
				if (arr2[index] < arr2[index +1])
				{
					numcount ++;
				}
				else 
				break;
			}
		}
	}
}	

