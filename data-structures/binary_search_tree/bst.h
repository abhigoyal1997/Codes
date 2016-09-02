#include <iostream>

using namespace std;

class BST
{
private:
    // Internal struct which stores node related information.
    struct BSTNode
    {
        int data;           // value in node is of type int
        int size;
        BSTNode* left;
        BSTNode* right;
    };
    BSTNode* root;

    void insertNode(BSTNode*&, int);
    void printTree(BSTNode*) const;
    bool searchNode(BSTNode*, int) const;
    BSTNode* getParent(int, bool*);
    bool rebalanceNode(BSTNode*, int);
    BSTNode* getMin(BSTNode*);
    BSTNode* getMax(BSTNode*);
    void deleteNode(BSTNode*);
public:
    BST();                  // the basic constructor and destructor functions
    ~BST();
    bool search(int) const; // search for a value in the tree
    void insert(int);       // insert a value/node in the tree
    void remove(int);       // remove value/node from the tree
    void rebalance(int);    // make value specified as new root, if node present

    void print() const;     // print values in sorted order
    void printroot() const; // print value of root, and its left child and
                            // right child
};
