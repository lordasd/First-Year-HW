/* Ex8a: Simple Recursion
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is running on recursion(no loops).
*
* Program has menu of 13 options.
* You can choose 1 at a time.
* Options:
* 1) Input integers into array of 10 spaces.
* 2) Sum all values in array.
* 3) Bubble sort - sorts from lowest to highest number.
* 4) Value search(Works only if bubble sort was chosen) - 
* Input a value, and check if value is in the array.
* 5) Arithmetic progression - looks if the values are in
* order of an arithmetic progression.
* 6) Prints out the array.
* 7) Prints out the array backwards.
* 8) Fibonacci - Checks if the current
* value(starts from index 2(third number))
* is sum of the two values before it for all the array. 
* 9) Palindrome - Checks if there is a reflection of values
* in each index.
* 10) Check how many sub-arrays are in the array -
* number progression(upwards/downwards)(minimum of 2 numbers).
* 11) Input a start and stop indexes to look for the highest value
* in the sub array you chose. if indexes are invalid, it will search
* the highest value in the array.
* 12) Prints out all prime numbers
* 13) End - Quit.
*
*==================================*/
//----------Include Section-----------//
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <cmath>

//-----------Using Section------------//
using std::cout;
using std::cin;
using std::endl;

//----------Constant Section----------//
const int N = 10;

//------------Prototypes---------------//
void option_menu(int arr[], bool bubbled);
void input_arr(int arr[], int index);
int sum_arr(const int arr[], int index, int sum);
void print_arr(const int arr[], int index);
void print_arr_backwards(const int arr[], int index);
bool arithmetic_progression(const int arr[], int index, bool prog);
bool fibonnaci_check(const int arr[], int index, bool fib);
bool palindrome_check(const int arr[], int index, int index2, bool pal);
bool value_exist(const int arr[], int index, int value, bool exist);
void prime_numbers(const int arr[], int index);
bool check_prime(const int arr[], int index ,int div);
void bubble_sort(int arr[], int index, bool bubbled);
void bubble_move(int arr[], int index_start, int index, int temp);
int highest_value(const int arr[], int index, int f_index, int l_index);
int sub_arrays(const int arr[], int index, int& count, bool &up, bool &down);

//------------Global Vars--------------//
enum OPTION{ARR_INPUT = 1, SUM, BUBL_SORT, EXIST, ARITH_PROG, PRINT_ARRAY,
    PRINT_ARRAY_BACK, FIBO, PALINDROME, SUB_ARR, SUB_VALUE ,PRIME, END};

//Main calls for options menu, until option 13(END) is chosen.
//-------------Main Function-----------//
int main(){

    int arr[N] = {0};
    bool bubbled = false;

    option_menu(arr, bubbled);

    return EXIT_SUCCESS;
}

//Options menu wokrs recursivly - Choosing options from 1-13.

//------------Option_Menu--------------//
void option_menu(int arr[], bool bubbled){

    //All variables for the functions.
    int option;
    int index, index2 ,f_index, l_index;
    int sum, value, count = 0;
    bool prog = false, fib = false, pal = false;
    bool finish = false, exist = false;
    bool up = false, down = false;

    cin >> option;

    switch (option){
        case ARR_INPUT:
            input_arr(arr, N-1);
            break;
        case SUM:
            sum = 0;
            cout << sum_arr(arr, 0, sum) << endl;
            break;
        case BUBL_SORT:
            bubble_sort(arr, N-1, 0);
            bubbled = true;
            break;
        case EXIST:
            if(bubbled){
                cin >> value;
                index = N-1;
                exist = value_exist(arr, index, value, 0);
                if(exist){
                    cout << "1\n";
                }
                else{
                    cout << "0\n";
                }
                break;
            }
            else{
                std::cerr << "Error\n";
                break;
            }
        case PRINT_ARRAY:
            print_arr(arr, N-1);
            cout << endl;
            break;
        case PRINT_ARRAY_BACK:
            print_arr_backwards(arr, 0);
            cout << endl;
            break;
        case ARITH_PROG:
            prog = arithmetic_progression(arr, 0, 1);
            if(prog){
                cout << "1\n";
            }
            else{
                cout << "0\n";
            }
            break;
        case FIBO:
            fib = fibonnaci_check(arr, N-1, 1);
            if(fib){
                cout << "1\n";
            }
            else{
                cout << "0\n";
            }
            break;
        case PALINDROME:
            index2 = N/2;
            pal = palindrome_check(arr, (N-1)/2, index2, 1);
            if(pal){
                cout << "1\n";
            }
            else{
                cout << "0\n";
            }
            break;
        case PRIME:
            prime_numbers(arr, N-1);
            cout << endl;
            break;
        case SUB_VALUE:
            cin >> f_index >> l_index;
            cout << highest_value(arr, N-1, f_index, l_index) << endl;
            break;
        case SUB_ARR:
            cout << sub_arrays(arr, N-1, count, up = false, down = false) << endl;
            break;
        case END:
            finish = true;
            break;
    }

    if(!finish){
        option_menu(arr, bubbled);
    }
}

//Input values into the array
//-----------Input_Arr----------------//
void input_arr(int arr[], int index){
    if(index != 0){
        input_arr(arr, index - 1);
    }
    cin >> arr[index];
}

//Sum all values in the array
//-----------Sum_arr-----------------//
int sum_arr(const int arr[], int index, int sum){
    if(index != N-1){
        sum = sum_arr(arr, index + 1, sum);
    }
    return sum += arr[index];
}

