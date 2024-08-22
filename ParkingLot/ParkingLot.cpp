/*
    Multi-Level Parking system

    The parking lot should have multiple levels, each level with a certain number of parking spots.
    The parking lot should support different types of vehicles, such as cars, motorcycles, and trucks.
    Each parking spot should be able to accommodate a specific type of vehicle.
    The system should assign a parking spot to a vehicle upon entry and release it when the vehicle exits.
    The system should track the availability of parking spots and provide real-time information to customers.
    The system should handle multiple entry and exit points and support concurrent access.
*/



#include<bits/stdc++.h>
using namespace std;

enum VehicleType{
    CAR,
    TRUCK,
    MOTORCYCLE,
};

class Vehicle {
    private:
        string numberPlate;
        VehicleType type;

    public:
        Vehicle (string numberPlate, VehicleType type) {
            this -> numberPlate = numberPlate;
            this -> type = type;
        }

        bool isSameType(Vehicle vehicle) {
            if(this -> type == vehicle.type) {
                return true;
            }
            return false;
        }

        VehicleType getType(){
            return this -> type;
        }

        string getNumberPlate() {
            return numberPlate;
        }
};

class ParkingSpot {
    private:
        int spotNumber;
        VehicleType allowedVehicle;
        Vehicle *parkedVehicle;


    public:
        ParkingSpot (int spotNum) {
            this -> spotNumber = spotNum;
            allowedVehicle = CAR;
            parkedVehicle = NULL;
        }

        bool parkVehicle(Vehicle vehicle) {
            if(isAvailable() && allowedVehicle == vehicle.getType()) {
                parkedVehicle = &vehicle;
                return true;
            }

            return false;
        }

        bool unparkVehicle (Vehicle vehicle) {
            if(parkedVehicle == NULL || parkedVehicle -> getNumberPlate() != vehicle.getNumberPlate()) {
                return false;
            }

            parkedVehicle = NULL;
            return true;
        }

        bool isAvailable(){
            return parkedVehicle == NULL;
        }

        int getSpotNumber(){
            return this -> spotNumber;
        }
};

class Level {
    private:
        int floor;
        vector<ParkingSpot> parkingSpots;

    public:
        Level (int floor, int numSpots) {
            this -> floor = floor;
            this -> parkingSpots.reserve(numSpots);

            for(int i = 0; i < numSpots; i++) {
                parkingSpots.emplace_back(i);
            }
        }

        bool parkVehicle(Vehicle vehicle) {
            for(auto &spot: parkingSpots) {
                if(spot.parkVehicle(vehicle)) {
                    return true;
                }
            }
            return false;
        }

        bool unparkVehicle(Vehicle vehicle) {
            for(auto &spot: parkingSpots) {
                if(spot.unparkVehicle(vehicle)) {
                    return true;
                }
            }
            return false;
        }

        int getFloor() {
            return floor;
        }

        void displayAvailability() {
            cout << "FLOOR NUMBER " << this -> getFloor() << endl;

            for(auto spot: parkingSpots) {
                string ans = to_string(spot.getSpotNumber()) + " -> " + (spot.isAvailable() ? "Available" : "Occupied");
                cout << ans << endl;
            }
        }
};


class ParkingLot {
    private:
        // Different level of the parking system
        vector<Level> levels;

        // Desfault constructor
        ParkingLot () {
            levels = vector<Level>();
        }

        // Deleted the copy constructor and = operator to ensure single instance of the class
        // according to singleton principle.
        ParkingLot (const ParkingLot&) = delete;
        ParkingLot& operator=(const ParkingLot&) = delete;

        static std::mutex mtx;


    public:
        static ParkingLot& getInstance() {
            //Only one instance of the parkinglot class.
            static ParkingLot instance;

            return instance;
        }

        void addLevel(int floor, int numSpots) {
            lock_guard<mutex> lock(mtx);

            levels.emplace_back(floor, numSpots);
        }

        bool parkVehicle(Vehicle vehicle) {
            lock_guard<mutex> lock(mtx);

            for(auto &level: levels) {
                if(level.parkVehicle(vehicle)) { 
                    return true;
                }
            }

            return false;
        }

        bool unparkVehicle (Vehicle vehicle) {
            lock_guard<mutex> lock(mtx);

            for(auto &level: levels) {
                if(level.unparkVehicle(vehicle)) 
                    return true;
            }

            return false;
        }

        void displayAvailability() {
            lock_guard<mutex> lock(mtx);

            for(auto level: levels) {
                level.displayAvailability();
                cout << endl;
            }
        }
};

std::mutex ParkingLot::mtx;

void multipleEntryExitPoints(ParkingLot& myParkingLot) {
    myParkingLot.addLevel(1, 10);
    myParkingLot.addLevel(2, 10);

    Vehicle car = Vehicle("ABC123", CAR);
    Vehicle car1 = Vehicle("ABC124", CAR);
    Vehicle car2 = Vehicle("ABC125", CAR);
    Vehicle car3 = Vehicle("ABC126", CAR);

    Vehicle truck = Vehicle("XYZ789", TRUCK);
    Vehicle motorcycle = Vehicle("M1234", MOTORCYCLE);

    myParkingLot.parkVehicle(car);
    myParkingLot.parkVehicle(car1);
    myParkingLot.parkVehicle(car2);
    myParkingLot.parkVehicle(car3);

    myParkingLot.parkVehicle(truck);
    myParkingLot.parkVehicle(motorcycle);

    myParkingLot.displayAvailability();

    myParkingLot.unparkVehicle(car);
    myParkingLot.unparkVehicle(car1);
    myParkingLot.unparkVehicle(car1);

    myParkingLot.displayAvailability();
}

int main() {
    ParkingLot& parkingLot1 = ParkingLot::getInstance();
    ParkingLot& parkingLot2 = ParkingLot::getInstance();

    thread t1(multipleEntryExitPoints, ref(parkingLot1));
    thread t2(multipleEntryExitPoints, ref(parkingLot2));

    t1.join();
    t2.join();

    return 0;
}
