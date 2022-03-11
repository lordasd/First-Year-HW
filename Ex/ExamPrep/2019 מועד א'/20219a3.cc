#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;

const int N = 6;

bool find_match(const char str1[], const char str2[]);
bool compare(const char str1[], const char str2[],
             int indx1, int indx2, bool &equal);
int highest_sum(const int arr[]);
int find_highest_sum(const int arr[], int index, int &max_index,
                     int &max_sum);
int sum_of_value(const int value, const int arr[], int index);

int main(){

    char str1[4] = {'a', 'b', 'c', '\0'};
    char str2[4] = {'a', 'b', 'c', '\0'};
    int arr[N] = {5, 5, 3, 8, 8, 3};

    // if(find_match(str1, str2)){
    //     cout << "Yes" << endl;
    // }
    // else{
    //     cout << "No" << endl;
    // }

    cout << highest_sum(arr) << endl;

    return EXIT_SUCCESS;
}

// //Task A:
// bool find_match(const char str1[], const char str2[]){
//     int i, j;
//     if(strlen(str1) == strlen(str2)){
//         for(i = 0, j = 0; i < strlen(str1) && j < strlen(str2); i++, j++){
//             if(str1[i] == str2[j]){
//                 continue;
//             }
//             else{
//                 return false;
//             }
//         }
//     }
//     else{
//         return false;
//     }

//     return true;
// }

// // Task B: Recursion.
// bool find_match(const char str1[], const char str2[]){
//     int indx1;
//     int indx2;
//     bool equal = false;

//     if(strlen(str1) == strlen(str2)){
//         if(compare(str1, str2, 0, 0 ,equal = false)){
//             return true;
//         }
//     }
//     return false;
// }

// bool compare(const char str1[], const char str2[],
//         int indx1, int indx2, bool &equal){
//     if(indx1 < strlen(str1) && indx2 < strlen(str2)){
//         if(str1[indx1] == str2[indx2]){
//             compare(str1, str2, indx1+1, indx2+1, equal = true);
//         }
//         else{
//             return equal = false;
//         }
//     }
//     return equal;
// }

//Task C: Find highest sum of equal values in array.
// int highest_sum(const int arr[]){

//     int num, max_num;
//     int sum = 0, highest_sum = 0;
//     int i, j;
//     bool first_num = false;

//     //each number goes over the whole array.
//     for(i = 0; i < N; i++){
//         for(j = 0; j < N; j++){
//             //Skip the same index.
//             if(i == j){
//                 continue;
//             }
//             if(arr[i] == arr[j]){
//                 //if it's the first time appearing,
//                 //save it, and save in sum.
//                 if(!first_num){
//                     num = arr[i];
//                     first_num = true;
//                     sum = num;
//                 }
//                 //add the num to the sum each time.
//                 sum += num;
//             }
//         }
//         if(sum > highest_sum){
//             highest_sum = sum;
//             max_num = num;
//         }
//         //reset values.
//         sum = 0;
//         first_num = false;
//     }
//     return max_num;
// }

//Task D:
int highest_sum(const int arr[]){
    int index;
    int max_index, max_sum;
    return find_highest_sum(arr, 0, max_index, max_sum);
}

int find_highest_sum(const int arr[], int index, int &max_index,
                     int &max_sum){
    int curr_sum = 0;
    if(index == N){
        return max_index;
    }
    curr_sum = sum_of_value(arr[index], arr, index);
    index++;
    if(curr_sum > max_sum){
        max_sum = curr_sum;
        max_index = arr[index];
    }
    return(find_highest_sum(arr, index, max_index, max_sum));
}

int sum_of_value(const int value, const int arr[], int index){
    if(index == N){
        return 0;
    }
    if(arr[index] == value){
        return arr[index] + sum_of_value(value, arr, index++);
    }
    else{
        return sum_of_value(value, arr, index++);
    }
}