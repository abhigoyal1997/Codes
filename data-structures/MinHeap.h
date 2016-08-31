#include <iostream>
#include <climits>

using namespace std;

class MinHeap
{
	int *val;
	int capacity;
	int size;

public:
	MinHeap();
	MinHeap(int);
	~MinHeap();

	void heapify(int);
	int getParent(int);
	int getRightChild(int);
	int getLeftChild(int);
	int extractMin();
	int getMin();
	void decreaseKey(int,int);
	void deleteKey(int);
	void insertKey(int);
};