#include <iostream>
#include <cstdlib>
#include <map>

using namespace std;

//The datastore template class
template <class T>
class datastore{
   // struct which stores the data items
   struct item {
       T id;
       struct item* next;
   };
   // struct used to store access count and pointer to struct item
   struct count_list {
       int count; 		// access count
       int num; 		// number of nodes in that count_list
       struct count_list* next; // pointer to next count node
       struct item* node;       // pointer to list of data items
   };
	
   struct count_list* head;
   map<T, count_list*> countMap;

   void deleteCountList(count_list*);
   void deleteCountNode(item*);
   void deleteItem(int, T);
   void insertItem(int, T);
   bool searchList(count_list*, T);
   void printList(count_list*);
   void copy(count_list*, count_list*);
   item* reverse(item*);

   public:
   datastore();
   ~datastore();

   void insert(T);      // Insert value T to the datastore
   int search(T);       // Search for value T in the datastore. return its access count if found, else return -1
   int find_max();      // Find maximum value of access count. print -1 if no nodes exist
   void list_max();     // Print values of data items with maximum access count value. 
                        // do not print anything if there are no nodes.

   void decrement(T);   // decrement count of the T by 1. if its count is 0, do nothing.
   void reset();        // set access count of all nodes to 0
   void list_zero();    // print all data values in count_list with count value 0. if none exist, print nothing
   void list_count(int);// print all nodes with access count which is passed as an argument. if none exist, print nothing.
   int eject(T);        // remove the value T from data store. return 1 for success, 0 for failure (value did not exist)
		
   void print();        // print all values in the datastore in the ascending order of access count.
};

