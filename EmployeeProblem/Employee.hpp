#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Employee {
    private:
        string name;
        int id;
        double salary;
    public: 
        Employee(string name, int id, double salary) {
            this->name = name;
            this->id = id;
            this->salary = salary;
        }

        // getter and setter method
        void setName(string name) {
            this->name = name;
        }
        string getName() {
            return name;
        }
        void setId(int id) {
            this->id = id;
        }
        int getId() {
            return id;
        }
        void setSalary(double salary) {
            this->salary = salary;
        }
        int getSalary() {
            return salary;
        }

        void getDetails() {
            cout << "The employee Name is " << getName() << " with ID " << getId() << " and have salary " << getSalary() << endl;
        }
};
