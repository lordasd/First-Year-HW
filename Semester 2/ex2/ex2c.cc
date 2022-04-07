/* Ex2c: List of lists
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program builds a data structure made in rows.
* prints the structure and connects all wanted nodes
* together and prints the data to the right of the nodes.
*
* input: row length and data(numbers for the row).
* 0 will terminate the input.
*
* Main - Summons functions: build_ds, print_ds, link_wanted,
* print_wanted - asks for input: wanted(the data to search 
* and link their nodes).
* 
* build_ds - Build Data structure. input row length and datas.
* first node will have data 0 and other will have the input.
* 
* alloc - Allocate and check allocation.
*
* print_ds - Prints Data structure
*
* link_wanted - Finding wanted data and linking
* all of them through down pointer.
*
* print_wanted - Print the data/value of the node
* right to wanted nodes
*
* free_ds - Delete all nodes.
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

//-------------Struct_Section---------------//
struct Node {
    int _data;
    Node *_right, *_down;
} ;

//---------------Prototype_Section---------------//
Node* build_ds();
Node* alloc();
void print_ds(Node *my_ds);
void link_wanted(Node *my_ds, int wanted);
void print_wanted(Node *my_ds, int wanted);
void free_ds(Node *my_ds);

//-------------Main-------------//
int main()
{
    struct Node *my_ds = build_ds();
    print_ds(my_ds);

    int wanted;
    cin >> wanted;
    link_wanted(my_ds, wanted);
    print_wanted(my_ds, wanted);

    free_ds(my_ds);

    return EXIT_SUCCESS;
}

//Build Data structure. input row and data
//first node will have data 0 and other, input.
//------------Build_Ds------------//
Node* build_ds()
{
    Node *head = NULL, *downhead = NULL, *tail = NULL,
            *node;
    int length, num;

    cin >> length;
    //Until 0 wasn't entered
    while(length != 0)
    {
        node = alloc();
        //first time set head
        if(!head)
        {
            head = node;
            downhead = node;
            tail = node;
            tail = head;
            tail->_data = 0;
        }
        //allocate a row of nodes
        while(length != 0)
        {
            cin >> num;
            node = alloc();
            node->_data = num;
            tail->_right = node;
            tail = node;
            length--;
        }
        cin >> length;
        //If len > 0 create a starting node downwards
        if(length > 0)
        {
            node = alloc();
            node->_data = 0;
            downhead->_down = node;
            downhead = node;
            tail = node;
        }
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
    //Set NULLS
    node->_right = NULL;
    node->_down = NULL;

    return node;
}

//Prints whole data structure
//-------------Print_Ds-----------//
void print_ds(Node *my_ds)
{
    Node *tail;

    while(my_ds != NULL)
    {
        tail = my_ds;
        while(tail != NULL)
        {
            cout << tail->_data << " ";
            tail = tail->_right;
        }
        cout << endl;
        my_ds = my_ds->_down;
    }
}

//Finding wanted data and linking
//all of them through down pointer.
//------------Linked_Wanted------------//
void link_wanted(Node *my_ds, int wanted)
{
    Node *head, *tail = NULL, *found = NULL;
    head = my_ds;
    tail = my_ds;
    bool first_found = false;;

    //While rows arent over
    while(head != NULL)
    {
        //While row isn't over
        while(tail != NULL)
        {
            if(wanted == tail->_data)
            {   
                //first time found
                if(!first_found)
                {
                    found = tail;
                    first_found = true;
                    break;
                }
                else{
                    found->_down = tail;
                    found = tail;
                    break;
                }
            }
            else
            {
                tail = tail->_right;
            }
        }
        //Go row down
        head = head->_down;
        tail = head;
    }
}

//Print the data of the node right to wanted nodes
//-----------Print_Wanted-----------//
void print_wanted(Node *my_ds, int wanted)
{
    Node *tail, *temp;
    tail = my_ds;
    bool found = false;

    //rows
    while(my_ds != NULL)
    {   
        //row
        while(tail != NULL)
        {
            if(wanted == tail->_data)
            {
                found = true;
                temp = tail->_right;
                if(temp == NULL)
                {
                    cout << "0" << " ";
                }
                else
                {
                    cout << temp->_data << " ";
                }
                //Next linked wanted node
                tail = tail->_down;
            }
            //Advance to find wanted node
            else
            {
                tail = tail->_right;
            }
        }
        //If the wanted node was found
        //it probably got to the end.
        if(found)
        {
            break;
        }
        my_ds = my_ds->_down;
        tail = my_ds;
    }
    cout << endl;
}

//Delete all nodes
//-----------Free_Ds-----------//
void free_ds(Node *my_ds)
{
    Node *tail, *temp;

    while(my_ds != NULL)
    {   
        //Prepares a new row
        tail = my_ds;
        my_ds = my_ds->_down;
        //Deletes a row
        while(tail != NULL)
        {
            temp = tail;
            tail = tail->_right;
            delete temp;
        }
    }
}