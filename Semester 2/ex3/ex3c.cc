/* Ex3c: Biggest subtree with even > odd numbers
*===============================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program is taking data input until eof(alt+z/d) and creates a bst.
* Searches for the subtree that has even > odd numbers and prints it.
*
* Main - calls functions.
* Creates bst, Gets subtree, prints subtree and frees memory. 
*
* Create_tree - Creates a binary search tree. Input a number until eof(alt+z/d)
* Node is created, data in inserted in the node, and then
* the node is inserted into the tree in insert_node().
*
* New_Node - Create a node. left+right = NULL
*
* Insert_Node - Insert a node to a tree
*
* Get_Subtree - Prepares even,odd and max_even for comparison
* and calls find_subtree to find the subtree.
*
* Find_Subtree - //Function goes to the leafes(left, then right) and checks
* each node if the data is even/odd and collects the amount
* and compares between them when there is a valid subtree.
* If we are in a valid subtree and even>odd, save the subtree. 
*
* Print_Subtree - Prints the subtree _data.
*
* Free_Tree - Free all tree memory
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
    Node *_left, *_right;
};

//---------------Prototype_Section---------------//
Node* create_tree();
Node* new_node();
void insert_node(Node *&root, Node *node);
Node* get_subtree(Node *root);
void find_subtree(Node *root, Node *&subtree, size_t& even,
                  size_t& odd, size_t& max_even);
void print_subtree(Node *subtree);
void free_tree(Node *root);

//Main calls functions.
//Creates bst, Gets subtree, prints subtree and frees memory 
//-------------Main-------------//
int main()
{
    Node *root = create_tree();
    if(root != nullptr)
    {
        Node *subtree = get_subtree(root);
        print_subtree(subtree);
        free_tree(root);
    }
    else
        cout << "NOT FOUND";

    return EXIT_SUCCESS;
}

//Creates a binary tree. Input a number until eof(alt+z/d)
//Node is created, data in inserted in the node, and then
//the node is inserted into the tree in insert_node().
//-------------Create_Tree-------------//
Node* create_tree()
{
    Node *root = nullptr, *node = nullptr;
    int data;

    cin >> data;
    while(!cin.eof())
    {
        node = new_node();
        node->_data = data;
        insert_node(root, node);
        cin >> data;
    }
    return root;
}

//Create a node. left+right = NULL
//--------------New_Node----------------//
Node* new_node()
{
    Node *node = new (nothrow) Node;

    if(node == nullptr)
    {
        cerr << "Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }

    node->_left = node->_right = nullptr;

    return node;
}

//Insert a node to a tree
//---------------Insert_Node---------------//
void insert_node(Node *&root, Node *node)
{
    if(!root)
        root = node;
    else if(node->_data <= root->_data)
        insert_node(root->_left, node);
    else
        insert_node(root->_right, node);
}

//Prepares even,odd and max_even for comparison
//and calls find_subtree to find the subtree.
//------------------Get_Subtree-------------------//
Node* get_subtree(Node *root)
{
    Node *subtree = nullptr;
    size_t even = 0, odd = 0, max_even = 0;

    find_subtree(root, subtree, even, odd, max_even);

    return subtree;
}

//Function goes to the leafes(left, then right) and checks
//each node if the data is even/odd and collects the amount
//and compares between them when there is a valid subtree.
//If we are in a valid subtree and even>odd, save the subtree. 
//---------------------Find_Subtree----------------------//
void find_subtree(Node *root, Node *&subtree, size_t& even,
                  size_t& odd, size_t& max_even)
{
    if(root->_left != nullptr) //Go left until the leaf
        find_subtree(root->_left, subtree, even, odd, max_even);
    if(root->_right != nullptr){ //Go right until the leaf
        //If we finished the left edge reset even until we get to the leag
        even = 0; //even saved already in max_even
        find_subtree(root->_right, subtree, even, odd, max_even);
    }
    //Checks the intersection
    if(root->_left != nullptr && root->_right != nullptr)
    {
        max_even += even; //insert all evens into max_even
        //so it will work with the total of both edges of the subtree
        if(root->_data % 2 == 0)
        {
            max_even++;
            even = 0;
        }
        else
            odd++;
        if(max_even > odd)
            subtree = root;
        return; //return from intersection back
    }
    //edges and leaves
    else if(root->_data % 2 == 0)
        even++;
    else
        odd++;
    //If we get a leaf for the first time and it's even, make it subtree.
    if(root->_left == nullptr || root->_right == nullptr)
        if(even > odd || (subtree == nullptr && root->_data % 2 == 0 &&
                          root->_right == nullptr && root->_left == nullptr) )
            subtree = root;
    if(even > max_even) //even will be always saved in max_even
        max_even = even;
}

//Prints the subtree _data.
//-----------------Print_Subtree----------------//
void print_subtree(Node *subtree)
{
    if(!subtree)
        cout << "NOT FOUND";
    else
        cout << subtree->_data << endl;
}

//Free all tree memory
//------------Free_Tree-------------//
void free_tree(Node *root)
{
    if(root)
    {
        free_tree(root->_left);
        free_tree(root->_right);
        delete root;
    }
}