#include <iostream>
#include <cstdlib>
using namespace std;
class myArray{
	private:
		int *arr;  
		int arrLimit;
		int lastIndex;
	public:
		myArray();       //empty constructor
		myArray(int n);  // number of items in an array
		myArray(int *a, int n);   //pointer to array list and number of items
		void setArrayLimit(int n);  //should set only once for empty constructor
		void addToArray(int a);   //append 'a' to array if within size limit
		void addToArray(int *a,int k);  //append k elements denoted by pointer array. Stop once array size limit is reached. 
		void printArray();     //print array, format- value1 value2 value3 
		void deleteFromArray();  //delete last element from array. If array empty, do nothing.
		void deleteFromArray(int k);   //delete last k elements of array if they exist. Stop deleting once the array becomes empty.
		bool isSorted();      //is array sorted
		bool binarySearch(int a);    //search element a in sorted array using binary search
		bool isEqual(myArray A);    //compare if 2 arrays are equal or not
		int getValue(int index);   //returns value from an array at a given index. If index is more than number of elements currently in array, print "INDEX OUT OF BOUND" and return -1.
		int size();            //returns number of elements currently present in array
		myArray operator+(myArray&); //if two arrays have same size, add the two arrays and return output array
		~myArray(); //destructor
};


