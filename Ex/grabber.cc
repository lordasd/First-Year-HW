#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int N = 100;

int main(){

    int num, sum = 0;
    int counter = 0;
    ifstream inp;

    inp.open("numbers.txt");

    inp >> num;
    counter++;
    while(!inp.eof()){
        sum += num;
        counter++;
        inp >> num;
    } 

    cout << "Sum: " << sum << " " << "Average: " << sum/counter << endl;

    return EXIT_SUCCESS;
}