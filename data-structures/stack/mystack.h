#include <iostream>

class Stack{

	// Internal struct which stores node related information.
    struct node
    {
        int data;           // value in node is of type int
        node * next;
    };

	node* head;             // use this pointer for stack operations
	size_t size;

void deleteNode(node*);

public:
	Stack() ;        // constructor, desctuctor
	~Stack();

	int top();       // return value at top of stack, do not remove element
	int pop();       // return value at top, remove element from stack. -1 if no element.

	void push(int);  // push value in stack.
	bool empty();    // check for stack emptiness
};
