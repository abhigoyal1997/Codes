#include <iostream>

using namespace std;

struct List
{
	int x;
	List* next;
};

void print(List* head){
	List* temp;
	temp = head;
	while(temp->next!=0){
		cout << temp->x << " ";
		temp = temp->next;
	}
	cout << temp->x << endl;
}

List* reverse(List* head){
	if(head==NULL || head->next==NULL) return head;// list of 0 or 1 element
	if(head->next->next==NULL){// list of 2 elements
		List* temp;
		temp = head->next;
		temp->next = head;
		head->next = NULL;
		return temp;
	}

	List* temp1;
	List* temp2;
	List* temp3;

	temp1 = head;
	temp2 = temp1->next;
	temp3 = temp2->next;// initializing the 3 temporary variables to 0, 1 & 2 elements of list
	temp1->next = 0;// setting the first element to point to null(thus it becomes the last element)
	temp2->next = temp1;
	while(temp3->next!=0){
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp3->next;
		temp2->next = temp1;
	}

	temp3->next = temp2;
	return temp3;// returns the head of reversed list(since temp3->next=0 after termination of loop, therefore it's the head for reversed list)
}

int main(){
	int n;
	cout << "\nNo. of elements in list: ";
	cin >> n;// no. of elements in list

	List* head;
	List* temp;

	if(n==0) return 0;// for empty list
	cout << "\nList of elements: ";
	head = new List;// head of the originally entered list
	temp = head;

	for(int i=0; i<n-1; i++){
		cin >> temp->x;
		temp->next = new List;
		temp = temp->next;
	}
	cin >> temp->x;
	temp->next = NULL;// assigning the last element

	cout << "\nThe entered list is: ";
	print(head);// printing the entered list

	head = reverse(head);// returns the pointer to the first element of the reversed list(last element of original)
	cout << "\nThe reverse of the entered list is: ";
	print(head);// printing the reversed list
}