    /*
    Requirements
        - Multilevel Parking lot
        - Multiple category of parking space
        - Multiple entry and exit (adds an interesting case of concurrency)
        - Should not allow more vehicles than allocated space for each category
        - Charge should be hourly basis
        - Display each number of parking for each category at entry itself
    */

 #include<iostream>
 #include <bits/stdc++.h>
 #include <map>
 #include <chrono>
 #include <ctime>
 #include <thread>

 
using namespace std;

class Address {
    public:
        string city;
        string state;
        string country;
};

enum ParkingSlotType {
    TwoWheeler,
    Compact,
    Medium,
    Large
};

enum VehicleCategory {
    Bike,
    Hatchback,
    Sedan,
    SUV,
    Bus
};

class Vehicle {
    string vehicleNumber;
    VehicleCategory vehicleCategory;
    public:
        Vehicle() {}
        Vehicle(string vehicleNumber, VehicleCategory vehicleCategory) {
            this->vehicleNumber = vehicleNumber;
            this->vehicleCategory = vehicleCategory;
        }
        VehicleCategory getVehicleCategory(){
            return vehicleCategory;
        }
        string getVehicleNumber() {
            return vehicleNumber;
        }
};

class ParkingSlot {
    string name;
    bool isAvailable;
    Vehicle vehicle;
    ParkingSlotType parkingSlotType;

    public:
        ParkingSlot() {}
        ParkingSlot(string name, ParkingSlotType parkingSlotType) {
            this->name = name;
            this->parkingSlotType = parkingSlotType;
            isAvailable = true;
        }

        string getName() {
            return name;
        }

        bool isSlotAvailable() {
            return isAvailable;
        }
        void addVehicle(Vehicle vehicle) {
            this->vehicle = vehicle;
            isAvailable = false;
        }

        void removeVehicle() {
            this->vehicle = Vehicle();
            isAvailable = true;
        }
        ParkingSlotType getParkingSlotType() {
            return parkingSlotType;
        }
};

class ParkingFloor {
    string name;
    map<ParkingSlotType, map<string, ParkingSlot>> parkingSlots;

    ParkingSlotType getCorrectSlot(VehicleCategory vehicleCategory) {
        if(vehicleCategory == Bike) {
            return TwoWheeler;
        } else if(vehicleCategory == Hatchback) {
            return Compact;
        } else if (vehicleCategory == Sedan || vehicleCategory == SUV) {
            return Medium;
        } else if(vehicleCategory == Bus) {
            return Large;
        } 
        //choosen TWOWHEELER AS DEFAULT FOR NOW
        return TwoWheeler;
    }

    public:
        ParkingFloor() {}
        ParkingFloor(string name, map<ParkingSlotType, map<string, ParkingSlot>> &parkingSlots) {
            this->name = name;
            this->parkingSlots = parkingSlots;
        }

        ParkingSlot getRelevantSlotForVehicleAndPark(Vehicle vehicle) {
            VehicleCategory vehicleCategory = vehicle.getVehicleCategory();
            ParkingSlotType parkingSlotType = getCorrectSlot(vehicleCategory);
            map<string, ParkingSlot> revelantParkingSlot = parkingSlots[parkingSlotType];

            for(auto &it: revelantParkingSlot) {
                if(it.second.isSlotAvailable()) {
                    it.second.addVehicle(vehicle);
                    return it.second;
                }
            }
            cout << "Parkng not available " << endl;
            // Return a default-constructed ParkingSlot object if no slot is available
            return ParkingSlot("", ParkingSlotType::TwoWheeler);
        }

        // Add equality comparison operator for ParkingFloor
        bool operator==(const ParkingFloor& other) const {
            return this->name == other.name;
        }
};

class Ticket {
    string ticketNumber;
    long startTime;
    long endTime;
    Vehicle vehicle;
    ParkingSlot parkingSlot;

    public:
        Ticket() {};
        void createTicketForSlot(ParkingSlot parkingSlot, Vehicle vehicle) {

            // Get the current system time
            auto now = chrono::system_clock::now();
            // Convert the system time to a time_t object
            time_t currentTime = chrono::system_clock::to_time_t(now);


            this->parkingSlot = parkingSlot;
            this->vehicle = vehicle;
            startTime = static_cast<long>(currentTime);
            cout << "StartTime from start" << startTime << endl;
            ticketNumber = vehicle.getVehicleNumber() + "-001";
        }

        string getTicketNumber() {
            return ticketNumber;
        }

        long getStartTime() {
            return startTime;
        }

        ParkingSlot getParkingSlot() {
            return parkingSlot;
        }

};


class ParkingLot {
    private: 
        string nameOfParkingLot;
        Address address;
        vector<ParkingFloor> parkingFloors;
        map<ParkingSlotType, double> VehicleTypePricing;

