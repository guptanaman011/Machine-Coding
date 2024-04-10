/*
Build a cache management system
CACHE MANAGEMENT SYSTEM

Your objective is to design a software cache management system (cms), which should
adhere to the following properties:
    1. The system should have multiple levels of cache storage. The number of levels
        should be configurable.
    2. The data maintained in the system will be in the form of a (key, value) pair of
        strings.
    3. Each level of cache will have a pre-specified constant CAPACITY, READ_TIME
        and WRITE_TIME. Any read operation for the corresponding cache will incur
        READ_TIME delay and any write operation for the corresponding cache will incur
        WRITE_TIME delay.
    4. The cache levels will be chained (e.g. L1 -> L2 -> L3 ...). The data stored at any
        level will be a subset of data stored at the next level.
    5. The system should support following operations:

    ● READ <Key> : Prints the value stored corresponding to the key and read
    time
    ● WRITE <Key> <Value> : Stores the (key, value) pair and prints the write
    time

    7. A data read operation is performed as below:
        a. The cms will start reading the caches starting with the lowest level and
            proceed towards next level if key is not found at current level. As soon as
            it finds the key, it should fetch the value from the cache and propagate
            backwards writing the same data at all the lower level caches. If the lower
            level cache is already full, it will rewrite the new data over the oldest data
            in the cache. 
    8. A data write operation is performed as below:
        a. The cms will first read the cache for existing duplicate data(having same key-value pair) starting with
            the lowest level. If it is already present, it should not overwrite the data.
            Otherwise, it should write the new data into the cache and proceed to the
            next level. If the cache level is full, it will purge the oldest data (or based
            on some other replacement policy) in the cache level before writing the
            new data.


Sample input:
    5 // Number of cache levels
    
    10 15 20 25 30 // Cache size of each level
    1 2 3 4 5 // READ time of each level
    2 4 6 8 10 // WRITE time of each level

    WRITE “abc” “def” // Should print “Write time: 45”
    WRITE “ghi” “jkl” // Should print “Write time: 45”
    READ “abc” // Should print “Value at abc is def”
    “Read time: 1”
    // Bonus Points:
    STATS // Should print “Usage: 2 / 10 , 2 / 15 , 2 / 20 , 2 / 25 , 2 / 30”
    “Avg Read Time: 1”
    “Avg Write Time: 45”
    Bonus Points:
    The system should be able to provide statistics in the following manner:
    A: STATS : Should print cache capacity details ( Filled / Total ) of each level and
    average read and write times of last 10 operations.
    Extension cases: Data type, Replacement Policy etc.


*/



#include <iostream>
#include <map>
#include <bits/stdc++.h>
#include <deque>
using namespace std;

struct CacheEntry {
    string key;
    string value;
};

class CacheLevels {
    private:
        int capacity;
        int readTime;
        int writeTime;
        deque<CacheEntry> cache; // Queue for keeping the track of the last entry
        map <string, string> mp;

    public: 
        CacheLevels(int capacity, int readTime, int writeTime) {
            this->capacity = capacity;
            this->readTime = readTime;
            this-> writeTime = writeTime;
        }

        pair<string, int> read(string key) {
            pair<string, int> result;
            result.second = readTime;
            if(mp.find(key) != mp.end()) {
                result.first = mp[key];
            }

            cout << "Key not found in cache" << endl;
            result.first = "";
            return result;
        }   

        bool search(string key, int& totalTime) {
            totalTime += readTime;

            for(auto& it: cache) {
                if(it.key == key) {
                    return true;
                }
            }

            return false;
        }

        void write(string key, string value, int& totalTime) {
            // find key if already present
            if(mp.find(key) != mp.end()){
                //key already present
                return;
            }
            if(cache.size() >= capacity) {
                // if cache is full then remove the oldest one
                cache.pop_front();
            }
            CacheEntry cacheEntry;
            cacheEntry.key = key;
            cacheEntry.value = value;
            cache.push_back(cacheEntry);
            //insert the value in map
            mp[key] = value;
            totalTime += writeTime;            
        }

        void printStats() {
            cout << "Usage -> " << cache.size() << "/"  << capacity << endl; 
        }
};

class CacheManagementSystem {
    private: 
        vector<CacheLevels> levels;
        vector<int> last10ReadOperationsTime;
        vector<int> last10WriteOperationsTime;
    public: 
        CacheManagementSystem(vector<int> capacities, vector<int> readTimes, vector<int> writeTimes){
            for(int i=0;i<capacities.size();i++) {
                CacheLevels cp(capacities[i], readTimes[i], writeTimes[i]);
                levels.emplace_back(cp);
            }
        }

        void write(string key, string value) {
            int totalTimeTaken = 0; 
            // first search
            bool isPresent = false;
            for(auto& level: levels) {
                level.search(key, totalTimeTaken);
            }

            if(!isPresent) {
                for(auto& level: levels) {
                    level.write(key, value, totalTimeTaken);
                }
            }
            
            cout << "Write time: " << totalTimeTaken << endl;
            if(last10WriteOperationsTime.size() >= 10) {
                last10WriteOperationsTime.erase(last10WriteOperationsTime.begin());
            }
            last10WriteOperationsTime.push_back(totalTimeTaken);
        }

        void read(string key) {
            int totalTimeTaken = 0; 
            pair<string, int> result;
            for(auto level: levels) {
                result = level.read(key);
                if(result.first != ""){
                    break;
                }
            }
            cout << "Value of " << key << " is " << result.first << endl;
            cout << "Time Taken " << result.second << endl;

            if(last10ReadOperationsTime.size() >= 10) {
                last10ReadOperationsTime.erase(last10ReadOperationsTime.begin());
            }
            last10ReadOperationsTime.push_back(result.second);
        }

        void printStats() {
            for(auto level: levels){
                level.printStats();
            }
        }

        void getAverageReadAndWriteTime() {
            int readSum = 0, writeSum = 0;
            for(auto& it: last10WriteOperationsTime){
                writeSum+=it;
            }
            for(auto& it: last10ReadOperationsTime){
                readSum+=it;
            }
            cout << "AVG Write Time " << writeSum/last10WriteOperationsTime.size() << endl;
            cout << "AVG Read Time " << readSum/last10ReadOperationsTime.size() << endl;
        }

};


int main() {

    int levels = 5;

    vector<int> capacities;
    capacities.push_back(10);
    capacities.push_back(15);
    capacities.push_back(20);
    capacities.push_back(25);
    capacities.push_back(30);

    vector<int> readTimes;
    readTimes.push_back(1);
    readTimes.push_back(2);
    readTimes.push_back(3);
    readTimes.push_back(4);
    readTimes.push_back(5);

    vector<int> writeTimes;
    writeTimes.push_back(2);
    writeTimes.push_back(4);
    writeTimes.push_back(6);
    writeTimes.push_back(8);
    writeTimes.push_back(10);

    CacheManagementSystem cms(capacities, readTimes, writeTimes);

    cms.write("abc", "def");

    cms.write("ghi", "jkl");


    cms.read("abc");

    cms.printStats();

    cms.getAverageReadAndWriteTime();

    return 0;
}