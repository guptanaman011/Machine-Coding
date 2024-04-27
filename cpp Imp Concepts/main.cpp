/*
 - If you want to search anything always think of hashMaps if they can be used
 - used priority queue if you want smallest and greatest element everytime with sorting
 - If you want to track the oldest one then use dequeue remove front if you want to remove oldest and push new from back
*/

// IMPLEMENTATION OF PRIORITY QUEUEU

#include <queue>
#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>

using namespace std;


class Student {
    string stuName;
    int marks;
    public:
        Student(string stuName, int marks) {
            this->stuName = stuName;
            this->marks = marks;
        }
        string getStuName() {
            return stuName;
        }
        int getMarks() {
            return marks;
        }

        bool operator< (const Student &other) const {
            return marks < other.marks;
        }
};

//return student object with highest marks
Student getTopper(vector<Student> &students) {
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end());

    // Return the student with the highest marks (the last element after sorting)
    return sortedStudents.back();
}

int main() {
    priority_queue<int> pq;   //max Heap  
    pq.push(10);
    pq.push(30);
    pq.push(20);
    
    cout << pq.top() << endl;

    priority_queue<int, vector<int>, greater<int>> pq1; //min heap ->  or you can you max heap and * by -1
    pq1.push(10);
    pq1.push(30);
    pq1.push(20);

    cout << pq1.top() << endl;


    // Custom sort 
    // - object attribute level
    Student s1("Naman", 30);
    Student s2("Aastha", 40);
    Student s3("Nipun", 50);
    Student s4("Raj", 60);

    vector<Student> students = {s1,s2,s3,s4};

    Student topper = getTopper(students);

    cout << "The topper is: " << topper.getStuName() << " with marks: " << topper.getMarks() << endl; 



    // array of array sorting

    vector<int> arr1 = {1, 2, 4};
    vector<int> arr2 = {1, 1, 1};
    vector<int> arr3 = {1, 2, 3};

    // Create a vector of indices to track the order
    vector<int> indices(arr1.size());
    iota(indices.begin(), indices.end(), 0);

    // Sort indices based on values in arr1
    sort(indices.begin(), indices.end(), [&](int i, int j) {
        return arr1[i] < arr1[j];
    });

    // Sort all arrays based on the sorted indices
    vector<vector<int>> allArrays = {arr1, arr2, arr3};
    for (auto &arr : allArrays) {
        vector<int> sortedArr(arr.size());
        transform(indices.begin(), indices.end(), sortedArr.begin(), [&](int index) {
            return arr[index];
        });
        arr = sortedArr;
    }

    // Print the sorted arrays
    for (const auto &arr : allArrays) {
        for (int num : arr) {
            cout << num << " ";
        }
        cout << endl;
    }

    
    return 0;
}



/*

#include <chrono>
 #include <ctime>
 #include <thread>

 `
auto now = chrono::system_clock::now();
            // Convert the system time to a time_t object
            time_t currentTime = chrono::system_clock::to_time_t(now);
            long endTime = static_cast<long>(currentTime);

*/



/*

HOW TO USE PRIORITY QUEUES WITH POINTERS

#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct comapare {
    bool operator()(const char* a, const char *b) const {
        return *a < *b;
    }
};

int main() {
    map<int, char*> mp;
    priority_queue<char*, vector<char*>, comapare> pq;

    char c1 = 'a';
    char c2 = 'b';


    mp.insert({1, &c1});
    mp.insert({2, &c2});

    pq.push(&c1);
    pq.push(&c2);




    cout << *pq.top() << endl;
    cout << *mp[2] << endl;

    // changing the value of c2;

    cout << "After changing the value of c1 and c2" << endl;

    c2 = 'z';
    c1 = 'x';

    cout << *pq.top() << endl;
    cout << *mp[2] << endl;

    return 0;
}




DEAL WITH OBJECTS

#include <iostream>
#include <queue>

using namespace std;

class MyClass {
public:
    int value;

    MyClass(int val) : value(val) {}

    // Custom comparator function for comparing MyClass objects
    static bool Compare(const MyClass* a, const MyClass* b) {
        return a->value < b->value;
    }
};

int main() {
    priority_queue<MyClass*, vector<MyClass*>, bool(*)(const MyClass*, const MyClass*)> pq(MyClass::Compare);

    MyClass obj1(10);
    MyClass obj2(5);
    MyClass obj3(20);

    pq.push(&obj1);
    pq.push(&obj2);
    pq.push(&obj3);

    while (!pq.empty()) {
        cout << pq.top()->value << " ";
        pq.pop();
    }

    return 0;
}


*/