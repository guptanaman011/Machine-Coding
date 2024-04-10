/*

Design and implement a task planner system 

A task has the following details : 
   - Title 
   - Creator 
   - Assignee (Optional) 
   - Status 
   - Type 
   - Due date 

A task can be of following types with additional information apart from what is mentioned above 
 - Feature : 
    - Feature summary 
    - Impact (Low, Moderate, High) 
 - Bug
    - Severity (P0, P1or P2)  
 - Story
    - Story Summary 
    - A story can have multiple SubTracks 
 - A SubTrack has the following details : 
    - Title 
    - Status 
    - A subtrack can be created and attached only to an existing story in non-completed status 

It should be easy to add a new task type to your application 

The status can change from a state to any state. 

Status field takes one of the following states depending on the task type : 
Feature => Open, In progress, Testing, Deployed 
Bug => Open, In progress, Fixed 
Story => Open, In Progress, Completed 

Sub-track status field takes one of these values Open, In Progress, Completed 

A sprint is defined as a collection of tasks used to track progress. You can add or remove a task from sprints. A task can be part of only one sprint at a time. 



Your task planner should have the following functionalities: 
Task
Create a task of any type 
Create sub-track 
Change the status of the task/sub-track
Change assignee of the task 
Display tasks assigned to a user categorised by task type
Sprint 
Create/Delete a Sprint 
Add/remove task to/from sprint
Display sprint snapshot. This should display the tasks that are part of the sprint and also display if they are delayed or on track 
Bonus Question (Only if time permits) :- 
The transition/change in the status should be based on allowed transitions eg :-
For task type feature, we might want to have only following allowed transitions : Open => In progress In progress => Testing Testing => Deployed In progress => Deployed 

The examples below are just to understand the functionalities and may not necessarily be used in the same format as input to your driver program. 

*/

#include <iostream>
#include<bits/stdc++.h>
using namespace std;

enum ImpactLevel {
    Low,
    Moderate,
    High
};

enum SeverityLevel {
    P0,
    P1,
    P2
};

enum TaskType {
    FeatureType,
    BugType,
    StoryType
};

enum TaskStatus {
    Open,
    InProgress,
    Testing,
    Deployed,
    Fixed,
    Completed
};

class Task {
    protected:
        string  title;
        string creator;
        string assignee; //optional
        TaskStatus status;
        TaskType type;
        string dueDate;

        void updateStatus(TaskStatus status) {
            this->status = status;
            cout << "Task of the status is changed to " << status << endl;
        }
        
        void checkAndUpdateStatus(vector<TaskStatus> allowedTransitions, TaskStatus newTaskStatus) {
            if(find(allowedTransitions.begin(), allowedTransitions.end(), newTaskStatus) != allowedTransitions.end()){
                updateStatus(newTaskStatus);
            } else {
                cout << "invalid status transitions for the task" << endl;
            }
        }
    
    public: 
        Task () {}
        Task(string title, string creator, TaskStatus status, TaskType type, string dueDate, string assignee = "") {
            this->title = title;
            this->creator = creator;
            this->status = status;
            this->type = type;
            this->dueDate = dueDate;
            this->assignee = assignee;
        }
        string getTitle() {
            return title;
        }
        void changeStatus(TaskStatus newTaskStatus) {
            if(type == FeatureType) {
                vector<TaskStatus> allowedTransitions = {Open, InProgress, Testing, Deployed};
                checkAndUpdateStatus(allowedTransitions, newTaskStatus);
            } else if(type == BugType) {
                vector<TaskStatus> allowedTransitions = {Open, InProgress, Fixed};
                checkAndUpdateStatus(allowedTransitions, newTaskStatus);
            } else if(type == StoryType){
                vector<TaskStatus> allowedTransitions = {Open, InProgress, Completed};
                checkAndUpdateStatus(allowedTransitions, newTaskStatus);
            } else {
                cout << "Invalid task type." << endl;
            } 
        }

        void changeAssignee(string assignee) {
            this->assignee = assignee;
            cout << "Assignee Changed to " << assignee << endl;
        }

        virtual void displayDetails() = 0;

};

class Feature : public Task {
    private:
        string featureSummary;
        ImpactLevel impact;
    public:
        Feature(string title, string creator, TaskStatus status, string dueDate, string featureSummary, ImpactLevel impact, string assignee = "") {
            this->title = title;
            this->creator = creator;
            this->status = status;
            this->dueDate = dueDate;
            this->featureSummary = featureSummary;
            this->impact = impact;
            this->assignee = assignee;
        }

