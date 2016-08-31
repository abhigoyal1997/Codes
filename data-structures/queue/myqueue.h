#include <iostream>

class myqueue{

	// Internal struct which stores node related information.
    struct node
    {
        int data;           // value in node is of type int
        node* next;
    };

	node* head;             // use this pointer for start of queue
	node* tail;
	size_t size;

// add variables, functions and function keywords as needed

public:
	myqueue() ;        // constructor, desctuctor
	~myqueue();

	bool enqueue(int); // add element to queue, return success/failure
	int dequeue();     // remove element from queue. return element or -1 (if not element)

	void print();      // print queue in FIFO order. print null if list empty
};
