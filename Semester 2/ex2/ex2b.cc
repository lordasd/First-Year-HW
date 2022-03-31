/* Ex2a: Jumps in a circle
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is taking input and creates a circled list which connects
* the last and the first nodes with next and prev pointers.
* Input: ID + jumps. input ends when jumps = 0.
* Program prints the id's with the combination of jumps of each landed
* node until 15 prints or until the jumps land on the node that has jumps = 0.
* 
* Main - Summons functions: create list, print
* jump combination and free the list
*
* create_list - Creates a list in input order that will 
* close the loop with the last and the first node(circle).
*
* alloc - Allocate and check allocation.
*
* print_jump_comb - prints the id's with the combination of jumps of each
* landed node until 15 prints or until the jumps land on the node that
* has jumps = 0.
*
* free_list - Delete all nodes.
*
*==================================*/
//-------Include_Section---------//
#include <iostream>
#include <new>

//-----------Using_Section---------//
using std::cout;
using std::cin;
using std::endl;
using std::nothrow;
using std::cerr;

//--------------Const_Section-------------//
const int N = 15; //Allowed numbers to print

//-------------Struct_Section---------------//
struct Node {
    int _id;
    int _jump;
    struct Node *_next,
            *_prev ;
} ;

//---------------Prototype_Section---------------//
Node* create_list();
Node* alloc();
void print_jump_comb(Node *head);
void free_list(Node *head);

//Summons functions: create list, print
//jump combination and free the list
//-------------Main-------------//
int main()
{
    Node *head = create_list();

    print_jump_comb(head);

    free_list(head);

    return EXIT_SUCCESS;
}

//Create a list in input order that will 
//close the loop with the last and the first node
//----------Create_list----------//
Node* create_list()
{
    Node *head = NULL, *tail = NULL, *node;
    int id = 1, jump;

    while(jump != 0)
    {
        cin >> id >> jump;

        node = alloc();
        node->_id = id;
        node->_jump = jump;
        node->_next = NULL;
        node->_prev = NULL;

        //first node
        if(!head)
        {
            head = node;
            tail = node;
        }
        //In the list
        if(jump != 0)
        {
            tail->_next = node;
            node->_prev = tail;
        }
        //last node closes circle
        else
        {
            tail->_next = node;
            node->_next = head;
            node->_prev = tail;
            head->_prev = node;

        }
        //advance
        tail = node;
    }

    return head;
}

//Allocate and check allocation
//--------------Alloc------------//
Node* alloc()
{
    Node *node = new (nothrow) Node;

    if(node == nullptr)
    {
        cerr << "Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }

    return node;
}

//Prints the id's of nodes in combination of moves
//counted by jumps 
//--------------Print_Jump_Comb---------------//
void print_jump_comb(Node *head)
{   
    //total prints allowed
    int run_count = N;
    //each jump count
    int jump_count;

    while(run_count != 0)
    {   
        //set jump count
        jump_count = head->_jump;
        //print id
        cout << head->_id << " ";
        //Jump positive
        if(head->_jump > 0)
        {
            while(jump_count != 0 && run_count != 0)
            {
                head = head->_next;
                jump_count--;
            }
        }
        //jump negative
        else if(head->_jump < 0)
        {
            while(jump_count != 0 && run_count != 0)
            {
                head = head->_prev;
                jump_count++;
            }
        }
        //jump = 0 = end
        else
        {
            cout << endl;
            return;
        }
        run_count--;
    }
    cout << endl;
}

//Delete all nodes
//------------Free_List--------------//
void free_list(Node *head)
{
    //set last node pointing to NULL.
    Node *ptr = head->_prev;
    ptr->_next = NULL;

    while(head != NULL)
    {
        Node *temp = head;
        head = head->_next;
        delete temp;
    }
}