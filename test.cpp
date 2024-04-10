// Online C++ compiler to run C++ program online
#include <iostream>
#include<bits/stdc++.h>
using namespace std;


 class Task {
        protected:
            string title;
        public:
            Task() {}
            Task(string title) {
                this->title = title;
            } 

            virtual void display() = 0;
    };

    class Feature : public Task {
        string featureSummary;
        public:
            Feature(string title, string featureSummary) {
                this->title = title;
                this->featureSummary = featureSummary;
            }

            void display() override {
                cout << "Title: " << title << endl;
                cout << "feature Summary" << featureSummary << endl;
            }
    };

    class Bug : public Task {
        string bugSummary;
        public:
            Bug(string title, string bugSummary) {
                this->title = title;
                this->bugSummary = bugSummary;
            }

            void display() override {
                cout << "Title: " << title << endl;
                cout << "feature Summary" << bugSummary << endl;
            }
    };

    class Story : public Task {
        string storySummary;
        public:
            Story(string title, string storySummary) {
                this->title = title;
                this->storySummary = storySummary;
            } 

            void display() override {
                cout << "Title: " << title << endl;
                cout << "feature Summary" << storySummary << endl;
            }
    };

    class Sprint {
        vector<Task*> tasks;

        public:
            Sprint(vector<Task*>& tasks) {
                this->tasks = tasks;
            }

            void displayAll() {
                for(int i=0;i<tasks.size();i++){
                    tasks[i]->display();
                }
            }
    };



int main() {
    Feature feature("Feature Tile", "Feature Summary");
    Story story("story Tile", "story Summary");
    Bug bug("bug Tile", "bug Summary");

    vector<Task*> tasks = {&feature, &story, &bug};
    Sprint sprint(tasks);

    sprint.displayAll();
   
    cout << "Completed " << endl;
    return 0;
}