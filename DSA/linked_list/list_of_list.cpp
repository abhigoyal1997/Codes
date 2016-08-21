#include "list_of_list.h"

template <class T>
datastore<T>::datastore(){
	head = NULL;
}

template <class T>
datastore<T>::~datastore(){
	deleteCountList(head);
	countMap.clear();
}

template <class T>
void datastore<T>::deleteCountList(count_list* listHead){
	if(listHead == NULL) return;
	deleteCountNode(listHead->node);
	deleteCountList(listHead->next);
	delete listHead;
}

template <class T>
void datastore<T>::deleteCountNode(item* node){
	if(node == NULL) return;
	deleteCountNode(node->next);
	delete node;
}

template <class T>
void datastore<T>::insert(T data){
	int count = search(data);
	deleteItem(count, data);
	if(count == -1) count = 1;
	else count++;
	insertItem(count, data);
}

template <class T>
void datastore<T>::deleteItem(int count, T data){
	if(count == -1) return;
	count_list* listHead = head;
	count_list* preListHead = NULL;
	while(listHead->count != count){
		preListHead = listHead;
		listHead = listHead->next;
	}

	item* node = listHead->node;
	item* preNode = NULL;
	while(node->id != data){
		preNode = node;
		node = node->next;
	}

	if(preNode == NULL){
		listHead->node = node->next;
		delete node;
	}
	else{
		preNode->next = node->next;
		delete node;
	}
	if(--listHead->num == 0){
		if(preListHead != NULL){
			preListHead->next = listHead->next;
			countMap[data] = NULL;
			delete listHead;
		}
		else{
			head = listHead->next;
			countMap[data] = NULL;
			delete listHead;
		}
	}
} 

template <class T>
void datastore<T>::insertItem(int count, T data){
	count_list* listHead = head;
	count_list* preListHead = NULL;
	while(listHead != NULL){
		if(listHead->count >= count) break;
		preListHead = listHead;
		listHead = listHead->next;
	}

	if(listHead == NULL){
		listHead = new count_list;
		listHead->count = count;
		listHead->node = NULL;
		listHead->next = NULL;
		listHead->num = 0;
		if(preListHead != NULL) preListHead->next = listHead;
		else head = listHead;
	}
	else if(listHead->count > count){
		count_list* nextListHead = listHead;
		listHead = new count_list;
		listHead->count = count;
		listHead->node = NULL;
		listHead->next = NULL;
		listHead->num = 0;
		if(preListHead != NULL) preListHead->next = listHead;
		else head = listHead;
		listHead->next = nextListHead;
	}

	item* nextNode = listHead->node;
	listHead->node = new item;
	listHead->node->id = data;
	listHead->node->next = nextNode;	
	listHead->num++;
	countMap[data] = listHead;
}

template <class T>
int datastore<T>::search(T data){
	if(countMap[data] == NULL) return -1;
	return countMap[data]->count;
}

template <class T>
int datastore<T>::find_max(){
	if(head == NULL) return -1;
	count_list* maxCount = head;
	while(maxCount->next != NULL) maxCount = maxCount->next;
	return maxCount->count;
}

template <class T>
void datastore<T>::list_max(){
	if(head == NULL) return;
	count_list* maxCount = head;
	while(maxCount->next != NULL) maxCount = maxCount->next;
	printList(maxCount);
}

template <class T>
void datastore<T>::decrement(T data){
	int count = search(data);
	if(count == -1 || count == 0) return;
	deleteItem(count, data);
	insertItem(count - 1, data);
}

template <class T>
void datastore<T>::reset(){
	if(head == NULL) return;

	count_list* listHead = head;
	count_list* zeroHead;
	count_list* tempListHead = head;
	zeroHead = new count_list;
	zeroHead->count = 0;
	zeroHead->node = NULL;
	zeroHead->next = NULL;
	zeroHead->num = 0;

	bool headZero = 0;
	if(head->count == 0) headZero = 1;

	while(listHead != NULL){
		copy(listHead, zeroHead);
		tempListHead = listHead->next;
		delete listHead;
		listHead = tempListHead;
	}

	zeroHead->node = reverse(zeroHead->node);
	if(headZero){
		item* zeroListNode = zeroHead->node;
		while(zeroListNode->next != NULL) zeroListNode = zeroListNode->next;
		zeroListNode->next = head->node;
		head->node = zeroHead->node;
		head->next = NULL;
	}
	else{
		head = zeroHead;
		head->next = NULL;
	}
	item* node = head->node;
	while(node != NULL){
		countMap[node->id] = head;
		node = node->next;
	}
}

template <class T>
void datastore<T>::copy(count_list* listHead, count_list* copyListHead){
	item* copyNode = copyListHead->node;
	item* node = listHead->node;
	listHead->node = NULL;

	if(copyListHead->node == NULL){
		copyListHead->node = node;
		return;
	}
	while(copyNode->next != NULL) copyNode = copyNode->next;
	copyNode->next = node;
}

template <class T>
typename datastore<T>::item* datastore<T>::reverse(item* head){
	if(head==NULL || head->next==NULL) return head;
	if(head->next->next==NULL){
		item* temp;
		temp = head->next;
		temp->next = head;
		head->next = NULL;
		return temp;
	}

	item* temp1;
	item* temp2;
	item* temp3;

	temp1 = head;
	temp2 = temp1->next;
	temp3 = temp2->next;
	temp1->next = 0;
	temp2->next = temp1;
	while(temp3->next!=0){
		temp1 = temp2;
		temp2 = temp3;
		temp3 = temp3->next;
		temp2->next = temp1;
	}

	temp3->next = temp2;
	return temp3;
}

template <class T>
void datastore<T>::list_zero(){
	if(head == NULL) return;
	if(head->count != 0) return;
	printList(head);
}

template <class T>
void datastore<T>::list_count(int count){
	count_list* listHead = head;
	while(listHead != NULL){
		if(listHead->count >= count) break;
		listHead = listHead->next;
	}
	if(listHead == NULL) return;
	if(listHead->count == count){
		cout << count << " ";
		printList(listHead);
	}
}

template <class T>
int datastore<T>::eject(T data){
	int count = search(data);
	if(count == -1) return 0;
	deleteItem(count, data);
	return 1;
}

template <class T>
void datastore<T>::print(){
	count_list* listHead = head;
	while(listHead != NULL){
		cout << listHead->count << " ";
		printList(listHead);
		listHead = listHead->next;
	}
}

template <class T>
void datastore<T>::printList(count_list* listHead){
	item* node = listHead->node;
	while(node != NULL){
		cout << node->id << " ";
		node = node->next;
	}	
	cout << endl;
}

template class  datastore<int>;
template class datastore<float>;
template class  datastore<char>;