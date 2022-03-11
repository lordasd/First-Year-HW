#include <iostream>

using std::cout;
using std::cin;
using std::endl;

const int N = 8;

int main(){

    int i, j, temp;
    int box[N], counter, looper[N];
    int print_count = 0;
    bool exist = false;

    for(i = 0; i < N; i++){
        cin >> box[i];
        looper[i] = -1; cout << looper[i] << 
    }

    for(counter = 0, i = 0, j = 0; i < N; i++){
        if(box[counter] >= 0 &&  box[counter] < N){
            looper[j] = counter;
            j++;
            counter = box[counter];

            if(box[counter] == looper[0]){
                exist = true;
            }
            
        }
        else{
            counter = i;
            counter++;
            j = 0;
        }
    }
    if(exist){
        for(i = 0; i < N; i++){
            if(looper[0] == looper[i]){
                print_count++;
            }
            if(print_count < 2){
                cout << looper[i] << " ";
            }
        }
        cout << endl;
    

    }

    return EXIT_SUCCESS;
}
