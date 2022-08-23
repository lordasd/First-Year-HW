/* Ex4a: Finding wanted number in a 2-way linked-list
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is building a linked-list by user-input(until eof(ctrl+z/d))
* with next&prev pointers and calls 6 print functions.
* Program has 6 functions which are build to be inserted into the print func
* as parameters (pointer to a function) and print out the number if there is 
* which meets the condition of the task that has been transfered part of the
* print fun call.
* Each task is done twice: 1)Going forward, 2)Going backward.
* If true, prints out the number, else "0" (6 prints).
* 
*==================================*/
//-------Include_Section---------//
#include <iostream>
#include <cmath>
#include <new>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::nothrow;
using std::cerr;

//-------------Struct_Section---------------//
struct Node{
    int _data;
    struct Node *_next,
                *_prev;
};

//---------------Prototype_Section---------------//
void build_list(Node* &first, Node* &last);
Node* create_node();
bool is_positive(int n);
bool is_prime(int n);
bool is_palindrome(int n);
Node* forward(Node* first);
Node* backward(Node* last);
void print_num(Node* start, bool(*func)(int), Node*(*direction_func)(Node*));
bool space_check(bool (*func)(int), Node* (*direction_func)(Node*));
void free_list(Node *first);

//Calls for linked-list build, prints all possible
//tasks(6), and calls for list deletion.
//-------------Main-------------//
int main()
{
    struct Node *first = nullptr, *last = nullptr;
    
    build_list(first,last);

    print_num(first, is_positive, forward);
    print_num(last, is_positive, backward);
    print_num(first, is_prime, forward);
    print_num(last, is_prime, backward);
    print_num(first, is_palindrome, forward);
    print_num(last, is_palindrome, backward);

    free_list(first);

    return EXIT_SUCCESS;
}

//Builds a list of nodes with prev and next pointers
//-------------Build_List---------------//
void build_list(Node* &first, Node* &last)
{
    Node *node = nullptr;
    int data;

    cin >> data;
    while(!cin.eof())
    {
        node = create_node();
        node->_data = data;
        if(!first)//first node
            first = node;
        else
        {
            last->_next = node;
            node->_prev = last;    
        }
        last = node;
        cin >> data;
    }
}

//Creates a node and defines pointer = NULL
//-----------Create_Node-------------//
Node* create_node()
{
    Node *node = new (nothrow) Node;
    if(node == nullptr)
    {
        cerr << "Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }
    node->_next = node->_prev = nullptr;
    return node;
}

//Function gets a pointer to a chosen node, task and direction.
//Function calls a requested task. if true, prints the number else
//Moves in the requested direction.
//-----------------Print_num---------------------//
void print_num(Node* start, bool (*func)(int), Node* (*direction_func)(Node*))
{
    while(start != nullptr)
    {   //If the number is true for the task
        if(func(start->_data))
        {   //Checks if last func for space issue
            if(space_check(func, direction_func))
                cout << start->_data << endl;   
            else
                cout << start->_data << " ";
            return;
        }
        start = direction_func(start);    
    }//Checks if last func for space issue
    if(space_check(func, direction_func))
        cout << "0\n";
    else
        cout << "0 ";
}

//Checks if the last function is called to sort the spaces issue.
//-------------------Space_Check------------------------//
bool space_check(bool (*func)(int), Node* (*direction_func)(Node*))
{
    if(func == is_palindrome && direction_func == backward)
        return true;
    else
        return false;
}

//Go forward in the list
//---------------Forward---------------//
Node* forward(Node* first){return first->_next;}

//Go back in the list.
//---------------Backward--------------//
Node* backward(Node* last){return last->_prev;}

//Check if the number is a prime
//----------Is_Prime----------//
bool is_prime(int n)
{
    for(int div = 2; div <= sqrt(n); div++)
        if(n % div == 0)
            return false;
    return n <= 1 ? false : true;
}

//Check if the number is possitive
//-----------Is_Positive-----------//
bool is_positive(int n){return n > 0 ? true : false;}

//Check if the number is plaindrome
//---------Is_Palindrome--------//
bool is_palindrome(int n)
{   //rem - remainder, temp will be transfered to reverse
    int reverse = 0, temp = n, rem;

    while(temp != 0)
    {
        rem = temp % 10;
        reverse = reverse * 10 + rem;
        temp /= 10;
    }
    if(reverse == n)//If reversed equal to recieved number
        return true;
    return false;
}

//Delete list memory
//----------Free_List----------//
void free_list(Node *first)
{
    while(first != nullptr)
    {
        Node *temp = first;
        first = first->_next;
        delete temp;
    }
}