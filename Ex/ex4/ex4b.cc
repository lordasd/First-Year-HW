#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 1000;

int main(){

    int i, num;
    bool exist = false;
    bool occur[N];

    for(i = 1; i < 25; i++){//Outer loop prints 1 - 24 as a first number.
        exist = false;
        num = i;
        while(!exist){
            cout << num;
            if(!occur[num]){
                occur[num] = true;
                if(num % 2 == 0){
                    num /= 2;
                }
                else{
                    num = num*3 + 1;
                }
                cout << " ";
            }
            else{
                exist = true;
            }
        }
        cout << endl; 
    }
    return EXIT_SUCCESS;
}