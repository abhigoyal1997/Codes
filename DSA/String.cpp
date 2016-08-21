#include <iostream>

using namespace std;

int len(const char* str){// to find the length of a const char array
	int l=0;
	while(str[l]!='\0') l++;
	return l;
}

void scopy(char* ptr, const char* str){// to copy a const char array to a char pointer in the heap memory
	int i=0;
	while(str[i]!='\0'){
		ptr[i]=str[i];
		i++;
	}
	ptr[i]='\0';
}

class String{
public:
	char* ptr;// points to the stored char array(i.e. string)
	String* next;// points to the next string in the list(if any)
	
	String(){// default constructor
		ptr = NULL;
		next = NULL;
	}
	
	String(const String& s){// copy constructor
		ptr = new char[len(s.ptr)+1];
		next = s.next;
		scopy(ptr, s.ptr);
	}

	String(const char* str){// constructor that uses a const char array for the initialization of string
		ptr = new char[len(str)+1];
		next = NULL;
		scopy(ptr, str);
	}

	~String(){// destructor
		delete[] ptr;
		delete next;
	}

	String& operator=(const char* str){// assignment using const char array
		delete[] ptr;
		ptr = new char[len(str)+1];
		scopy(ptr, str);
		return *this;
	}

	String& operator=(const String& s){// assignment  using another string
		if(ptr==s.ptr) return *this;
		*this = s.ptr;
		return *this;
	}

	String operator+(const char* str){// concatenation with a const char array
		String result;
		result.ptr = new char[len(ptr)+len(str)+1];
		int i=0;
		while(ptr[i]!='\0'){
			result.ptr[i]=ptr[i];
			i++;
		}
		int j=0;
		while(str[j]!='\0'){
			result.ptr[i]=str[j];
			j++;
			i++;
		}
		result.ptr[i]='\0';
		return result;
	}

	String operator+(const String& s){// concatenation with another string
		return *this+s.ptr;
	}

	char& operator[](int i){// [] operator for indexing
		return ptr[i];
	}

	bool operator<(const String& s){// returns true if the string comes alphabetically before another string(passed as argument)
		int i=0;
		while(ptr[i]!='\0' && s.ptr[i]!='\0'){
			if(ptr[i]>s.ptr[i]) return 0;
			if(ptr[i]<s.ptr[i]) return 1;
			i++;
		}
		if(len(ptr)<len(s.ptr)) return 1;
		return 0;
	}

	bool operator>(const String& s){// returns true if the string comes alphabetically after another string(passed as argument)
		int i=0;
		while(ptr[i]!='\0' && s.ptr[i]!='\0'){
			if(ptr[i]<s.ptr[i]) return 0;
			if(ptr[i]>s.ptr[i]) return 1;
			i++;
		}
		if(len(ptr)>len(s.ptr)) return 1;
		return 0;
	}

	void print(){// to print the string
		cout << ptr;
	}

	int length(){// to find the length of the string
		return len(ptr);
	}
};

void sort(String* &head){// to sort a given list alphabetically(cosidering ascii values of characters for comparison) using insertion sort
	String* x = head->next;// x = next string to be added to the so far sorted list
	String* pivot = head;// pivot = the last string of the so far sorted list
	while(x!=NULL){// invariant = list till pivot is alphabetically sorted, head is the first string and x is the next string to be added to so far sorted list
		if(*head<*x==0){// case in which head will change(comparison using overloaded < operator)
			pivot->next = x->next;
			x->next = head;
			head = x;
			x = pivot->next;
			continue;
		}
		String* temp = head->next;
		String* temp1 = head;
		while(*temp<*x){
			temp1 = temp;
			temp = temp->next;
		}
		if(temp==x){// case in which the string is already in the correct position
			pivot = pivot->next;
			x = x->next;
			continue;
		}// temp = pointer to the string which should come just after *x // temp1 = pointer to the string which should come just before *x
		pivot->next = x->next;
		temp1->next = x;
		x->next = temp;
		x = pivot->next;
	}
}

int main(){
	String a="abcd";// constructor using constant string to initialize a
	cout << "a = "; a.print(); cout << endl;

	String b(a);// copy constructor
	cout << "b = "; b.print(); cout << endl;

	char buffer[100];// assuming the maxlenght of string is 99
	cout << "Enter a string(c): ";
	cin >> buffer;
	String c;// default contructor
	c = buffer;// assingment using a pointer to a char array
	cout << "c = "; c.print(); cout << endl;
	cout << "Length of the string entered is= " << c.length() << endl;

	String d;
	d = c + "abcd";// concatenation with a constant string and assingment using another string
	cout << "d(c+\"abcd\") = "; d.print(); cout << endl;

	cout << "Enter a string(e): ";
	cin >> buffer;
	String e;
	e = buffer;
	cout << "e = "; e.print(); cout << endl;

	String f;
	f = c + e;// concatenation with another string
	cout << "f(c+e) = "; f.print(); cout << endl;

	char t;
	cout << "Enter a character: "; cin >> t;
	d[2] = t;// changing a character of string using indexing(overloaded [] operator)

	cout << "New d(after changing the 3 character to the entered one)= "; d.print(); cout << endl;

	cout << "Enter no. of strings in the list to be sorted: ";
	int n; cin >> n;
	if(n<=0) return 0;

	cout << "Enter the strings to stored in the list.\n";
	String* head;
	String* temp;
	
	cin >> buffer;
	head = new String(buffer);
	temp = head;

	for(int i=0; i<n-1; i++){
		cin >> buffer;
		temp->next = new String(buffer);
		temp = temp->next;
	}
	temp = NULL;
	sort(head);// sorts the list with head as the pointer to the first string

	temp = head;

	cout << "\nThe sorted list is:\n\n";
	while(temp!=NULL){
		temp->print(); cout << endl;
		temp = temp->next;
	}
}