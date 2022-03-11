/* Ex9c: Golden Bars problem
*==================================
* Written by David Zaydenberg
*
* Program is trying to split 5 inputed weights between two jewlers.
* Program will try to distribute the weight recursively with backtracking.
*
* Main - Will call for input function to input 5 weights 
* of golden bars(in array). and then call the aux_dist function
* that will prepare all of the variables for the distribution funcion.
*
* input - function that lets you input 5 golden bars.
*
* aux_dist - Prepares 2 aux arrays that the bars will be distributed to.
* with index of each own to be able to use it recursively.
* and lastly a found boolian that will determine if a split have been found.
* calls the distribution function.
* If distribution have been found, print in print_distribution, else
* print Cannot divide.
*
* distribution - is a bool that will get from it self, true(found) or false.
* It will go over the whole main array and start distributing golden bars.
* if the array comes to end of it(index_main = N), it will go to
* validity_check to see if the sum of two aux arrays are equal.
* if yes, return true.
* if not, return false, and continue removing number from first array 
* and moving it to the second one, until validity_check will be true.
*
* validity_check - Will sum aux1_arr and aux2_arr and compare their sum.
* if they are equal, the split have been found and return true.
* if sum is not equal, return false to continue distributing.
*
* print_distribution - If equal sum have been found, print both aux arrays
* and skip zeroes.
* 
*/
//===============================//
//-------Include Section---------//
#include <iostream>
#include <cstdlib>

//-----------Using Section---------//
using std::cout;
using std::cin;
using std::endl;

//--------Const Section----------//
const int N = 5;

//---------------Prototype Section---------------//
void input(int arr[]);
void aux_dist(const int arr[]);
bool distribution(const int arr[], int aux1_arr[], int aux2_arr[],
                int index_main, int index1_arr, int index2_arr, bool found);
bool validity_check(const int aux1_arr[], const int aux2_arr[]);
void print_distribution(const int aux1_arr[], const int aux2_arr[]);

/*Will call for input function to input 5 weights 
of golden bars(in array). and then call the aux_dist function
that will prepare all of the variables for the distribution funcion.*/
//-------------Int main-------------//
int main(){

    int arr[N];

    input(arr);
    
    aux_dist(arr);

    return EXIT_SUCCESS;
}

//function that lets you input 5 golden bars.
//------Input------//
void input(int arr[]){
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
}

/*Prepares 2 aux arrays that the bars will be distributed to.
with index of each own to be able to use it recursively.
and lastly a found boolian that will determine if a split have been found.
calls the distribution function.
If distribution have been found, print in print_distribution, else
print Cannot divide.*/
//-----------Aux_dist-----------//
void aux_dist(const int arr[]){
    int aux1_arr[N] = {0};
    int aux2_arr[N] = {0};
    int index_main = 0;
    int index1_arr = 0;
    int index2_arr = 0;
    bool found = false;

    if(distribution(arr, aux1_arr, aux2_arr, index_main,
                index1_arr, index2_arr, found)){
                    print_distribution(aux1_arr, aux2_arr);
    }
    else{
        cout << "Cannot divide" << endl;
    }

}

/*is a bool that will get from it self, true(found) or false.
It will go over the whole main array and start distributing golden bars.
if the array comes to end of it(index_main = N), it will go to
validity_check to see if the sum of two aux arrays are equal.
if yes, return true.
if not, return false, and continue removing number from first array 
and moving it to the second one, until validity_check will be true.*/
//---------Distribution----------//
bool distribution(const int arr[], int aux1_arr[], int aux2_arr[],
                int index_main, int index1_arr, int index2_arr, bool found){
    
    //Check if the split is found
    if(index_main == N){
        if(validity_check(aux1_arr, aux2_arr)){
            return true;
        }
    }
    //Distribute between aux1_arr and aux2_arr.
    else if(index_main < N){
        aux1_arr[index1_arr] = arr[index_main];
        //If next recursive call is true, return true to end the func
        if(distribution(arr, aux1_arr, aux2_arr, index_main + 1,
                    index1_arr + 1, index2_arr, false)){
                    return true;
        }
        //remove value to distribute to the second array
        aux1_arr[index1_arr] = 0;
        //----------------------------
        aux2_arr[index2_arr] = arr[index_main];
        //If next recursive call is true, return true to end the func
        if(distribution(arr, aux1_arr, aux2_arr, index_main + 1,
                    index1_arr, index2_arr + 1, false)){
                    return true;
        }
        //remove value to distribute to the first array
        aux2_arr[index2_arr] = 0;
    }
    return false;
}

/*Will sum aux1_arr and aux2_arr and compare their sum.
if they are equal, the split have been found and return true.
if sum is not equal, return false to continue distributing.*/
//-------Validity_Check------------//
bool validity_check(const int aux1_arr[], const int aux2_arr[]){
    int sumaux1 = 0, sumaux2 = 0;
    for(int i = 0; i < N; i++){
        sumaux1 += aux1_arr[i];
        sumaux2 += aux2_arr[i];
    }
    if(sumaux1 == sumaux2 && (sumaux1 != 0 || sumaux2 != 0) ){
        return true;
    }
    return false;
}

/*If equal sum have been found, print both aux arrays
and skip zeroes.*/
//--------Print_Distribution--------//
void print_distribution(const int aux1_arr[], const int aux2_arr[]){
    for(int i = 0; i < N; i++){
        if(aux1_arr[i] == 0){
            continue;
        }
        cout << aux1_arr[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < N; i++){
        if(aux2_arr[i] == 0){
            continue;
        }
        cout << aux2_arr[i] << " ";
    }
    cout << endl;
}
