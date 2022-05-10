/* Ex3b: Quarter sub_tree
*==================================
* Written by David Zaydenberg
*
* Program takes input of Id, x, y and builds a node of of these parameters 
* and create a binary search tree.
* Program searches and checks which sub tree's point values
* are in the same quadrent as both points of the left and right nodes
* and saves the subtree that have the most of this condition.
* ** RunTime - O(N) **
* 
* Main - Main calls functions.
* Creates bst, Gets subtree, prints subtree and frees memory 
*
* Create_tree - Creates a binary tree. Input ID, x and y until eof(alt+z/d)
* Node is created, data(x,y) in inserted in the node, and then
* the node is inserted into the tree in insert_node().
*
* New_Node - Create a node. left+right = NULL
*
* New_Point - Creates a Point node.
*
* Insert_Node - Insert a node to a tree
*
* Get_Subtree - Prepares variables to use in recursion and
* gets the subtree from "find_subtree" function
*
* Find_Subtree - Finds the leaves(first left, than right) and check each
* node if the condition is met(same sign). 
*
* Check_Subtree -  checks if the conditions are met for a node.
* If the _data values(x,y) are the same sign as the node below, count++.
*
* Check_xy_left - Check left side if the x,y values
* are the same(negative/possitive)
*
* Check_xy_right - Check right side if the x,y values
* are the same(negative/possitive)
*
* Print_Subtree - Prints the subtree intersection x,y parameters
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
struct Point{
    int _x;
    int _y;
};

struct Node{
    int _id;
    struct Point *_data;
    struct Node *_left, *_right;
};

//---------------Prototype_Section---------------//
Node* create_tree();
Node* new_node();
Point* new_point();
void insert_node(Node *&root, Node *node);
Node* get_subtree(Node *root);
void find_subtree(Node *root, Node *&subtree, size_t& max_count,
                  size_t &lcount, size_t &rcount,
                  bool &left_fail, bool &right_fail);
void check_subtree(Node* root, Node *&subtree, size_t &max_count,
           size_t &lcount, size_t &rcount, bool &left_fail, bool &right_fail);
bool check_xy_left(Node* root, bool &left_fail);
bool check_xy_right(Node* root, bool &right_fail);
void print_subtree(Node *subtree);
void free_tree(Node *root);

//Main calls functions.
//Creates bst, Gets subtree, prints subtree and frees memory 
//-------------Main-------------//
int main()
{
    Node *root = create_tree();

    if(root != nullptr){
        Node *subtree = get_subtree(root);
        print_subtree(subtree);
        free_tree(root);
    }
    else
        cout << "0 0\n";

    return EXIT_SUCCESS;
}

//Creates a binary tree. Input ID, x and y until eof(alt+z/d)
//Node is created, data(x,y) in inserted in the node, and then
//the node is inserted into the tree in insert_node().
//-------------Create_Tree-------------//
Node* create_tree()
{
    Node *root = nullptr, *node = nullptr;
    Point *point = nullptr;
    int id, x, y;

    cin >> id >> x >> y;
    while(!cin.eof())
    {
        node = new_node();
        point = new_point();
        node->_data = point;
        node->_id = id;
        point->_x = x;
        point->_y = y;
        insert_node(root, node);
        cin >> id >> x >> y;
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

//Creates a Point node.
//-------------New_Point-------------//
Point* new_point()
{
    Point *point = new (nothrow) Point;

    if(point == nullptr)
    {
        cerr << "Cannot allocate memory\n";
        exit(EXIT_FAILURE);
    }

    return point;
}

//Insert a node to a tree
//---------------Insert_Node---------------//
void insert_node(Node *&root, Node *node)
{
    if(!root)
        root = node;
    else if(node->_id <= root->_id)
        insert_node(root->_left, node);
    else
        insert_node(root->_right, node);
}

//Prepares variables to use in recursion and
//gets the subtree from "find_subtree" function
//--------------Get_inter---------------//
Node* get_subtree(Node *root)
{
    size_t max_count = 0, lcount = 0, rcount = 0;
    bool left_fail = false, right_fail = false;
    Node* subtree = nullptr;
    find_subtree(root, subtree, max_count, lcount,
               rcount, left_fail, right_fail);
    return subtree;
}

//Finds the leaves(first left, than right) and check each
//node if the condition is met(same sign). 
//-----------------Find_Subtree---------------------//
void find_subtree(Node *root, Node *&subtree, size_t& max_count,
                  size_t &lcount, size_t &rcount,
                  bool &left_fail, bool &right_fail)
{  
    if(root->_left != nullptr) //Go left until the leaf
    {
        find_subtree(root->_left, subtree, max_count, lcount,
                   rcount, left_fail, right_fail);
    }
    if(root->_right != nullptr) //Go right until the leaf
    {
        //If after visiting left side we got right_fail,
        //we change it because it will be considered as left side.
        //(Happends after returning to an intersection)
        if(!left_fail && right_fail)
        {
            left_fail = true;
            right_fail = false;
        }
        find_subtree(root->_right, subtree, max_count, lcount,
                   rcount, left_fail, right_fail);
    }
    //After finished visiting edges and we are at the intersection
    //Checks if no edge failed saves the right count to the left and
    //clears the right count so it will start a new count in the right subtree
    if(root->_left != nullptr && root->_right != nullptr &&
        rcount > lcount && max_count > 0 && !left_fail && !right_fail)
    {
        lcount = rcount;
        rcount = 0;
    }
    //Goes into the node and checks if the conditions are met
    check_subtree(root, subtree, max_count, lcount,
                 rcount, left_fail, right_fail);
    //If count is bigger than max_count save it and replace subtree.
    if(lcount > max_count || rcount > max_count)
    {
        if(lcount > max_count){
            subtree = root;
            max_count = lcount;
        }
        else if(rcount > max_count){
            subtree = root;
            max_count = rcount;
        }
    }
}

//checks if the conditions are met for a node.
//If the _data values(x,y) are the same sign as the node below, count++.
//------------------Check_Subtree------------------//
void check_subtree(Node* root, Node *&subtree, size_t &max_count,
           size_t &lcount, size_t &rcount, bool &left_fail, bool &right_fail)
{
    //If we are at a leaf
    if(root->_right == nullptr && root->_left == nullptr)
    {
        if(rcount > 0){//left leaf visit
            lcount++;
        }
        else if(lcount > 0){//right leaf visit
            rcount++;
        }
        else{
            lcount++;//First leaf visit
        }
    }
    //If we are at a left subtree
    else if(root->_right == nullptr && check_xy_left(root, left_fail))
    {
        lcount++;
    }
    //If we are at a right subtree
    else if(root->_left == nullptr && check_xy_right(root, right_fail))
    {
        rcount++;
    }
    //If we are at an intersection and both (left&right) subtrees
    //are valid, sum them up and make the intersection as the subtree.
    else if(root->_left != nullptr && root->_right != nullptr){
        if(lcount > 0 && rcount > 0 && check_xy_left(root, left_fail) &&
        check_xy_right(root, right_fail) && !left_fail && !right_fail){
            max_count = lcount+rcount+1;
            subtree = root;
        }
        return; //(go back(node before))
    }
}

//Check left side if the x,y values are the same(negative/possitive)
//-----------------Check_xy_left------------------//
bool check_xy_left(Node* root, bool &left_fail)
{
    if(root->_data->_x < 0 && root->_left->_data->_x < 0)
    {
        if( (root->_data->_y < 0 && root->_left->_data->_y < 0) ||
           (root->_data->_y > 0 && root->_left->_data->_y > 0) )
        {
            return true;
        }
    }
    else if(root->_data->_x > 0 && root->_left->_data->_x > 0)
    {
        if( (root->_data->_y < 0 && root->_left->_data->_y < 0) ||
           (root->_data->_y > 0 && root->_left->_data->_y > 0) )
        {
            return true;
        }
    }
    //Make left subtree failed, so there won't be intersection check.
    left_fail = true; 
    return false;
}

//Check right side if the x,y values are the same(negative/possitive)
//-----------------Check_xy_Right-----------------//
bool check_xy_right(Node* root, bool &right_fail)
{
    if(root->_data->_x < 0 && root->_right->_data->_x < 0)
    {   
        if( (root->_data->_y < 0 && root->_right->_data->_y < 0) ||
           (root->_data->_y > 0 && root->_right->_data->_y > 0) )
        {
            return true;
        }
    }
    else if(root->_data->_x > 0 && root->_right->_data->_x > 0)
    {
        if( (root->_data->_y < 0 && root->_right->_data->_y < 0) ||
           (root->_data->_y > 0 && root->_right->_data->_y > 0))
        {
            return true;
        }
    }
    //Make left subtree failed, so there won't be intersection check.
    right_fail = true;
    return false;
}

//Prints the subtree intersection x,y parameters
//-----------------Print_Subtree----------------//
void print_subtree(Node *subtree)
{
    if(!subtree){
        cout << "0 0\n";
    }
    else{
        cout << subtree->_data->_x << " "
        << subtree->_data->_y << endl;
    }
}

//Free all tree memory
//------------Free_Tree-------------//
void free_tree(Node *root)
{
    if(root)
    {
        free_tree(root->_left);
        free_tree(root->_right);
        delete root->_data;
        delete root;
    }
}
