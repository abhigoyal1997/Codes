//functions not directly used in resmain.cpp

#include "res.h"

string adminpass="qwerty";//admin password required to recharge user account
User active;

Time::Time(){
	h=0; m=0;
}

Time::Time(int hh, int mm){
	h=hh; m=mm;
}

bool Time::operator>(Time t){
	if(h>t.h)  return 1;
	if(h==t.h && m>t.m)  return 1;
	return 0;
}

bool Time::operator==(Time t){
	if(h==t.h && m==t.m) return 1;
	else return 0;
}

Time Time::operator-(Time t){
	int mins;
	mins=60*(h-t.h)+(m-t.m);
	Time temp(mins/60,mins%60);
	return temp;
}

void Time::print(){
	cout << setw(2) << setfill('0') << h << ':' << setw(2) << setfill('0') << m;
}

int mdays(int m, int y){//returns no. of days in a given month and year
	bool l=0;
	if((y%4==0 && y%100!=0) || y%400==0)  l=1;
	if(l && m==2)  return 29;
	switch(m){
		case 2:  return 28;
		case 4:  return 30;
		case 6:  return 30;
		case 9:  return 30;
		case 11: return 30;
		default: return 31;
	}
}

Date::Date(){
	d=1; m=1; y=2010;
}

Date::Date(int dd, int mm, int yy){
	if(yy>2009 && mm>0 && mm<13 && dd>0 && dd<mdays(mm,yy)+1){
		d=dd; m=mm; y=yy;
	}//initializes only for valid date
}

bool Date::operator>(Date x){
	if(y>x.y)  return 1;
	if(y==x.y && m>x.m)  return 1;
	if(y==x.y && m==x.m && d>x.d)  return 1;
	return 0;
}

bool Date::operator==(Date t){
	if(y==t.y && m==t.m && d==t.d) return 1;
	else return 0;
}

int Date::nday(){//returns (no. of days between journey date and current date +1)
	time_t currentTime;
	time(&currentTime);
	struct tm* localTime=localtime(&currentTime);
	Date current_date(localTime->tm_mday, localTime->tm_mon+1, localTime->tm_year+1900);//current system date

	int days=0;
	if(y==current_date.y){
		if(m==current_date.m){
			days=abs(d-current_date.d);
		}
		else{
			days=abs((mdays(m,y)-d+1)+current_date.d);
			for(int i=m+1; i<current_date.m; i++) days+=mdays(i,y);
		}
	}
	else{
		days=abs((mdays(m,y)-d)+current_date.d);
		for(int i=m+1; i<=12; i++) days+=mdays(i,y);
		for(int i=1; i<current_date.m; i++) days+=mdays(i,current_date.y);
	}
	return days;
}

int Date::day(){//returns day of week for a given date(sunday=0)
	int sm=(m+9)%12+1;
	return (d+(13*sm-1)/5+y%100+(y%100)/4+(y/100)/4-2*(y/100))%7;
}

void Date::print(){
	cout << d << '-' << m << '-' << y;
}

