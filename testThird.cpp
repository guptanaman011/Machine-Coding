 /*
 Requirements
    - Multilevel Parking lot
    - Multiple category of parking space
    - Multiple entry and exit (adds an interesting case of concurrency)
    - Should not allow more vehicles than allocated space for each category
    - Charge should be hourly basis
    - Display each number of parking for each category at entry itself
 */
#include <iostream>
#include <map>

using namespace std;

enum ParkingSlotType {
    TwoWheeler,
    Compact,
    Medium,
    Large
};

enum VehicleCategory {
    Bike,
    HatchBack,
    Sedan,
    SUV,
    Bus
};

class Vehicle {
    private:
        string vehicleNumber;
        VehicleCategory vehicleCategory;
    public:
        Vehicle() {};
        Vehicle(string vehicleNumber, VehicleCategory vehicleCategory) {
            this->vehicleNumber = vehicleNumber;
            this->vehicleCategory = vehicleCategory;
        }
        // getter methods
        string getVehicleNumber() {
            return vehicleNumber;
        }

        VehicleCategory getVehicleCategory() {
            return vehicleCategory;
        }
};

class ParkingSlot {
    private:
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

        // getter methods
        string getName() {
            return name;
        }

        bool isParkingAvailable() {
            return isAvailable;
        }

        ParkingSlotType getParkingSlotType() {
            return parkingSlotType;
        }

        void addVehicle(Vehicle& vehicle) {
            this->vehicle = vehicle;
            isAvailable = false;
        }   

        void removeVehicle() {
            this->vehicle = Vehicle();
            isAvailable = true;
        }
};


// parkingFloor can have multiple parking slots 
class ParkingFloor {
    private:
        string name;
        unordered_map<ParkingSlotType, unordered_map<string, ParkingSlot>> parkingSlots;
        ParkingSlotType getCorrectSlot(VehicleCategory vehicleCategory) {
            if(vehicleCategory == Bike) {
                return TwoWheeler;
            } else if(vehicleCategory == HatchBack) {
                return Compact;
            } else if(vehicleCategory == Sedan || vehicleCategory == SUV) {
                return Medium;
            } else {
                return Large;
            }
        }

    public:
        ParkingFloor(string name, unordered_map<ParkingSlotType, unordered_map<string, ParkingSlot>>& parkingSlots) {
            this->name = name;
            this->parkingSlots = parkingSlots;
        }

        ParkingSlot getRelevantParkingSlot(Vehicle vehicle) {
            VehicleCategory vehicleCategory = vehicle.getVehicleCategory();
            ParkingSlotType parkingSlot = getCorrectSlot(vehicleCategory);
            map<string, ParkingSlot> revelantParkingSlots = parkingSlots[parkingSlot];
            for(auto &it: revelantParkingSlots) {
                if(it.second.getParkingSlotType()) {
                    it.second.addVehicle(vehicle);
                    return it.second;
                }
            }
            cout << "Parking not available" << endl;
            return ParkingSlot("", TwoWheeler);
        }
};


// parking lot can have multiple parkingFloors
class ParkingLot {
    private:
        
};


int main() {
    return 0;
}