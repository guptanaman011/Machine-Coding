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
#include <unordered_map>

using namespace std;

class Employee {
private:
    int id;
    string name;
    int performanceRating;

public:
    Employee(int id, string name, int performanceRating) {
        this->id = id;
        this->name = name;
        this->performanceRating = performanceRating;
    }

    // getter methods
    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    int getPerformanceRating() const {
        return performanceRating;
    }

    void updatePerformanceRating(int performanceRating) {
        this->performanceRating = performanceRating;
        cout << "Employee with id " << id << "'s rating updated to " << performanceRating << endl;
    }

    void displayDetails() const {
        cout << "ID - " << id << " Name - " << name << " Performance Rating - " << performanceRating << endl;
    }
};

class Employees {
private:
    struct CompareEmployees {
        bool operator()(const Employee* emp1, const Employee* emp2) const {
            return emp1->getPerformanceRating() < emp2->getPerformanceRating();
        }
    };
    priority_queue<Employee*, vector<Employee*>, CompareEmployees> pq;
    unordered_map<int, Employee*> mp;

public:
    void addEmployee(Employee& employee) {
        Employee* emp = new Employee(employee);
        pq.push(emp);
        mp.insert({emp->getId(), emp});
    }

    void updatePerformanceRating(int empId, int updatedRating) {
        if (mp.find(empId) != mp.end()) {
            mp[empId]->updatePerformanceRating(updatedRating);
        } else {
            cout << "Employee with ID " << empId << " not found." << endl;
        }
    }

    void displayEmployeeWithHighestRating() const {
        if (!pq.empty()) {
            cout << "Employee with highest rating - ";
            pq.top()->displayDetails();
        }
    }

    void displayAllEmployees() const {
        priority_queue<Employee*, vector<Employee*>, CompareEmployees> tempPQ = pq;
        while (!tempPQ.empty()) {
            tempPQ.top()->displayDetails();
            tempPQ.pop();
        }
    }
};

int main() {
    Employee e1(1, "John", 90);
    Employee e2(2, "Alice", 92);
    Employee e3(3, "Bob", 78);

    Employees emp;

    emp.addEmployee(e1);
    emp.addEmployee(e2);
    emp.addEmployee(e3);

    emp.displayEmployeeWithHighestRating();

    emp.updatePerformanceRating(3, 95);

    emp.displayAllEmployees();

    emp.displayEmployeeWithHighestRating();

    return 0;
}


//  Cannot use MAP