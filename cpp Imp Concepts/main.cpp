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