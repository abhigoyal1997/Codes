//includes functions used in resmain.cpp directly except member functions

#include "res.h"

map<long long,Ticket> tkt;//stores all the booked tickets which are not expired
map<int,Train> t;//stores all the information about trains
map<string,User> uzer;//stores the information about users
vector<Food> menu;

void load_train(){//to load the train information
	ifstream file(traindata);

	while(!file.eof()){

		int num; file >> num; t[num].num=num;

		file >> t[num].name;

		file >> t[num].nstops;


		t[num].station.resize(t[num].nstops);
		for(int i=0; i<7; i++)	file >> t[num].station[0].run[i];

		for(int i=0; i<16; i++)	for(int k=0; k<10; k++){
			for(int j=0; j<64; j++){
				t[num].coach[i].seat[k][j].user.resize(t[num].nstops-1);
				t[num].coach[i].seat[k][j].ocpd.resize(t[num].nstops-1);
			}
		}
		for(int i=0; i<t[num].nstops; i++){
			file >> t[num].station[i].sname;
			file >> t[num].station[i].t.h;
			file >> t[num].station[i].t.m;
			file >> t[num].station[i].d;
			file >> t[num].station[i].day;
			int day=t[num].station[i].day;
			if(i==0) continue;
			for(int j=0; j<7; j++){
				t[num].station[i].run[(j+day-1)%7]=t[num].station[0].run[j];
			}
		}
	}
	file.close();
}

void load_seat(){//initializes the seat array for all coaches of resp. trains
	if(tkt.begin()==tkt.end()) return;
	for(map<long long,Ticket>::iterator i=tkt.begin(); i!=tkt.end(); i++){
		int si,di;
		t[(i->second).train].station_index((i->second).src,(i->second).dst,si,di);
		for(int j=si; j<di; j++){
			t[(i->second).train].coach[(i->second).coach].seat[(i->second).days][(i->second).seat].user[j]=uzer[(i->second).uname];
			t[(i->second).train].coach[(i->second).coach].seat[(i->second).days][(i->second).seat].ocpd[j]=1;
		}
	}
}

void load_ticket(){//to load information about booked tickets
	ifstream ifile(ticketdata);//data stored in file "ticketdata"

	time_t currentTime;//to get current system date and time
	time(&currentTime);
	struct tm* localTime=localtime(&currentTime);
	Date current_date(localTime->tm_mday, localTime->tm_mon+1, localTime->tm_year+1900);//storing current system date
	Time current_time(localTime->tm_hour, localTime->tm_min);//storing current system time

	string s; ifile >> s;
	if(s=="0") goto ifile_close;//to check if there are 0 booked tickets
	else ifile.seekg(0);
	while(!ifile.eof()){
		Ticket temp; ifile >> temp.pnr;
		ifile >> temp.uname >> temp.train >> temp.coach >> temp.seat >> temp.src >> temp.dst >> temp.date.d >> temp.date.m >> temp.date.y >> temp.price;
		int srci, dsti;
		t[temp.train].station_index(temp.src, temp.dst, srci, dsti);
		temp.dep=t[temp.train].station[srci].t; temp.arr=t[temp.train].station[dsti].t;
		temp.days=temp.date.nday();
		if(current_date>temp.date || (current_date==temp.date && current_time>temp.dep)) continue;//skips the expired ticket by comparing its departure date & time with current date & time
		tkt[temp.pnr]=temp;
		uzer[tkt[temp.pnr].uname].ticket.push_back(temp.pnr);
	}
  ifile_close:	ifile.close();
}

void load_foodmenu(){//to load food menu
	ifstream fmenu(foodmenu);//data stored in file "foodmenu"

	while(!fmenu.eof()){
        Food temp;
        fmenu>>temp.name>>temp.price>>temp.veg;
        menu.push_back(temp);
	}
	fmenu.close();
}

void load_user(){//to load the user information
	ifstream ufile(userdata);//data stored in file "userdata"
	while(!ufile.eof()){
		string uname, pass, fname, lname; long balance;
		ufile >> uname;
		ufile >> pass >> fname >> lname >> balance;
		uzer[uname].initialize(uname,pass,fname,lname,balance);
	}
	ufile.close();
	load_seat();
}

