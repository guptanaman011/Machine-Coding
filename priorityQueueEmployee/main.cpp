/*
Problem: Employee Priority Queue
Design a system to manage a priority queue of employees based on their performance ratings. Each employee has the following attributes:

Name
Employee ID
Performance Rating (a numerical value indicating the employee's performance)
Implement the following functionalities:

Add an employee to the priority queue.
Remove the employee with the highest performance rating from the queue.
Update the performance rating of an employee.
Get the employee with the highest performance rating without removing them from the queue.
Check if the priority queue is empty.
Display the names and performance ratings of all employees in the queue sorted by performance rating (highest to lowest).
You need to implement a PriorityQueue class with methods to perform the above operations. Use a max heap data structure based on the performance rating attribute to maintain the priority queue.


PriorityQueue pq;

pq.addEmployee("John", 101, 85);
pq.addEmployee("Alice", 102, 92);
pq.addEmployee("Bob", 103, 78);

pq.updatePerformanceRating(101, 90);

pq.removeHighestRatedEmployee();

cout << "Employee with the highest performance: " << pq.getHighestRatedEmployee().name << endl;

pq.displayEmployees();


Employee with the highest performance: John
Employee Name     Performance Rating
John              90
Alice             92
Bob               78


** Same question with priority queue with multiple levels -> If performance rating of 2 employee is equal, use goodness rating, use fairness rating, use no of years of exp (less)

*/
#include <iostream>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

class Employee {
    private:
        string empName;
        int empId;
        int performaceRating;
    public:
        Employee(string empName, int empId, int performaceRating) {
            this->empName = empName;
            this->empId = empId;
            this->performaceRating = performaceRating;
        }

        // getter methods
        string getEmpName() {
            return empName;
        }

        int getEmpId() {
            return empId;
        }

        int getPerformanceRating() {
            return performaceRating;
        }

        void updatePerformanceRating(int performaceRating) {
            this->performaceRating = performaceRating;
        }

        void displayEmployeeDetails() {
            cout << "EmpName - " << empName << endl;
            cout << "EmpId - " << empId << endl;
            cout << "Performance rating - " << performaceRating << endl; 
        }
};

class Employees {
    private:
        struct CompareEmployee {
            bool operator()(Employee& e1, Employee& e2) {  
                return e1.getPerformanceRating() < e2.getPerformanceRating();
            }
        };
        priority_queue<Employee, vector<Employee>, CompareEmployee> pq;
    public:
        void addEmployee(Employee &emp) {
            pq.push(emp);
            cout << "Employee Added" << endl;
        }

        void removeEmployeeWithHighestRating() {
            cout << "Size -> " << pq.size() << endl;
            // if (!pq.empty()) {
            //     Employee e = pq.top();
            //     cout << "Removing Employee " << e.getEmpName() << endl;
            //     pq.pop();
            // } else {
            //     cout << "Priority queue is empty." << endl;
            // }
        }

        void employeeWithHighestRating() {
            Employee emp = pq.top();
            cout << "Employee with highest rating - " << emp.getEmpName() << " with rating " << emp.getPerformanceRating() << endl;
        }

        void updatePerformanceRating(int empId, int updatedPerformanceRating) {
            // find in the queue
            priority_queue<Employee, vector<Employee>, CompareEmployee> temp;
            while(!pq.empty()) {
                Employee empFromPQ = pq.top();
                pq.pop();
                if(empFromPQ.getEmpId() == empId) {
                    //update performance rating
                    empFromPQ.updatePerformanceRating(updatedPerformanceRating);
                }
                temp.push(empFromPQ);
            }
            pq = temp;
        }

        void displayDetailsOfAllEmployees() {
            // find in the queue
            priority_queue<Employee, vector<Employee>, CompareEmployee> temp;
            while(!pq.empty()) {
                Employee empFromPQ = pq.top();
                pq.pop();
                empFromPQ.displayEmployeeDetails();
                temp.push(empFromPQ);
            }
            pq = temp;
        }

        bool isPqEmpty() {
            cout << "Size -> " << pq.size() << endl;
            return pq.empty();
        }

};

int main() {

    //create employees
    Employee e1("John", 1, 90);
    Employee e2("Alice", 2, 92);
    Employee e3("Bob", 3, 78);

    Employees emp;

    emp.addEmployee(e1);
    emp.addEmployee(e2);
    emp.addEmployee(e3);

    emp.employeeWithHighestRating();

    // update bob rating to 95
    emp.updatePerformanceRating(3, 95);

    emp.employeeWithHighestRating();


    // see details of all employees
    emp.displayDetailsOfAllEmployees();

    cout << emp.isPqEmpty() << endl; 



    emp.removeEmployeeWithHighestRating();

    emp.employeeWithHighestRating();

    return 0;
}
