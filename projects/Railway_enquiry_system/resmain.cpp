#include "res.h"

const char traindata[]="traindata", ticketdata[]="ticketdata", foodmenu[]="foodmenu", userdata[]="userdata";

int loginscreen(){//sign in or sign up or exit query
	system("clear");
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
		cout << "*                  WELCOME TO RAILWAY ENQUIRY SYSTEM                  *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "*   1: Login as an existing user                                      *"<<endl;
		cout << "*   2: Create a new user account                                      *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "*   0: Exit                                                           *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
		cout<<"\nEnter your choice: "; int query; cin >> query;
		system("clear");
		return query;
}

int mainscreen(){//index of the program
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
		active.printname();
		cout << "*                                                                     *"<<endl;
		cout << "*   What would you like to do?                                        *"<<endl;
		cout << "*   1: See schedule of a particular train                             *"<<endl;
		cout << "*   2: Get list of trains between 2 stations or book a ticket         *"<<endl;
		cout << "*   3: Do enquiry about a running train                               *"<<endl;
		cout << "*   4: Order food                                                     *"<<endl;
		cout << "*   5: Cancel a Ticket                                                *"<<endl;
		cout << "*   6: See current account balance or recharge                        *"<<endl;
		cout << "*   7: Change the account password                                    *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "*   0: Logout                                                         *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "*                                                                     *"<<endl;
		cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
		cout<<"\nEnter your choice: "; int query; cin >> query;
		return query;
}

int main(){

	load_train();
	load_ticket();
	load_user();
	load_foodmenu();

	login: int login=loginscreen();

	switch(login){
		case 1: if(!active.login()) goto login; break;
		case 2: active.create(); break;
		case 0: remove(ticketdata);
				save_ticketdata(); save_userbalance();
				system("clear"); return 0;
	}

	while(1){
		system("clear");
		int query=mainscreen();
		system("clear");
		switch(query){
			case 1:
				printindex(1);
				schedule(); break;
			case 2: get_train(); break;
			case 3: run_enquiry(); break;
			case 4: order_food(); break;
			case 5: tkt_cancel(); break;
			case 6: active.recharge(); break;
			case 7: active.changepass(); break;
			case 0: active.logout(); goto login;
			default: cout<<"INVALID INPUT !!!"<<endl;
		}
	}
}