void save_ticketdata(){//to update the ticket, called at end of program
	ofstream file(ticketdata);
	if(tkt.begin()==tkt.end()){
		file << '0';
		return;
	}
	for(map<long long,Ticket>::iterator i=tkt.begin(); i!=tkt.end(); i++){
		if(i->first==0 || (i->second).train==0) continue;//to skip null ticket like cancelled tickets

		file << i->first << " " << (i->second).uname << " " << (i->second).train << " " << (i->second).coach << " " << (i->second).seat << " " << (i->second).src << " " << (i->second).dst << " ";
		file << " " << (i->second).date.d << " " << (i->second).date.m << " " << (i->second).date.y << " " << (i->second).price << endl;
	}
	file.close();
}

void save_userbalance(){//to update the balance of all users,called at end of program
	for(map<string,User>::iterator i=uzer.begin(); i!=uzer.end(); i++) (i->second).store_balance();
	uzer.clear();
}

void printindex(bool b){//prints all the trains along with their train nos., takes true as argument if clear screen required
	if(b) system("clear");
	cout << "Index:-" << endl << endl;
	for(map<int,Train>::iterator i=t.begin(); i!=t.end(); i++){
		cout << setw(5) << setfill('0') << i->first << '	' << (i->second).name << endl;
	}
}

void schedule(){
	cout << "Enter the Train number or enter 0 to exit: ";
  enter_tn:	int tn;  cin >> tn;
	bool valid=0;
	if(tn==0) return;
	for(map<int,Train>::iterator i=t.begin(); i!=t.end(); i++){   //ensures that user enters valid train no.
		if(tn==i->first) valid=1;
	}
	if(!valid){
		cout << "Please enter a valid train no.: "; goto enter_tn;
	}
	system("clear");
	t[tn].printsch();
	cout << "Enter any character to return\n";
	char c; cin >> c;
	return;
}

void get_train(){
	system("clear");
	enter_source:	cout << "Enter the source station code: ";
	string src; cin >> src;
	cout << "Enter the destination station code: ";
	string dst; cin >> dst;

	int srci, dsti; bool valid=0;//srci=source index  dsti=destination index

	system("clear");
	vector<int> train;//to ensure that user enter a train no. from the given list only when asked
	cout << "\n\nTRAIN NO.\t" << setw(20) <<  "TRAIN NAME\t DISTANCE\t DEPARTURE\t ARIVAL\n\n";
	for(map<int,Train>::iterator i=t.begin(); i!=t.end(); i++){
		if((i->second).station_index(src, dst, srci, dsti)){
			cout << "  " << setw(5) << setfill('0') << i->first << "\t" <<  right << setw(20) << setfill(' ') << t[i->first].name << "\t    " << setw(4) << setfill(' ') << (i->second).station[dsti].d-(i->second).station[srci].d << "\t   ";
			(i->second).station[srci].t.print(); cout << "\t "; (i->second).station[dsti].t.print(); cout << endl << endl;
			valid=1;
			train.push_back(i->first);
		}
	}

	if(!valid){
		system("clear");
		cout << "Invalid Input\n\n";
		cout << " 1: Try another"<<endl;
		cout << " 0: Return to the mainscreen"<<endl;
		cout<<"\nEnter your choice: "; int query; cin >> query;
		if(query==1) goto enter_source;
		else if(query==0) return;
	}

	cout << " 1: See complete schedule of a train"<<endl;
	cout << " 2: Book a ticket" << endl;
	cout << " 0: Return to the mainscreen"<<endl;
	cout<<"\nEnter your choice: "; int query; cin >> query;
	if(query==1) schedule();
	else if(query==2){
		cout << "Enter a train number from the above list: ";
	  enter_tnum:	int tnum; cin >> tnum;
		bool tn=0;
		for(size_t i=0; i<train.size(); i++) tn=tn||(tnum==train[i]);
		if(!tn){
			cout << "Please enter a train number form the above list only: "; goto enter_tnum;
		}
		t[tnum].station_index(src, dst, srci, dsti);//getting the indices of the source and destination stations
		t[tnum].book_ticket(srci, dsti);
	}
	else if(query==0) return;
}

