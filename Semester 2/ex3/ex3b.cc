/* Ex3b: Quarter Sub_Tree
*==================================
* Written by David Zaydenberg, ID: 319323721, Login: davidzay
*
* Program takes input of Id, x, y and builds a node of
* of these parameters and create a binary search tree.
* Program searches and checks which sub tree's point values
* are in the same quadrent as both points of the
* left and right nodes and saves the subtree that has the
* most nodes which comply with the condition.
* ** RunTime - O(N) ** while searching in-order.
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
int find_subtree(Node *root, Node *&subtree, int& max_count);
int check_nodes(Node *root, Node* &subtree, int sub_left,
                int sub_right, int &max_count);
void replace_subtree(Node *root, Node* &subtree, int sub_left,
                     int sub_right, int &max_count);
int check_intersec(Node *root, Node* &subtree, int sub_left,
                   int sub_right, int &max_count);
int check_leaf(Node *root, Node* &subtree, int sub_left,
               int sub_right, int &max_count);
int check_edge(Node *root, int sub_left, int sub_right);
bool check_xy_left(Node* root);
bool check_xy_right(Node* root);
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
    int max_count = 0, last_count;
    Node* subtree = nullptr;

    last_count = find_subtree(root, subtree, max_count);
    //checks if the return amount is the same as max_count,
    //meaning subtree != root.
    if(max_count == last_count)
        return subtree;
    else if(last_count > max_count && last_count >= 0)
    //If last count retured bigger than max_count and subtree didn't fail
        return root; //We are at root(meaning the whole tree is valid)
    else
        return subtree;
}

//Finds the leaves(first left, than right) and check each
//node if the condition is met(same sign).
//-----------------Find_Subtree---------------------//
int find_subtree(Node *root, Node *&subtree, int& max_count)
{
    int sub_left = 0, sub_right = 0;

    if(root == nullptr) //return 0 if at null
    {
        return 0;
    }
    //If we meet an intersection split sums to sub_left and right
    if(root->_left != nullptr && root->_right != nullptr)
    {
        sub_left += find_subtree(root->_left, subtree, max_count);
        sub_right += find_subtree(root->_right, subtree, max_count);
    }
    //After reaching a leaf turn back and sum with sub_left or sub_right
    if(root->_left != nullptr && root->_right == nullptr)
        sub_left += find_subtree(root->_left, subtree, max_count);
    else if(root->_left == nullptr && root->_right != nullptr)
        sub_right += find_subtree(root->_right, subtree, max_count);
    //after each node visit, check if subtree can be replaced
    if(sub_left > max_count || sub_right > max_count)
        replace_subtree(root, subtree, sub_left, sub_right, max_count);
    //Check if a node meets the condition.
    return check_nodes(root, subtree, sub_left, sub_right, max_count);
}

//Checks where is the node located and check the node itself for condition
//-------------------Check_Nodes------------------------//
int check_nodes(Node *root, Node* &subtree, int sub_left,
                int sub_right, int &max_count)
{
    if(root->_left != nullptr && root->_right != nullptr)//intersection check
        return check_intersec(root, subtree, sub_left, sub_right, max_count);
    if(root->_left == nullptr && root->_right == nullptr)//Leaf check
        return check_leaf(root, subtree, sub_left, sub_right, max_count);
    if(root->_left != nullptr || root->_right != nullptr)//Nodes in edges
        return check_edge(root, sub_left, sub_right);
    return 0;
}

//Replace the subtree with the side that has more amount
//--------------------Replace_Subtree----------------------//
void replace_subtree(Node *root, Node* &subtree, int sub_left,
                     int sub_right, int &max_count)
{
    if(sub_left > max_count)
    {
        max_count = sub_left;
        subtree = root->_left;
    }
    else
    {
        max_count = sub_right;
        subtree = root->_right;
    }
}

//after visiting both sides we check the intersection and
//---------------------Check_Intersec--------------------//
int check_intersec(Node *root, Node* &subtree, int sub_left,
                   int sub_right, int &max_count)
{
    if(sub_left >= 0 && sub_right >= 0)
    {   //Both left and right nodes have the same sign values(x,y)
        if(check_xy_left(root) && check_xy_right(root))
        {
            subtree = root;
            max_count = sub_left + sub_right + 1;
            return max_count;
        }
    }
    return -100;//Else fail the subtree
}

//Check the leaf(if it's first time), else return +1.
//------------------------Check_Leaf----------------//
int check_leaf(Node *root, Node* &subtree, int sub_left,
               int sub_right, int &max_count)
{
    if(sub_left == 0 && sub_right == 0 && max_count == 0) // first leaf
    {   //First leaf, make it subtree.
        subtree = root;
        max_count = 1;
        return 1;
    }
    else{
        return 1; // return 1 anyways because it's a leaf
    }
}

//Check if the values(x,y) of node in the edge are the same
//sign as the node below.return +1 if yes, else fail the subtree 
//--------------------Check_Edge--------------------//
int check_edge(Node *root, int sub_left, int sub_right)
{
    if(sub_left >= 0 && sub_right >= 0)
    {
        if(root->_left != nullptr)
        {
            if(check_xy_left(root))
                return 1 + sub_left;
            else//fail the subtree
                return -100 + sub_left;
        }
        else
        {
            if(check_xy_right(root))
                return 1 + sub_right;
            else//fail the subtree
                return -100 + sub_left;
        }
    }
    return -100;//Else fail the subtree
}

//Check left side if the x,y signs are the same(negative/possitive)
//-----------------Check_xy_left------------------//
bool check_xy_left(Node* root)
{
    if(root->_data->_x < 0 && root->_left->_data->_x < 0)
    {
        if( (root->_data->_y < 0 && root->_left->_data->_y < 0) ||
            (root->_data->_y > 0 && root->_left->_data->_y > 0) )
                return true;
    }
    else if(root->_data->_x > 0 && root->_left->_data->_x > 0)
    {
        if( (root->_data->_y < 0 && root->_left->_data->_y < 0) ||
            (root->_data->_y > 0 && root->_left->_data->_y > 0) )
                return true;
    }
    return false;
}

//Check right side if the x,y signs are the same(negative/possitive)
//-----------------Check_xy_Right-----------------//
bool check_xy_right(Node* root)
{
    if(root->_data->_x < 0 && root->_right->_data->_x < 0)
    {
        if( (root->_data->_y < 0 && root->_right->_data->_y < 0) ||
            (root->_data->_y > 0 && root->_right->_data->_y > 0) )
                return true;
    }            
    else if(root->_data->_x > 0 && root->_right->_data->_x > 0)
    {
        if( (root->_data->_y < 0 && root->_right->_data->_y < 0) ||
            (root->_data->_y > 0 && root->_right->_data->_y > 0) )
                return true;
    }           
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
