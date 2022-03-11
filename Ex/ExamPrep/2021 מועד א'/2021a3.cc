#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::cin;

int string_to_int(char str[]);
int convert(char str[], int index, int num);

int main(){

    char str[5] = {'1', '4', '6', '2', '\0'};

    cout << string_to_int(str) << endl;

    return EXIT_SUCCESS;
}

//Function gets str from main.
//Sends str, number, and index to convert function
//to do all the conversion.
int string_to_int(char str[]){
    unsigned int num = 0;
    int index;

    //start from index 0.
    return convert(str, 0, num);
}

//Convert each char to integer.
int convert(char str[], int index, int num){
    //When str gets to the end of it's string
    //return the result number.
    if(str[index] == '\0'){
        return num;
    }
    //str - '0' it will show exactly the integer number.
    num += (str[index] - '0');
    //Multiply by 10 to add the next number
    //But if it's the last index, don't add more.
    if(index < strlen(str) - 1){
        num *= 10;
    }
    //continue to the next index.
    num = convert(str, index + 1, num);
    return num;
}