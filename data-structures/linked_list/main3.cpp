#include "list_of_list.h"

void insertData(datastore<int> &x){
	int n; cin >> n;
	int in;
	while(n--){
		cin >> in;
		x.insert(in);
	}
}

int main(){

	datastore<int> x;
	char ch;
	cin>>ch;
	while(ch!='q'){
		int in; int inp;
		
		switch(ch){
			case 'i':	insertData(x);
				 		break;
			case 'p':	x.print();
					 	break;
			case 's':	cin >> in;
						cout << x.search(in) << endl;
						break;
			case 'm':	cout << x.find_max() << endl;
					 	break;	
			case 'l':	x.list_max();
						break;
			case 'z':	x.list_zero();
						break;
			case 'c':	cin >> inp;
						x.list_count(inp);
						break;
			case 'e':	cin >> in;
						cout << x.eject(in) << endl;
						break;
			case 'x':	break;
			case 'd':	cin >> in;
						x.decrement(in);
						break;
			case 'r':	x.reset();
		}

		cin>>ch;
	}

	return 0;
}
