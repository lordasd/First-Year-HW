/* Ex3a: Intersection and son identicality 
*==================================
* Written by David Zaydenberg
*
* Program is taking input of data(whole possitive numbers) until eof(alt+z/d)
* and builds a binary tree.
* Program prints out how many itersections are there that their data and their
* left sons data are equal.
*
* Main - Main calls functions and prints the num of intersections
* intersec_sum returned
*
* Create_tree - Creates a binary tree. Input a number until eof(alt+z/d)
* Node is created, data in inserted in the node, and then
* the node is inserted into the tree in insert_node().
*
* New_Node - Create a node. left+right = NULL
* 
* Insert_Node - Insert a node to a tree
*
* Intersec_Sum - Going through the whole tree recursively while returning
* + 1 for each intersection which their data is equal to
* the data of their son to the left.
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
    struct Node *_left, *_right;
};

//---------------Prototype_Section---------------//
Node* create_tree();
Node* new_node();
void insert_node(Node *&root, Node *node);
int intersec_sum(Node *root);
void free_tree(Node *root);

//Main calls functions and prints the num of intersections
//intersec_sum returned
//-------------Main-------------//
int main()
{
    Node *root = create_tree();

    cout << intersec_sum(root);

    free_tree(root);

    return EXIT_SUCCESS;
}

//Creates a binary tree. Input a number until eof(alt+z/d)
//Node is created, data in inserted in the node, and then
//the node is inserted into the tree in insert_node().
//-------------Create_Tree-------------//
Node* create_tree()
{
    Node *root = NULL, *node = NULL;
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

    if(node == NULL)
    {
        cerr << "Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }

    node->_left = node->_right = NULL;

    return node;
}

//Insert a node to a tree
//---------------Insert_Node---------------//
void insert_node(Node *&root, Node *node)
{
    if(!root)
    {
        root = node;
    }
    else if(node->_data <= root->_data)
    {
        insert_node(root->_left, node);
    }
    else
    {
        insert_node(root->_right, node);
    }
}

//Going through the whole tree recursively while returning
// + 1 for each intersection which their data is equal to
//the data of their son to the left.
//---------------Intersec_Sum-----------------//
int intersec_sum(Node *root)
{
    if(root == NULL){
        return 0;
    }
    Node *temp = root->_left;
    if(root->_left != NULL) {
        if (root->_data == temp->_data) {
            return intersec_sum(root->_left) +
                   intersec_sum(root->_right) + 1;
        }
    }
    return intersec_sum(root->_left) +
           intersec_sum(root->_right);
}

//Free all tree memory
//------------Free_Tree-------------//
void free_tree(Node *root)
{
    if(!root)
    {
        free_tree(root->_left);
        free_tree(root->_right);
        delete root;
    }
}