string day(int n){//returns day of week as string(0=sunday)
	string d[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	return d[n];
}

void User::initialize(string username, string password, string first, string last, long bal){
	uname=username; pass=password; fname=first; lname=last; balance=bal;
}

bool User::exist(){
	for(map<string,User>::iterator i=uzer.begin(); i!=uzer.end(); i++) if(uname==i->first) return 1;
	return 0;
}

bool User::check_pass(string password){
	if(password==pass) return 1;
	return 0;
}

void User::store_balance(){
	fstream file(userdata);
	string u,p,temp;
	while(!file.eof()){
		file >> u >> p;
		if(u==uname && p==pass){
			file >> temp >> temp;
			file << " " << setw(10) << setfill('0') << balance;
		}
		else file >> temp >> temp >> temp;
	}
}

void User::create(){
	ofstream ofile(userdata,ios::in|ios::app);
	cout << " Enter your First Name: "; cin >> fname;
	cout << " Enter your Last Name: "; cin >> lname;
	username:  cout << " Enter the Username you want to use: "; cin >> uname;
	if(exist()){
		cout << "\n Username is already taken. Try another.\n";
		goto username;
	}
	password: cout << " Enter a password not more than 20 characters: "; cin >> pass;
	if(pass.length()>20){
		cout << "\n Password length should not be more than 20 characters"; goto password;
	}
	balance=0;
	ofile << uname << " " << setw(20) << setfill(' ') << pass << " " << fname << " " << lname << " " << setw(10) << setfill('0') << balance << "\n\n";
	uzer[uname]=*this;
}

bool User::login(){
	system("clear");
  enter_uname:	cout << " Enter the Username: "; cin >> uname;
	cout << " Enter password: "; cin >> pass;
	for(map<string,User>::iterator i=uzer.begin(); i!=uzer.end(); i++){
		if((i->first)==uname && (i->second).pass==pass){
			*this=i->second;
			return 1;
		}
	}
	cout << "\n Invalid Username or password\n\n";
	cout << " 1: Try another"<<endl;
	cout << " 0: Return to the previous screen"<<endl;
	cout<<"\nEnter your choice: "; int query; cin >> query;
	if(query==1) goto enter_uname;
	else if(query==0) return 0;
}

void User::printname(){//to print in appropriate format for mainscreen() function
	int l=fname.length() + lname.length() + 1;
	string s=fname + ' ' + lname;
	cout << "*" << setw(35-l/2) << setfill(' ') << right << "Welcome " << s << setw(35-(l+1)/2) << setfill(' ') << "*" << endl;
	return;
}

void User::recharge(){//to recharge the account (admin password required)
	cout << "\nYour current account balance is: " << balance;

	enter_amount:	cout << "\nEnter the amount to recharge or 0 to return: ";
	long amount; cin >> amount;

	if(amount==0) return;

	if(amount<0){
		cout << "Enter a valid amount\n"; goto enter_amount;//for robustness
	}

	cout << "Enter the admin password: ";//to authenticate the admin
	string password; cin >> password;
	if(password==adminpass){
  recharge:
		balance+=amount;
		store_balance();
		cout << "\nRecharge successful\n Your new account balance is: " << balance << endl;
		cout << "\nEnter any key to return\n"; char q; cin >> q;
	}
	else{
		for(int i=0; i<2; i++){//gives only three chances to enter admin password(including the previous one)
			cout << "\nInvalid Password. Try again: ";
			cin >> password;
			if(password==adminpass) goto recharge;
		}
	}
}

void User::changepass(){//changes user password and stores it in the data file
	fstream file(userdata);
	string password,u,temp,p;
	for(int i=0; i<3; i++){
		cout << "\nEnter the current password: "; cin >> password;
		if(password!=pass){
			cout << "\nWrong password entered. Try again\n";
			if(i==2) return;
		}
		else break;
	}

	password: cout << "\nEnter the new password (not more than 20 characters long): "; cin >> password;
	cout << "Re-enter the new password: "; cin >> p;
	if(password.length()>20){
		cout << "\n Password length should not be more than 20 characters"; goto password;
	}
	if(password!=p){
		cout << "\n The two passwords don't match. Try again."; goto password;
	}
	while(!file.eof()){
		file >> u;
		if(u==uname){
			file << " " << setw(20) << setfill(' ') << password;
			pass=password;
			break;
		}
		else file >> temp >> temp >> temp >> temp;
	}
	cout << "\nPassword changed succesfully\nPress any key to return\n";
	char c; cin >> c;
	return;
}

void User::logout(){
	uzer[uname]=*this;       // updating the previously active user information in the map
	fname='\0';
	lname='\0';
	uname='\0';
	pass='\0';
	balance=0;
	ticket.clear();
	return;
}

long User::update_balance(long amount){
	balance+=amount;
	return balance;
}

void Train::printsch(){                                           //prints the schedule/route of the train
	cout << setw(5) << setfill('0') << num << '\t' << name << endl;
	cout << "\nSr.\tStation\tTime\tDistance\tDay\n\n";
	for(int i=0; i<nstops; i++){
		cout << setw(2) << setfill('0') << i+1 << '\t' <<station[i].sname << '\t';
		station[i].t.print();
		cout << '\t' << station[i].d << "\t\t" << station[i].day << endl;
	}
	cout << endl;
}

bool Train::station_index(string src, string dst, int &srci, int &dsti){
 	for(int i=0; i<nstops; i++){
 		for(int j=i+1; j<nstops; j++) if(src==station[i].sname && dst==station[j].sname){
			srci=i; dsti=j; return 1;
		}
	}
	return 0;
}


bool Seat::bkd(int si, int di){
    bool r=0;
    for(int i=si;i<di;i++) r=r||ocpd[i];
    return r;
}

int Coach::giveseat(int si,int di, int days){    //assigns an empty seat during booking, returns seat no. and then updates the information in the required objects i.e. vectors in Seat struct
    int i;
    for(i=0; i<64&&seat[days][i].bkd(si,di);) i++;
    for(int k=si; k<di; k++) {seat[days][i].ocpd[k]=1;  seat[days][i].user[k]=active;}
    return i;
}

int Coach::emptyseats(int si,int di, int days){// returns the no. of empty seats in a coach for a specific date
    int r=0;
    for(int i=0; i<64; i++) r+=seat[days][i].bkd(si,di);
    return 64-r;
}

void Coach::assigntype(int i){//assigns the type of coach user demands
    if (i>15) return;
    int typelist[]={0,0,1,2,2,2,2,2,2,2,2,3,3,3,4,5};
    type=typelist[i];
    return;
}

float Coach::multiplier(){//sets price for each coach type
    float pricemultipierlist[]={1,1.2,2.5,4,7,10};
    return pricemultipierlist[type];
}

void User::get_tkts(){//adds the pnr nos. of tickets booked by the user to the ticket vector
	for(map<long long,Ticket>::iterator i=tkt.begin(); i!=tkt.end(); i++) if((i->second).uname==uname) ticket.push_back(i->first);
}

void User::tkt_update(Ticket &t){
	t.uname=uname;
	ticket.push_back(t.pnr);
}

string stringoftype(int i){// just for printing the required coach type
    switch(i){
        case 0: return "SEATER CLASS";
        case 1: return "AC CHAIR CLASS";
        case 2: return "SLEEPER CLASS";
        case 3: return "3 TIER AC";
        case 4: return "2 TIER AC";
        case 5: return "1 TIER AC";
        default: return "ERROR";
    }
}

string berth(int seat){//to get the alloted berth in the train
	seat=seat%8;
	string b[]={"lower", "middle", "upper", "lower", "middle", "upper", "side lower", "side upper"};
	return b[seat];
}

void Train::book_ticket(int srci, int dsti){
    system("clear");
   	cout << "\n\nTRAIN NO.\t TRAIN NAME\t DISTANCE\t DEPARTURE\t ARIVAL\n\n";
   	cout << "  " << setw(5) << setfill('0') << num << "\t\t" << name << "\t    " << setw(4) << setfill('0') << station[dsti].d-station[srci].d << "\t   ";
	station[srci].t.print(); cout << "\t "; station[dsti].t.print(); cout << endl << endl;
	cout << "\nThe train runs on the following days: \n\n";
	for(int i=0; i<7; i++) if(station[srci].run[i]) cout << day(i) << "  ";
		cout << endl;
  enter_journey_date:	cout << "\nEnter the date of journey (in DD MM YYYY format): ";int d,m,y; cin >> d >> m >> y;
	Date journey_date(d,m,y);

	int journey_day=journey_date.day();

	if(!station[srci].run[journey_day]){                                               //checks if train runs on the date given by the user
		cout << "\nThe train doesn't run on this day \nEnter 1 to book for another date: ";
		char ch; cin >> ch; if(ch!='1') return;
		goto enter_journey_date;
	}

	Ticket tt;                                                                                  //creating a dummy ticket
    tt.date=journey_date; tt.dep=station[srci].t; tt.arr=station[dsti].t; tt.days=tt.date.nday();

	time_t currentTime;
	time(&currentTime);
	struct tm* localTime=localtime(&currentTime);
	Date current_date(localTime->tm_mday, localTime->tm_mon+1, localTime->tm_year+1900);
	Time current_time(localTime->tm_hour, localTime->tm_min);

	if(current_date>tt.date || (current_date==tt.date && current_time>tt.dep)){//checks if the train has already departed
		cout << "\nSorry the train has already departed \nEnter 1 to book for another date: ";
		char ch; cin >> ch; if(ch!='1') return;
		goto enter_journey_date;
	}

	if(tt.days>9){//restricting the booking upto 10 days from now(including current day)
		cout << "\nYou can only book tickets upto 10 days from now \nEnter 1 to book for another date: ";
		char ch; cin >> ch; if(ch!='1') return;
		goto enter_journey_date;
	}

    cout << "\n\nTickets are available in:-\n\n"<< setw(15)<<setfill(' ') << left <<"Type"<< setw(5)<<setfill(' ')<<"Coach"<< setw(7)<<setfill(' ')<<"Price"<< setw(15)<<setfill(' ')<<"No. of seats"<<endl;
    for(int i=0; i<16;i++) if(coach[i].emptyseats(srci,dsti,tt.days)) {//showing the availability of seats in different coaches
        coach[i].assigntype(i);
        int cost=(station[dsti].d-station[srci].d)*coach[i].multiplier();
        cout << setw(15)<<setfill(' ')<< left <<stringoftype(coach[i].type) << setw(5)<<setfill(' ')<< i  << setw(7)<<setfill(' ')<< cost <<setw(15)<<setfill(' ')<< coach[i].emptyseats(srci,dsti,tt.days)<<endl;
    }

    cout << "Which coach will you choose? (Insert 16 to go to main menu) : ";
  enter_coach:  int i; cin>>i;

 	if(i==16) return;
    if(i<0||i>15){
    	cout << "\nPlease enter coach no. from the list: "; goto enter_coach;
    }
    if(!coach[i].emptyseats(srci,dsti, tt.days)){
    	cout << "\nPlease enter coach no. from the list: "; goto enter_coach;
    }
    long cost=abs(station[srci].d-station[dsti].d)*coach[i].multiplier();//cost of ticket

    cout << "\nRs " << cost << " will be deducted from your balance. Continue? (Y/N) :";
    char yn; cin>>yn;

    if(!((yn=='Y')||(yn=='y'))) return;

    cout << "\nPlease enter your password: ";

    string password;
    for(int p=0; p<3; p++){//password verification
    	cin >> password;
	    if(active.check_pass(password)) break;
    	if(p>=2) return;
    	cout <<"\nThe password you entered is incorrect. Tryagain: ";
	}

    if(active.update_balance(0)<cost){
        cout<<endl<<"Not enough balance. Please contact admin to recharge your account.(Press any key to go to main menu.) :";
        char temp; cin>>temp; return;
    }

    int seatnum=coach[i].giveseat(srci,dsti, tt.days);

    tt.pnr=tt.date.d+10*((num)*65*50*50*20+i*65*50*50+srci*65*50+dsti*65+seatnum);//arbitrary formula which ensures that every booked ticket gets a unique pnr no.
    tt.price=cost;
    tt.train=num; tt.seat=seatnum; tt.coach=i;
    tt.src=station[srci].sname; tt.dst=station[dsti].sname;
    active.tkt_update(tt); tkt[tt.pnr]=tt;//updating the information of booked ticket in the required places
    cout << "\n\nSeat number " << seatnum+1 << "(" << berth(seatnum) << " berth) of coach " << i << " is booked for you. Your balance after  transaction is Rs " << active.update_balance(-1*cost) << ". (Press any key to continue.)";
    cin >> yn; return;
}

void Ticket::tkt_print(){//prints the ticket information given pnr
	cout << "\nPNR No.:\t" << pnr << "\n" << "Train no.:\t" << setw(5) << setfill('0') << train << "\n" << "Source:\t\t" << src << "\n" << "Destination:\t" << dst;
	cout << "\n" << "Coach: " << coach << "\tSeat no. " << seat+1 << "\tBerth: " << berth(seat);
	cout << "\nPrice: " << price << endl;
	cout << "Jorney Date: "; date.print();cout << "\t\t";
	cout << "Departure: "; dep.print(); cout << "\t";
	cout << "Arrival: "; arr.print(); cout << endl;
}

string Food::vnv(){
    if (veg) return "Veg";
    else return "Non-Veg";
}
