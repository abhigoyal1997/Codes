#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

struct Time{
	int h,m;
	Time();
	Time(int hh, int mm);
	bool operator>(Time t);
	bool operator==(Time t);
	Time operator-(Time t);//returns difference in hrs and mins
	void print();
};

struct Date{
	int d,m,y;
	Date();
	Date(int dd, int mm, int yy);
	bool operator>(Date t);
	bool operator==(Date t);
	int day();//returns the day of week(sunday=0)
	int nday();//returns no. of days between given date and current date +1
	void print();
};

struct Station{
	string sname;//station name
	bool run[7];//tells on which day train comes at this station
	Time t;//arrival time
	int day;//running day of train since it departed from source of train(assuming it to be 1 at source of train)
	int d;//distance from source of train
};

struct Ticket{
	string uname/*username*/, src/*source code*/, dst/*destination code*/; long long pnr; int price, train/*train no.*/, coach, seat, days/*days left for journey*/;
	Date date;/*journey date*/
	Time arr/*arrival*/, dep/*departure*/;
	void tkt_print();//prints information of ticket
};

struct Food{
    string name;
    bool veg;
    int price;
    string vnv();//returns "Veg" if veg and "Non Veg" otherwise
};

class User{
 	string pass/*password*/;  long balance;
  public:
 	string fname/*first name*/, lname/*last name*/, uname/*username*/;
	vector<long long> ticket;//stores pnr nos. of tickets booked by this user
	void initialize(string username, string password, string first, string last, long balance);//mainly to initialize the members of uzer map
	bool check_pass(string password);//______________//returns 1 if enteres password is correct
 	bool exist();//tells if the user with given username exists or not
	void create();//create a new user
	bool login();
	void printname();//prints name of user
	void logout();
	void recharge();
	void store_balance();//stores the new user balance in the datafile
	void changepass();//to change password
	void get_tkts();//stores pnr nos. of tickets booked by user in ticket vector
	void tkt_update(Ticket &t);//updates ticket vector on booking of a ticket
	long update_balance(long amount);//to update the balance and then return new one
};

struct Seat{
    vector<User> user;
    vector<bool> ocpd;//size=(no. of stops of train-1) tells if the seat is booked between consecutive stops
    bool bkd(int si, int di);//tells if the seat is booked between given two stops si=source code di=destination code
};

struct Coach{
    Seat seat[10][64];//total no. seats =64 & first index gives the day of journey from today(index=0 means today)
    int type;
    float multiplier();//price multiplier
    void assigntype(int i);//returns type of coach assigned during booking
    int emptyseats(int si, int di, int days);//tells no. of available seats
    int giveseat(int si,int di, int days);//assigns an empty seat during booking
};

struct Train{
	string name;
	long num/*train_no.*/, nstops/*no.of stops*/;
	Coach coach[16];
	vector<Station> station;//size=nstops
	void printsch();//prints schedule of the train
	bool station_index(string src, string dst, int &srci, int &dsti);//gives source station index and destination station index given their codes
	void book_ticket(int srci, int dsti);//to book a ticket given source and destination station indices
};

void printindex(bool b);//prints the complete index of trains
void schedule();//to get schedule of a train
void get_train();//to get trains between two stations
void run_enquiry();//for running train enquiry like which is the next station and time remaining for it to arrive and time remaining for destination to arrive
void load_train();//to load train data
void load_ticket();//to load ticket data
void load_user();//to load user data
void load_foodmenu();//to load foodmenu
void save_ticketdata();//to save the new booked and cancelled tickets
void save_userbalance();//to save the user balance in the userdata file
void tkt_cancel();//ticket cancellation
void order_food();


extern User active;//active user//  defined as global variables
extern map<long long,Ticket> tkt;//stores all tickets with pnr as index//    defined as global variables
extern map<int,Train> t;//stores all trains with train no. as index//  defined as global variables
extern map<string,User> uzer;//stores all users with username as index//  defined as global variables
extern vector<Food> menu;//stores the food menu//  defined as global variables
extern const char traindata[], ticketdata[], userdata[], foodmenu[];
