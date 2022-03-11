#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

const int N = 100;

int main(){

    char str[N], sum = 0;
    int counter = 0;
    ifstream inp;

    inp.open("chars.txt");

    inp.get(str, N);

    cout << str << endl;

    return EXIT_SUCCESS;
}