
#include <iostream>
#include <vector>
#include <memory>
#include <string>
using namespace std;

// 1. Different types of vehicles
enum class VehicleType {
    CAR,
    BIKE
};

// 2. Base class for all vehicles
class Vehicle {
protected:
    string registrationNumber;

public:
    Vehicle(string number) : registrationNumber(number) {}

    virtual VehicleType getType() const = 0;

    string getRegistrationNumber() const {
        return registrationNumber;
    }

    virtual ~Vehicle() = default;
};

// 3. Car is a type of Vehicle
class Car : public Vehicle {
public:
    Car(string number) : Vehicle(number) {}

    VehicleType getType() const override {
        return VehicleType::CAR;
    }
};

// 4. Bike is a type of Vehicle
class Bike : public Vehicle {
public:
    Bike(string number) : Vehicle(number) {}

    VehicleType getType() const override {
        return VehicleType::BIKE;
    }
};

// 5. Base class for all parking spots
class ParkingSpot {
protected:
    int spotId;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int id)
        : spotId(id), parkedVehicle(nullptr) {}

    virtual bool canFit(const Vehicle& vehicle) const = 0;

    bool isAvailable() const {
        return parkedVehicle == nullptr;
    }

    bool parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr ||
            !isAvailable() ||
            !canFit(*vehicle)) {
            return false;
        }

        parkedVehicle = vehicle;
        return true;
    }

    bool removeVehicle() {
        if (isAvailable()) {
            return false;
        }

        parkedVehicle = nullptr;
        return true;
    }

    int getSpotId() const {
        return spotId;
    }

    string getParkedVehicleNumber() const {
        if (parkedVehicle == nullptr) {
            return "Empty";
        }

        return parkedVehicle->getRegistrationNumber();
    }

    virtual ~ParkingSpot() = default;
};

// 6. A car parking spot accepts only cars
class CarParkingSpot : public ParkingSpot {
public:
    CarParkingSpot(int id) : ParkingSpot(id) {}

    bool canFit(const Vehicle& vehicle) const override {
        return vehicle.getType() == VehicleType::CAR;
    }
};

// 7. A bike parking spot accepts only bikes
class BikeParkingSpot : public ParkingSpot {
public:
    BikeParkingSpot(int id) : ParkingSpot(id) {}

    bool canFit(const Vehicle& vehicle) const override {
        return vehicle.getType() == VehicleType::BIKE;
    }
};

// 8. ParkingLot manages all parking spots
class ParkingLot {
private:
    vector<unique_ptr<ParkingSpot>> spots;

public:
    void addCarSpot(int id) {
        spots.push_back(make_unique<CarParkingSpot>(id));
    }

    void addBikeSpot(int id) {
        spots.push_back(make_unique<BikeParkingSpot>(id));
    }

    bool parkVehicle(Vehicle* vehicle) {
        if (vehicle == nullptr) {
            return false;
        }

        for (const auto& spot : spots) {
            if (spot->isAvailable() && spot->canFit(*vehicle)) {
                if (spot->parkVehicle(vehicle)) {
                    cout << "Vehicle "
                         << vehicle->getRegistrationNumber()
                         << " parked in spot "
                         << spot->getSpotId() << endl;
                    return true;
                }
            }
        }

        cout << "No suitable spot available for vehicle "
             << vehicle->getRegistrationNumber() << endl;
        return false;
    }

    bool unparkVehicle(const string& registrationNumber) {
        for (const auto& spot : spots) {
            if (spot->getParkedVehicleNumber() == registrationNumber) {
                spot->removeVehicle();

                cout << "Vehicle " << registrationNumber
                     << " removed from spot "
                     << spot->getSpotId() << endl;
                return true;
            }
        }

        cout << "Vehicle " << registrationNumber
             << " was not found in the parking lot." << endl;
        return false;
    }

    void showParkingStatus() const {
        cout << "\n--- Parking Lot Status ---\n";

        for (const auto& spot : spots) {
            cout << "Spot " << spot->getSpotId()
                 << " : " << spot->getParkedVehicleNumber()
                 << endl;
        }
    }
};

// 9. Program execution starts here
int main() {
    ParkingLot lot;

    // Create parking spots
    lot.addCarSpot(1);
    lot.addCarSpot(2);
    lot.addBikeSpot(3);
    lot.addBikeSpot(4);

    // Create vehicles
    Car car1("CAR-101");
    Car car2("CAR-102");
    Bike bike1("BIKE-201");
    Bike bike2("BIKE-202");

    // Park vehicles
    lot.parkVehicle(&car1);
    lot.parkVehicle(&bike1);
    lot.parkVehicle(&car2);
    lot.parkVehicle(&bike2);

    lot.showParkingStatus();

    // Try to park another car when car spots are full
    Car car3("CAR-103");
    lot.parkVehicle(&car3);

    // Remove a vehicle
    lot.unparkVehicle("CAR-101");

    // Now another car can use the freed spot
    lot.parkVehicle(&car3);

    lot.showParkingStatus();

    return 0;
}