        void displayDetails() override {
            cout << "Feature Task Details: " << endl;
            cout << "Title: " << title << endl;
            cout << "Creator: " << creator << endl;
            cout << "Assignee: " << assignee << endl;
            cout << "Status: " << status << endl;
            cout << "Type: Feature" << endl;
            cout << "Due Date: " << dueDate << endl;
            cout << "Feature Summary: " << featureSummary << endl;
            cout << "Impact: " << impact << endl;
        }  
};

class Bug : public Task {
    SeverityLevel severityLevel;
    public:
        Bug(string title, string creator, TaskStatus status, string dueDate, SeverityLevel severityLevel, string assignee = "") {
            this->title = title;
            this->creator = creator;
            this->status = status;
            this->dueDate = dueDate;
            this->assignee = assignee;
            this->severityLevel = severityLevel;
        }

        void displayDetails() override {
            cout << "Feature Task Details: " << endl;
            cout << "Title: " << title << endl;
            cout << "Creator: " << creator << endl;
            cout << "Assignee: " << assignee << endl;
            cout << "Status: " << status << endl;
            cout << "Type: Feature" << endl;
            cout << "Due Date: " << dueDate << endl;
            cout << "Severity Level: " << severityLevel << endl;
        }
};

class SubTrack  {
    string title;
    TaskStatus status;

        void updateStatus(TaskStatus status) {
            this->status = status;
            cout << "Task of the status is changed to " << status << endl;
        }

        void checkAndUpdateStatus(vector<TaskStatus> allowedTransitions, TaskStatus newTaskStatus) {
            if(find(allowedTransitions.begin(), allowedTransitions.end(), newTaskStatus) != allowedTransitions.end()){
                updateStatus(newTaskStatus);
            } else {
                cout << "invalid status transitions for the task" << endl;
            }
        }
        public:
        SubTrack(string title, TaskStatus status) {
            this->title = title;
            this->status = status;
        }
        void changeStatus(TaskStatus newTaskStatus) {
            vector<TaskStatus> allowedTransitions = {Open, InProgress, Completed};
            checkAndUpdateStatus(allowedTransitions, newTaskStatus);
        }
};

class Story : public Task {
    string shortSummary;
    vector<SubTrack> subtracks;
    public:
        Story(string title, string creator, TaskStatus status, string dueDate, string shortSummary, string assignee = "") {
            this->title = title;
            this->creator = creator;
            this->status = status;
            this->dueDate = dueDate;
            this->assignee = assignee;
            this->shortSummary = shortSummary;
        }

        void addSubTrack(SubTrack subtrack) {
            if(status != Completed){
                subtracks.push_back(subtrack);
                cout << "Subtrack added to the story" << endl;
            } else {
                cout << "Cannot add subtrack to a completed story" << endl;
            }
        }

        void displayDetails() override {
            cout << "Feature Task Details: " << endl;
            cout << "Title: " << title << endl;
            cout << "Creator: " << creator << endl;
            cout << "Assignee: " << assignee << endl;
            cout << "Status: " << status << endl;
            cout << "Type: Feature" << endl;
            cout << "Due Date: " << dueDate << endl;
        }

};



class Sprint {
    private:
        vector<Task*> tasks;

    public:

      Sprint(vector<Task*> &task) {
        this->tasks = task;
      }

    void removeTask(Task& task) {

        // find the index
        int index = -1;
        for(int i=0;i<tasks.size();i++) {
            if(task.getTitle() == tasks[i]->getTitle()) {
                index = i;
                break;
            }
        }
        if(index == -1) {
            cout << "Task not found in sprint " << endl; 
        } else {
            tasks.erase(tasks.begin() + index);
        }
      
    }

    void addTask(Task& task) {
        tasks.push_back(&task);
    }

    void displayAllTasks() {
        for(int i=0;i<tasks.size();i++) {
            tasks[i]->displayDetails();
            cout << endl;
        }
        
    }
};


int main() {
    Feature featureTask("New Feature", "John Doe", TaskStatus::Open, "2024-04-30", "Summary of Feature", ImpactLevel::High);
    Bug bugTask("Critical Bug", "Jane Doe", TaskStatus::Open, "2024-04-15", SeverityLevel::P0);
    Story storyTask("User Story", "John Smith", TaskStatus::Open, "2024-05-15", "Summary of Story");

    SubTrack subTrack("SubTrack 1", TaskStatus::Open);

    storyTask.addSubTrack(subTrack);

    vector<Task*> tasks = {&featureTask, &bugTask, &storyTask};

    Sprint sprint(tasks);

    sprint.displayAllTasks();


    featureTask.changeStatus(InProgress);
    featureTask.displayDetails();


    Feature featureTask2("New Feature2", "NAMAN", TaskStatus::Open, "2024-04-30", "Summary of Feature", ImpactLevel::High);

    sprint.addTask(featureTask2);

    sprint.displayAllTasks();


    cout << "Thanks!" << endl;
    return 0;
}