void tkt_cancel(){
	cout << "The following tickets have been booked in your name:\n\n";
	cout << "PNR No.\n";
	for(size_t i=0; i<active.ticket.size(); i++) cout << active.ticket[i] << endl;//prints pnr nos. of the tickets booked by the active user
	cout << "\n 1: See complete details of a ticket"<<endl;
	cout << " 2: Cancel a ticket" << endl;
	cout << " 0: Return to the mainscreen"<<endl;
	cout<<"\nEnter your choice: "; int query; cin >> query;
	if(query==0) return;
	long long pnr;
 	cout << "\nEnter the PNR no.: "; cin >> pnr;
	if(tkt[pnr].uname!=active.uname){//checks if the pnr entered by the user is one from the pnr nos. of tickets bookes by him
		cout << "\nThis ticket is not booked by you\n"; int x; cin >> x;
		return;
	}
	if(query==1){
		tkt[pnr].tkt_print();
		cout << "\nEnter 1 if you want to cancel this ticket or any other character to return: ";
		int q; cin >> q;
		if(q!=1) return;
	}
	int refund=0.8*tkt[pnr].price;
	cout << "\nYou will get a refund of Rs. " << refund;
	cout << "\nAre you sure you want to cancel this ticket?(Enter Y to confirm)  "; char ch; cin >> ch;
	if(ch!='y' && ch!='Y') return;

	string password;
	cout << "\nEnter you password: ";
	for(int p=0; p<3; p++){//password verification
    	cin >> password;
    	if(active.check_pass(password)) break;
    	if(p>=2) return;
    	cout <<"\nThe password you entered is incorrect. Tryagain: ";
	}

	vector<long long>::iterator it;//to find and erase the cancelled ticket from the ticket vector member of the User struct
  	it = find (active.ticket.begin(), active.ticket.end(), pnr);
  	int si,di;
  	t[tkt[pnr].train].station_index(tkt[pnr].src, tkt[pnr].dst, si, di);
  	for(size_t i=si; i<di; i++){
  		t[tkt[pnr].train].coach[tkt[pnr].coach].seat[tkt[pnr].days][tkt[pnr].seat].ocpd[i]=0;
  	}
  	tkt.erase(pnr); active.ticket.erase(it);
	cout << "\nYour ticket is succesfully canceled\nYour new account balance is: " << active.update_balance(refund) << "\nEnter any character to return: ";
	char x; cin >>x;
}

