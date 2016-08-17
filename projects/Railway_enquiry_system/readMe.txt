In our project, we have imitated the official ticket reservation website of Indian railways. This program can be actually be used as an enquiry machine, because it saves the data even after exiting the program.


Instructions to run:-

Use command ./a.out to run the program through bash. If it is not compiled, you can compile it as follows.
Compile res.cpp, resmain.cpp and trainres.cpp together with any c++ compiler (Use g++ if possible).
Using g++: g++ res.cpp resmain.cpp trainres.cpp
This should create an executable file a.out. Use command ./a.out to run the program


Login screen:-

We have maintained an account for each and every user of program, which contains information about him and his balance.

One is allowed to login to existing account or create a new account when the program is started, or exit the program. List of usernames and passwords is stored in the file “userdata” new users’ data gets saved at the end.  Both username and password must be less than 20 characters.

Sample username and password: 
Username: 123
Password: 123


Main screen:-

This is like the index of the program. The choice is then entered and the corresponding window of that function opens.

(1) Schedule of a particular train
First the available trains are showed up. Right now we have data for 16 trains(More can be added easily). Enter the number of the train you are interested in and its schedule will show up. It includes all the station it stops at, along with the time at which it stops, and their distance from the source station. If a train runs for multiple days, it also shows the day of travel.

NOTE: All times in this program are in the format of 24 hrs HH:MM, and dates in the format DD MM YYYY. Please enter in this format, wherever required.

In our program, the day of travel is absolute and same for all passengers, irrespective of their source and destination.
Train starts its journey at day 1.

(2) Get list of trains between 2 stations or book a ticket
This is used to book tickets.
Enter the source and destinition stations of your journey. For that you must know the station codes. Note that all stations of India are not included in our data. Station codes must be in CAPITALS.
Sample data: 
Source: NDLS 
Destination:  KOTA

All the trains between these two stations are displayed. Choice is given if you want to book tickets or get further information about the trains. If you choose to book tickets, number of the desired train is to be entered next. This shows further information about the train and also asks the date of journey. 

Tickets can be booked only upto 10 days from today. Also the train runs only on particular days of the week. Only dates corresponding to those days can be selected. 
If tickets are available, the coaches which are not full are displayed, along with their types, ticket prices, and number of available seats.
Ticket price is directly proportional to the distance between two stations. It does not depend on the train, but only on the type of the coach.
Select the coach you want to book a ticket in. you are asked to confirm booking.
If you do not have enough balance, a message regarding so is displayed and you need to add money to your account through option 6 of main screen. We maintain a record of balance of each user of this program, which remains saved even after the program is terminated. 
If balance is available, it is deducted by the appropriate amount, and a ticket pnr is generated. This pnr acts as a handle for the ticket in later use. The information regarding the booking is saved.

(3) Enquiry about a running train
This shows the current status of running train. You are asked to enter the train number. After you enter the number, you need to enter its today’s day of journey. For example, if train started yesterday, you should enter 2.
Sample data: 
Train num: 12618 (Runs every day, so no error of invalid query)
Day: 1
This will show up the next station, or the current status of train (ie “train not yet departed” or “train reached destination”). Output depends on current time. 
It also gives the option of checking the time left for journey, which also depends on passenger’s destination station.

(4) Order food
Food can be ordered through this option. The menu is displayed, along with price and veg/nonveg category. 
Enter the indexes of required items, followed by their quantities. Enter 0 when order is finished. For example, if you want 4 Aloo parathas and 3 veg biryanis, you should enter “3 4 8 3 0” 
If you don’t have enough balance, you will be asked to recharge.
If you have enough balance, total will be displayed and you will be asked to confirm. Then enter your password to finalize the order. The bill will be deducted from your balance. Updated balance will be displayed.

(5)  Cancel ticket
First, pnr of all the tickets booked by you will be displayed. You can get more details about a ticket by entering 1 and then entering pnr. You can also directly cancel by entering 2 and then entering pnr.
If you enter pnr,the amount of refund you will get is shown. Refund is 80% of cost of ticket. You will be given choice to continue cancellation. Then you will need your password to confirm cancellation. This will cancel the ticket and it will again be available for booking. The refund will be credited to your balance. Updated balance will be displayed.

(6) See current account balance or recharge
First the present account balance is shown. Enter the amount to recharge or enter 0 to return without recharging. Only the administrator can recharge. After entering amount, you will be asked for admin password, which is “qwerty” by default. Updated balance is shown.

(7) Change the account password
The current password is asked for confirmation and then you are asked to enter the new password. Re-enter the new password to confirm. Change in password is recorded in “userdata” file.

(0)Log out
Logs out your account for signing in through different user or exiting the program. Takes you to login screen.