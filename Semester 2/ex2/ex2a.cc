/* Ex2a: Bigger and smaller
*==================================
* Written by David Zaydenberg
*
* Program is taking input(until eof - for windows = ctrl+z.
* for linux = ctrl+d) for a linked list and
* counts how many numbers are bigger than the back and
* smaller than the front except from the first and the last
* numbers which they only refer to their close number.
*
* Main - Summons functions and prints out the amount.
*
* Create_List - Create a list in input order.
*
* Alloc - Allocate and check allocation.
*
* Bigger_Smaller - Check if current node data is bigger than
* back and smaller than front data.
*
* Free_List - Delete all nodes
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
struct Node{
    int _data;
    struct Node *_next;
};

//---------------Prototype_Section---------------//
Node* create_list();
Node* alloc();
int bigger_smaller(Node *head);
void free_list(Node *head);

//Summons functions and prints out the amount.
//-------------Main-------------//
int main()
{
    Node *head = create_list();
    int amount;

    amount = bigger_smaller(head);
    cout << amount << endl;

    free_list(head);

    return EXIT_SUCCESS;
}

//Create a list in input order
//----------Create_list----------//
Node* create_list()
{
    Node *head = NULL,
            *tail = NULL,
            *node;
    int num;

    cin >> num;

    while(!cin.eof())
    {
        node = alloc();
        node->_data = num;
        node->_next = NULL;

        //first node
        if(!head)
        {
            head = node;
            tail = node;
        }
        tail->_next = node;
        tail = node;

        cin >> num;
    }

    if(head == tail && head == node)
    {
        head->_next = NULL;
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

//Check if current node data is bigger than
//back and smaller than front data.
//---------Bigger_Smaller------------//
int bigger_smaller(Node *head)
{
    int amount = 0;
    Node *front = NULL, *rear = NULL;
    front = head;
    rear = head;

    while (head != 0)
    {
        //At starting point
        if(front == rear)
        {
            if(head->_next == NULL)
            {
                return amount+1;
            }
            //move front forward to check
            front = rear->_next;
            if(rear->_data < front->_data)
            {
                amount++;
            }
            //move another time to make space
            //for head in the middle
            if(front->_next != NULL)
            {
                front = front->_next;
                head = head->_next;
                continue;
            }
        }
            //If next for front is null:
        else if(front->_next == NULL)
        {
            //If the head is bigger than the node
            //before and smaller than node after,
            //We can skip next node check(last node).
            if(head->_data > rear->_data &&
               head->_data < front->_data)
            {
                amount += 2;
                return amount;
            }
                //if last number is bigger than head
                //return
            else if(front->_data > head->_data){
                amount++;
                return amount;
            }
            else{
                return amount;
            }
        }
            //All validation in the middle of the list:
        else
        {
            if(head->_data > rear->_data &&
               head->_data < front->_data)
            {
                amount++;
            }
        }
        //move all pointers forward
        rear = rear->_next;
        head = head->_next;
        front = front->_next;
    }

    return amount;
}

//Delete all nodes
//------------Free_List--------------//
void free_list(Node *head)
{
    while(head != NULL)
    {
        Node *temp = head;
        head = head->_next;
        delete temp;
    }
}
