/*
Bill Sharing Application
						
Problem Definition:
    To create a bill sharing application (like splitwise)
						
The application features are as follows:
	- The application must have a concept of a group - which is basically a collection of registered users.
    - A registered user can belong to multiple groups.
    - A person should be able to add a bill to the application. The bill will contain
        - Total Amount of the bill
        - People involved and their share of contribution
        - People can split bill.
        - Group to which that bill get added.							
    - The application should keep track of all such bills. Also, the application should be able to display two things:
        - Group wise balances to a user
        - Total Balance to a user
    - To summarise, we expect the following features
        - Ability to register a bill against a group with a list of participating users
        - Users must be able to record contributions to these bills by way of specifying exact amount they owe or by % of share of the total
        - A user must be able to view group wise balances
								
For example: Mudit registers a bill for lunch totalling 300 rupees. The bill is to be split equally among Mudit, Sourav and Souvik.
Mudit has paid 250 while Souvik shelled out 50 rupees to complete the bill. Thus, Mudit should get back 150 rupees while Sourav and Souvik
need to give back 100 and 50 rupees respectively in order to balance out the bill.
								
Bonus:
 - Support individual (person to person) balances.
 - A person should be able to settle up bill
 - A person should be able to remove people from group (only if user is settled up)
 - Also take care of concurrency issues that can arise out of multiple persons registering bills at the same time.


								
Expectation:
		
Code should be functionally complete.							
Code should be modular.
Design should be extensible.
The code should be parameterized rather than hard coded.

*/
#include <bits/stdc++.h>
#include <iostream>
#include <map>

using namespace std;

class User {
    private:
        string name;
        map<string, double> balances;

    public:
        User(string name) {
            this->name = name;
        }
        string getName() {
            return name;
        }      
        void addBalance(string key, double value) {
            balances[key] = value;
        }

        void displayBalance() {
            for(auto &it: balances) {
                cout << it.first << " Banlance: " << it.second << endl;
            }
        }
};


class Bill {
    private:
        string groupName;
        int amount;
        map<string, int> contributions;

    public:
        Bill(string groupName, int amount){
            this->groupName = groupName;
            this->amount = amount;
        }
        int getAmount() {
            return amount;
        }
         
        map<string, int> getContributions() {
            return contributions;
        }

        void addContributions(string name, int amountPaid) {
            contributions[name] += amountPaid;
        }
};

class Group {
    private:
        string name;
        vector<User> users;
        vector<Bill> bills;

    public:
        Group(string name) {
            this->name = name;
        }

    void addUsers(User user) {
        users.push_back(user);
    }

    void addBill(Bill b1) {
        bills.push_back(b1);
    }

    void calculateGroupBalances() {
        map<string, double> balances;
        for(auto &bill: bills) {
            double sharePerPerson = bill.getAmount() / users.size();
            for(auto &entry: bill.getContributions()){
                balances[entry.first] = entry.second - sharePerPerson;
            }
        }

        for(auto &user: users){
            user.addBalance(user.getName(), balances[user.getName()]);
        }
    }

    void displayGroupBalances() {
        for(auto &user: users) {
            user.displayBalance();
        }
    }
};


int main() {

    User u1("Naman");
    User u2("Nipun");
    User u3("Aastha");

    Group g1("Trio");

    g1.addUsers(u1);
    g1.addUsers(u2);
    g1.addUsers(u3);

    Bill b1("Lunch", 300);
    b1.addContributions(u1.getName(), 250);
    b1.addContributions(u2.getName(), 50);
    b1.addContributions(u2.getName(), 0);

    g1.addBill(b1);
    g1.calculateGroupBalances();
    g1.displayGroupBalances();


    return 0;
}