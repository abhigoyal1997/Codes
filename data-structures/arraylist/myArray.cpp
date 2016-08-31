#include "myArray.h"

myArray::myArray(){
	arrLimit = 0;
	lastIndex = -1;
}

myArray::myArray(int n){
	arrLimit = n;
	arr = new int[n];
	lastIndex = -1;
}

myArray::myArray(int *a, int n){
	arrLimit = n;
	arr = new int[n];
	int i=0;
	for(i; i!=n; i++) arr[i] = a[i];
	lastIndex = i-1;
}

void myArray::setArrayLimit(int n){
	arrLimit = n;
	arr = new int[arrLimit];
}

void myArray::addToArray(int a){
	if(lastIndex==arrLimit-1) return;
	arr[++lastIndex] = a;
}

void myArray::addToArray(int *a,int k){
	for(int i=0; i!=k; i++){
		this->addToArray(a[i]);
	}
}

void myArray::printArray(){
	for(int i=0; i!=lastIndex+1; i++) cout << arr[i] << " ";
	cout << endl;
}

void myArray::deleteFromArray(){
	if(lastIndex==-1) return;
	arr[lastIndex--]==0;
}

void myArray::deleteFromArray(int k){
	while(k--){
		this->deleteFromArray();
	}
}

bool myArray::isSorted(){
	bool sorted=true;
	for(int i=0; i!=lastIndex; i++){
		sorted = sorted && (arr[i+1]>=arr[i]);
	}
	return sorted;
}

bool myArray::binarySearch(int a){
	if(lastIndex==-1) return 0;
	if(lastIndex==0){
		if(arr[0]==a) return 1;
		return 0;
	}

	int mid = lastIndex/2;
	if(arr[mid]==a) return 1;
	if(arr[mid]>a){
		int x[mid+1];
		for(int i=0; i!=mid+1; i++){
			x[i] = arr[i];
		}
		myArray b(x, mid+1);
		return b.binarySearch(a);
	}
	if(arr[mid]<a){
		int x[lastIndex-mid];
		for(int i=0; i!=lastIndex-mid; i++){
			x[i] = arr[mid+i+1];
		}
		myArray b(x, lastIndex-mid);
		return b.binarySearch(a);
	}
}

bool myArray::isEqual(myArray A){
	if(lastIndex!=A.lastIndex) return 0;
	bool equal=true;
	for(int i=0; i!=lastIndex+1; i++) equal = equal && (A.getValue(i)==this->getValue(i));
	return equal;
}

int myArray::getValue(int index){
	if(index>lastIndex || index<0){
		cout << "INDEX OUT OF BOUND";
		return -1;
	}
	return arr[index];
}

int myArray::size(){
	return lastIndex+1;
}

myArray myArray::operator+(myArray& A){
	if(this->lastIndex!=A.lastIndex) return *this;
	myArray B(this->lastIndex + A.lastIndex + 2);
	B.addToArray(this->arr, lastIndex+1);
	B.addToArray(A.arr, A.lastIndex+1);
	return B;
}

myArray::~myArray(){
	delete[] arr;
}