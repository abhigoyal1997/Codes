#include <iostream>

using namespace std;

template <class T>
class BST
{
private:
    // Internal struct which stores node related information.
    struct BSTNode
    {
        T data;           // value in node is of type int
        BSTNode * left;
        BSTNode * right;

    //BSTNode(T val):data(val),left(NULL),right(NULL){}
    };
    BSTNode* root;

    void insertNode(BSTNode**, T);
    void printTree(BSTNode*) const;
    bool searchNode(BSTNode*, T) const;
    BSTNode* getParent(T, bool*);
    bool rebalanceNode(BSTNode*, T);
    BSTNode* getMin(BSTNode*);
    BSTNode* getMax(BSTNode*);
    void deleteNode(BSTNode*);
public:
    BST();                  // the basic constructor and destructor functions
    ~BST();
    bool search(T) const; // search for a value in the tree
    void insert(T);       // insert a value/node in the tree
    void remove(T);       // remove value/node from the tree
    void rebalance(T);    // make value specified as new root, if node present

    void print() const;     // print values in sorted order
    void printroot() const; // print value of root, and its left child and
                            // right child
};