    public:
        ParkingLot(string nameOfParkingLot, Address address, vector<ParkingFloor> parkingFloors, map<ParkingSlotType, double> VehicleTypePricing){
            this->nameOfParkingLot = nameOfParkingLot;
            this->address = address;
            this->parkingFloors = parkingFloors;
            this->VehicleTypePricing = VehicleTypePricing;
        }

        void addFloors(string name,  map<ParkingSlotType, map<string, ParkingSlot>> parkingSlot) {
            ParkingFloor p1(name, parkingSlot);
            parkingFloors.push_back(p1);
        }

        void removeFloors(ParkingFloor parkingFloor) {
            auto it = find(parkingFloors.begin(), parkingFloors.end(), parkingFloor);
            if(it != parkingFloors.end()){
                parkingFloors.erase(it);
            }
        }

        Ticket assignTicket(Vehicle vehicle) {
            // serach on the first floor
            // search for floors
            ParkingSlot parkingSlot;
            for(int i=0;i<parkingFloors.size();i++) {
                parkingSlot = parkingFloors[i].getRelevantSlotForVehicleAndPark(vehicle);
                if(parkingSlot.getName() != "") {
                    //we got the parking
                    break;
                }
            }
            if(parkingSlot.getName() == ""){
                cout << "Sorry, No parking is available at the moment." << endl;
                return Ticket();
            }
            Ticket ticket = Ticket();
            ticket.createTicketForSlot(parkingSlot, vehicle);

            cout << "After creating ticket get ticket number ---->>>> " << ticket.getTicketNumber() << endl;
            return ticket;
        }

        double scanAndPay(Ticket ticket) {
            auto now2 = chrono::system_clock::now();
            // Convert the system time to a time_t object
            time_t currentTime2 = chrono::system_clock::to_time_t(now2);
            long endTime = static_cast<long>(currentTime2);

            // Convert start and end times to seconds
            long startTimeSeconds = ticket.getStartTime();

            cout << "EndTime " << endTime << endl;
            cout << "StartTime " << startTimeSeconds << endl;
            double durationSeconds = endTime - startTimeSeconds; // Calculate the duration in seconds
            cout << "Duration in Seconds: " << durationSeconds << endl;
            double durationHours = durationSeconds / 3600; // Convert seconds to hours

            cout << "Duration in hours: " << durationHours << endl;

            ParkingSlotType parkingDebug = ticket.getParkingSlot().getParkingSlotType();

            ParkingSlot parkingSlot123 = ticket.getParkingSlot();

            double price = durationHours * VehicleTypePricing[ticket.getParkingSlot().getParkingSlotType()];
            price = round(price);

            cout << "PRICE: " << price << endl;
            return price;
        }

};

// Function to sleep for a specified duration in milliseconds
void sleep_ms(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

 int main() {
    string nameOfparkingLot = "Naman parking Lot";
    Address address = Address();
    address.city = "Jaipur";
    address.country = "India";
    address.state = "Rajasthan"; 

    map<ParkingSlotType, map<string, ParkingSlot>> allSlots;

    // create parking slot type
    ParkingSlot p1("c1", Compact);
    ParkingSlot p2("c2", Compact);
    ParkingSlot p3("c3", Compact);

    ParkingSlot p4("l1", Large);
    ParkingSlot p5("l2", Large);
    ParkingSlot p6("l3", Large);

    
    map<string, ParkingSlot> compactSlots;

    compactSlots["c1"] = p1;
    compactSlots["c2"] = p2;
    compactSlots["c3"] = p3;

    map<string, ParkingSlot> largeSlots;

    largeSlots["l1"] = p4;
    largeSlots["l2"] = p5;
    largeSlots["l3"] = p6;

    allSlots[Compact] = compactSlots;
    allSlots[Large] = largeSlots;

    // create parking floor
    ParkingFloor floor("1", allSlots);

    vector<ParkingFloor> parkingFloors;
    parkingFloors.push_back(floor);

    map<ParkingSlotType, double> VehicleTypePricing;

    VehicleTypePricing[TwoWheeler] = 100;
    VehicleTypePricing[Compact] = 3600;
    VehicleTypePricing[Medium] = 300;
    VehicleTypePricing[Large] = 400;
    // create main instance
    ParkingLot parking(nameOfparkingLot, address, parkingFloors, VehicleTypePricing);

    Vehicle v1("RJ-14-AC-9816", Hatchback);

    Ticket ticket = parking.assignTicket(v1);

    cout << "Ticket is assigned -> " << ticket.getTicketNumber() << endl;

    cout << "Sleeping for 1 seconds " << endl;

    sleep_ms(1000);

    cout << "Woke up after 1 seconds " << endl;

    double price = parking.scanAndPay(ticket);

    cout << "Total Price -> Rs" << price << endl;
    cout << "Thank you for visiting. " << endl;
 
    return 0;
 }
