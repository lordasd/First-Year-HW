/*
 *Ex#9c: The Golden Eggs
 * ==============================================
 * written by: Rotem Kashani, id:209073352, login=rotemkash
 
 * this program get 5 numbers and find way to divide them between 2 persons
 equal way. if sum of all values cannot divided with 2 equally the program 
 don't print nothing. if it is way to divide, the program will print the first
person (helf sum) and then print the secound person numbers(the other half sum)

 * input: for exemple: 1 2 5 6 8
  
 * output: 1 2 8
			5 6
 */

//~~~~~~~~~~~~~~~~~include section~~~~~~~~~~~~~
#include <iostream>
#include <cstdlib>

//~~~~~~~~~~~~~~~~~using section~~~~~~~~~~~~~~~
using std::cout;
using std::cin;
using std::endl;

//~~~~~~~~~~~~~~~~~const section~~~~~~~~~~~~~~~
const int N=5; // size of array

//~~~~~~~~~~~~~~~~~prototypes~~~~~~~~~~~~~~~~

void read_data(int arr[]);
void manager(const int arr[]);
void golden_eggs(const int arr[], int n1[], int n2[],
	 int index, int i_n1, int i_n2, bool &found);
void print(const int print[]);
int sum(const int arr_sum[]);
void reset_array(int arr[]);

//~~~~~~~~~~~~~~~~~main section~~~~~~~~~~~~~~~~
int main(){

	int arr[N]; // save inputs
	read_data(arr);

	manager(arr);

    return EXIT_SUCCESS;

}

//manage all process
void manager(const int arr[]){

	int index=0; //index divided start from

	int n1[N]; //save first man result
	int n2[N]; //save second man result

	int i_n1 =0; //first man index for run over arr
	int i_n2 =0; //second man index for run over arr

	bool found = false;//if found solution stop the program

	reset_array(n1);
	reset_array(n2);

	golden_eggs(arr,n1,n2,index, i_n1,i_n2, found);


}
//~~~~~~~~~~~~~~~~~~~reset array~~~~~~~~~~~~~~~
void reset_array(int arr[]){
	for(int i=0; i < N; i++)
		arr[i] = -1;
}
//~~~~~~~~~~~fill array with inputs~~~~~~~~~~~~~~
void read_data(int arr[]){
	for(int i=0; i < N; i++)
		cin >> arr[i];
}
/* ---------- golden_eggs_Function --------- */
void golden_eggs(const int arr[], int n1[], int n2[],
	 int index, int i_n1, int i_n2, bool &found){

	if(index == N && !found)
        if(sum(n1)==sum(n2)) //if found solotion print
        {
            print(n1);
            print(n2);
            found = true; //for print only one time
            return;
        }

	if(index<N) //keep run until end of array
    {
        n1[i_n1] = arr[index];
        golden_eggs(arr, n1, n2, index+1, i_n1+1, i_n2, found);
        n1[i_n1] = -1;
        n2[i_n2] = arr[index];
        golden_eggs(arr, n1, n2, index+1, i_n1, i_n2+1,found);
        n2[i_n2]=-1;
	}
}

//~~~~~~~~~~~calc sum of array~~~~~~~~~~~~~~
int sum(const int arr_sum[]){
	
    int sum = 0;
	for(int i = 0; i< N && arr_sum[i]!=-1; i++)
	{
		sum += arr_sum[i];
	}
	return sum;
}

//~~~~~~~~~~print result after found solotion~~~
void print(const int p[]){
	
    int i = 0;

		while(p[i] != -1 && i<N)
		{
			cout << p[i]<< " ";
			i++;
		};
		cout << endl;
}