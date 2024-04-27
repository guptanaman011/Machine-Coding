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
#include <bits/stdc++.h>
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

class Sprint {
    private:
        vector<Task> tasks;
    public:
        void addTask() {

        }
        void removeTask() {

        }
        void displayAllTasks() {

        }
};

class Task: public Sprint {
    protected:
        string title;
        string creator;
        string assignee;
        TaskStatus status;
        TaskType type;
        string dueDate;
    public:
        Task() {}
        Task(string title, string creator, string assignee="", TaskStatus status, TaskType type, string dueDate) {
            this->title = title;
            this->creator = creator;
            this->assignee = assignee;
            this->status = status;
            this->type = type;
            this->dueDate = dueDate;
        }

};

class Feature: public Task {
    private:
        string featureSummary;
        ImpactLevel impactLevel;
    public:
        Feature() {}
        Feature(string title, string creator, string assignee="", TaskStatus status, TaskType type, string dueDate, string featureSummary, ImpactLevel impactLevel){
            this->title = title;
            this->creator = creator;
            this->assignee = assignee;
            this->status = status;
            this->type = type;
            this->dueDate = dueDate;
            this->featureSummary = featureSummary;
            this->impactLevel = impactLevel;
        }




};

class Bug: public Task  {
    private:
        SeverityLevel severity;
    public:

};

class SubTrack {
    private:
        string title;
        TaskStatus status;
    public:
    
};
class Story: public Task  {
    private:

    public:
};


int main() {
    // create a task of all the three types
    Feature featureTask("Enable Invoice Download Button", "Naman", "Aastha", Open, FeatureType, "20-04-2024", "Enable the invoice download button for the publishers", Moderate);

    return 0;
}