//Prints out the array.
//------------Print_arr--------------//
void print_arr(const int arr[], int index){
    if(index != 0){
        print_arr(arr, index - 1);
    }
    cout << arr[index] << " ";
}

//Prints out the array backwards
//------------Print_arr_backwards--------//
void print_arr_backwards(const int arr[], int index){
    if(index != N-1){
        print_arr_backwards(arr, index + 1);
    }
    cout << arr[index] << " ";
}

//Checks if the array is an arithmetic progression.
//------------Arithmetic_Progression---------------//
bool arithmetic_progression(const int arr[], int index, bool prog){
    if(index != N-1){
        prog = arithmetic_progression(arr, index + 1, prog);
    }
    int sub = arr[1] - arr[0];
    if(!prog){
        return false;
    }
    if(sub == (arr[index] - arr[index - 1]) || (index == 0 && prog)){
        return true;
    }
    return false;
}

//Check if there is a fibonnaci sequence from the third value.
//-------------------Fibonacci_check------------------------//
bool fibonnaci_check(const int arr[], int index, bool fib){
    if(index != 0){
        fib = fibonnaci_check(arr, index - 1, fib);
    }
    if(!fib){
        return false;
    }
    if(index > 2 && arr[index-2]+arr[index-1] == arr[index]){
        return true;
    }
    else if(index > 2 && arr[index-2]+arr[index-1] != arr[index]){
        return false;
    }
    return true;
}

//Checks if there is a plaindrome in the array.
//--------------Palindrome_Check-------------------//
bool palindrome_check(const int arr[], int index, int index2, bool pal){
    if(index != 0 && index2 != N-1){
        pal = palindrome_check(arr, index - 1, index2 + 1 ,pal);
    }
    if(!pal){
        return false;
    }
    if(arr[index] == arr[index2]){
        return true;
    }
    else{
        return false;
    }
    return true;
}

//Check if an inputed value exists in the array.
//--------------Value_Exist-----------------//
bool value_exist(const int arr[], int index, int value, bool exist){
    if(index != 0){
        exist = value_exist(arr, index - 1, value, exist);
    }
    if(exist){
        return true;
    }
    if(arr[index] == value){
        return true;
    }
    return false;
}

// Prints out all prime numbers in array.
// ------------Prime_Numbers------------//
void prime_numbers(const int arr[], int index){
    if (index != 0){
        prime_numbers(arr, index - 1);
        if (arr[index] > 1 && index < N){
            bool prime = false;
            int div = arr[index] / 2;
            prime = check_prime(arr, index, div);
            if (prime){
                cout << arr[index] << " ";
            }
        }
    }
}

//Check if a value in array is a prime number.
// -------------------Check_Prime---------------------//
bool check_prime(const int arr[], int index, int div){
    bool prime = true;
    if (div >= 2){
        prime = check_prime(arr, index, div - 1);
        if (arr[index] % div == 0 && prime && div <= arr[index] / 2)
            return false;
    }
    return prime;
}

//Sorting the array in order. Sends rounds to start from
//in the array
//----------Bubble_Sort---------------//
void bubble_sort(int arr[], int index, bool bubbled){
    if(index != 0){
        bubble_sort(arr, index - 1, bubbled);
    }
    int temp = 0;
    int index_start;
    bubble_move(arr, index_start = index, 0, temp);
}

//Sorts each round it gets in order.
//-----------Bubble_move--------------//
void bubble_move(int arr[], int index_start, int index, int temp){
    if(index < N-1-index_start){
        if(arr[index] > arr[index + 1]){
            temp = arr[index + 1];
            arr[index + 1] = arr[index];
            arr[index] = temp;
        }
        bubble_move(arr, index_start, index + 1, temp);
    }
}

//Searches for the highest value between the sub array that was
//inputed with f_index and l_index. If the indexes are invalid,
//it will search for the highest value in the array.
//--------------Highest_Value---------------//
int highest_value(const int arr[], int index, int f_index, int l_index){
    bool inside = false;
    bool outside = false;
    int max = 0;
    if(index == 0){
        return arr[index];
    }
    max = highest_value(arr, index - 1, f_index, l_index);
    //-------
    if(f_index > l_index || f_index > N-1 || f_index < 0 ||
       l_index < 0 || l_index > N-1){
        outside = true;
    }
    else{
        inside = true;
    }
    if(inside && index > l_index){
        return max;
    }
    if(outside){
        if(arr[index] > max){
            return arr[index];
        }
        else{
            return max;
        }
    }
    else if(index >= f_index && index <= l_index && inside){
        if(arr[index] > max){
            return arr[index];
        }
        else{
            return max;
        }
    }
    return max;
}

//Count how many sub arrays are in the array.
//subarray - number progression(upwards/downwards).
//--------------Sub_Arrays--------------//
int sub_arrays(const int arr[], int index, int& count, bool &up, bool &down){
    int subs = 0;
    if(index != 0){
        subs = sub_arrays(arr, index - 1, count, up = false, down = false);
    }
    //-------
    if(arr[index] < arr[index + 1]){
        up = true;
        count++;
        if(down && count >= 2){
            subs++;
            count = 0;
        }
        else if(down && count < 2){
            count = 0;
        }
        down = false;
    }
    else if(arr[index] > arr[index + 1]){
        down = true;
        count++;
        if(up && count >= 2){
            subs++;
            count = 0;
        }
        else if(up && count < 2){
            count = 0;
        }
        up = false;
    }
    if(count >= 2 && index == N-1){
        subs++;
    }
    return subs;
}