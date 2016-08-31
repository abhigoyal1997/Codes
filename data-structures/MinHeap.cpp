#include "MinHeap.h"

void swap(int &x, int &y){
	int t=x;
	x=y; y=t;
}

MinHeap::MinHeap(){
	val = NULL;
	capacity = 0;
	size = 0;
}

MinHeap::MinHeap(int capacity){
	this->capacity = capacity;
	size = 0;
	val = new int[capacity];
}

MinHeap::~MinHeap(){
	delete[] val;
}

void MinHeap::heapify(int i){
	int l = getLeftChild(i);
	int r = getRightChild(r);
	int smallest = i;
	if(l < size && val[l]<i) smallest = l;
	if(r < size && val[r]<smallest) smallest = r;
	if(smallest != i){
		swap(val[smallest],val[i]);
		heapify(smallest);
	}
}

int MinHeap::getParent(int i){
	return (i-2)/2;
}

int MinHeap::getRightChild(int i){
	return 2*i+2;
}

int MinHeap::getLeftChild(int i){
	return 2*i+1;
}

int MinHeap::extractMin(){
	if(size <= 0) return INT_MAX;
	if(size == 1){
		size--;
		val[0];
	}

	int root = val[0];
	val[0] = val[size-1];
	size--;
	heapify(0);
	return root;
}

int MinHeap::getMin(){
	return val[0];
}

void MinHeap::decreaseKey(int i, int v){
	val[i] = v;
	while(i!=0 && val[getParent(i)]>val[i]){
		swap(val[i],val[getParent(i)]);
		i = getParent(i);
	}
}

void MinHeap::deleteKey(int i){
	val[i] = val[size-1];
	size--;
	heapify(0);
}

void MinHeap::insertKey(int k){
	if(size == capacity) return;
	val[size-1] = k;
	size++;
	int i=0;
	while(i!=0 && val[getParent(i)]>val[i]){
		swap(val[i],val[getParent(i)]);
		i = getParent(i);
	}
}

int main(){

}