void run_enquiry(){
	system("clear");

	time_t currentTime;
	time(&currentTime);
	struct tm* localTime=localtime(&currentTime);
	Date current_date(localTime->tm_mday, localTime->tm_mon+1, localTime->tm_year+1900);
	Time current_time(localTime->tm_hour, localTime->tm_min);
	int day=current_date.day();
	int next_day=day;

  enter_trainnum:	bool valid=0;
	cout << "\nEnter the train no.: "; int tnum, i=1; cin >> tnum;
	for(map<int,Train>::iterator i=t.begin(); i!=t.end(); i++){       //ensures that user enters valid train no.
		if(tnum==i->first) valid=1;
	}
	if(!valid) goto invalid;

	cout << "\nEnter day of journey(assuming that train departed from source on day 1): "; int t_day; cin >> t_day;

	if(t_day>t[tnum].station[t[tnum].nstops-1].day || t_day<1){//checks if the input by user is valid
		valid=0; goto invalid;
	}
	if(t_day==t[tnum].station[t[tnum].nstops-1].day && current_time>t[tnum].station[t[tnum].nstops-1].t){//checks if the train has already reached its destination
		cout << "\nThe train has reached the destination \nEnter any character to return\n"; char q; cin >> q; return;
	}
	if(t_day==1 && t[tnum].station[0].t>current_time){//checks if the train har departed or not
		cout << "\nThe train has not yet departed from the source \nEnter any character to return\n"; char q; cin >> q; return;
	}
	for(i=1; i<t[tnum].nstops; i++){
		if(t[tnum].station[i].day==t_day && t[tnum].station[i].run[day] && t[tnum].station[i].t>current_time){
			valid=1; goto next_station;
		}
	}
	for(i=1; i<t[tnum].nstops; i++){
		if(t[tnum].station[i].day==t_day+1 && t[tnum].station[i].run[(day+1)%7]){
			valid=1; next_day++; break;
		}
	}

  invalid:	if(!valid){
		cout << "\nInvalid enquiry \nEnter 1 to try again: "; char ch; cin >> ch;
		if(ch=='1') goto enter_trainnum;
		else return;
	}

  next_station:	cout << "\nThe next station is: " << t[tnum].station[i].sname << endl;
	cout << "\nTime remaining for next station to come: ";

	Time temp=t[tnum].station[i].t;
	if(next_day==day+1) temp.h+=24;
	temp=temp-current_time; temp.print();

	cout << "\nEnter 1 to see the time left for your journey: "; char ch; cin >> ch;
	if(ch!='1') return;
	cout << "\nEnter your destination station code: "; string dst;

  dst:	cin >> dst;

	if(dst==t[tnum].station[i].sname){
		cout << "\nTime left for you journey: ";
		temp.print(); return;
	}

	bool dst_valid=0;
  	int j=0;
	for(j=i+1; j<t[tnum].nstops; j++) if(t[tnum].station[j].sname==dst){
		dst_valid=1; break;
	}
	if(!dst_valid){
		cout << "\nPlease enter a valid destination code or 0 to return: "; cin >> dst;
		if(dst=="0") return; goto dst;
	}
	cout << "\nTime left for your journey: ";

	temp=t[tnum].station[j].t; next_day=next_day+(t[tnum].station[j].day-t[tnum].station[i].day);
	temp.h+=24*(next_day-day);
	temp=temp-current_time; temp.print();

	cout << "\n\nEnter any character to return\n"; char x; cin >> x;
}

void order_food(){
    cout<<"\nIndex\tItem name\tPrice\tVeg/Non-veg\n\n";

    for(size_t i=0; i<menu.size()-1; i++){
        cout<<i+1<<"\t"<<menu[i].name<<"\t"<<menu[i].price<<"\t"<<menu[i].vnv()<<"\n";
    }

    query: cout<<"\nEnter the index of the items you want to eat followed by their quantities\neg. to order 3 items having index 2 you should enter 2 3 followed by 0 when finished(enter 0 when finished)\n";

    int index, quantity, cost=0;
    int tempi=0;
    while(true){
    	cin >> index;
    	if(index==0 && tempi==0) return;
    	if(index==0) break;
      enter_index:	if(index<0 || index>menu.size()){ cout<<"\nPlease enter valid index or 0 to finish: "; goto enter_index; }

      enter_quantity:	cin >> quantity; if(quantity<0){ cout << "\nPlease enter valid quantity: "; goto enter_quantity; }

    	cost+=menu[index-1].price*quantity;
    	tempi++;
    }

    cout<<"\nYour order has been taken. Rs "<<cost<<" will be deducted from your account. Enter Y to confirm : ";
    char yn; cin>>yn;

	if(!((yn=='Y')||(yn=='y'))) return;

	string password;
	cout << "\nEnter you password: ";
	for(int p=0; p<3; p++){//password verification, maximum 3 attempts
    	cin >> password;
    	if(active.check_pass(password)) break;
    	if(p>=2) return;
    	cout <<"\nThe password you entered is incorrect. Tryagain: ";
	}

    if(active.update_balance(0)<cost){
        cout<<endl<<"Not enough balance. Please contact admin to recharge your account.(Enter any character to go to main menu.) :";
        char temp; cin>>temp; return;
    }


    cout<<endl<<"Food will be delivered soon. Your balance after deduction is: " << active.update_balance(-1*cost);
    cout << "\nEnjoy the journey! (Enter any character to go to main menu.) :";
    active.store_balance();

    char temp; cin>>temp; return;
}
