#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Class: Vehicle
class Vehicle {
protected:
    string registrationNo;
    string ownerName;
    int yearOfManufacture;
    double kmDriven;

public:
    Vehicle(const string& reg, const string& owner, int year, double km)
        : registrationNo(reg), ownerName(owner), yearOfManufacture(year), kmDriven(km) {}

    virtual double fuelCost(double kmToTravel) const = 0; // Pure virtual
    
    virtual void describe() const {
        cout << "Registration No: " << registrationNo << "\n"
             << "Owner: " << ownerName << "\n"
             << "Year: " << yearOfManufacture << "\n"
             << "KM Driven: " << kmDriven << " km\n";
    }

    virtual string vehicleType() const = 0; // Pure virtual

    virtual ~Vehicle() {} // Virtual destructor

    double getKmDriven() const { return kmDriven; }
    string getRegNo() const { return registrationNo; }
};

// Car Class (Single Inheritance from Vehicle)
class Car : public Vehicle {
private:
    string fuelType; // "Petrol" or "Diesel"
    double mileageKmpl;

public:
    Car(const string& reg, const string& owner, int year, double km, const string& fType, double mileage)
        : Vehicle(reg, owner, year, km), fuelType(fType), mileageKmpl(mileage) {}

    double fuelCost(double kmToTravel) const override {
        double fuelPricePerLitre = (fuelType == "Petrol") ? 106.00 : 93.00;
        return (kmToTravel / mileageKmpl) * fuelPricePerLitre;
    }

    string vehicleType() const override {
        return "Car";
    }

    void describe() const override {
        Vehicle::describe();
        cout << "Vehicle Type: Car\n"
             << "Fuel Type: " << fuelType << "\n"
             << "Mileage: " << mileageKmpl << " km/l\n";
    }
};

// Truck Class (Single Inheritance from Vehicle)
class Truck : public Vehicle {
protected:
    double payloadCapacityTons;
    double fuelEfficiencyKmpl;

public:
    Truck(const string& reg, const string& owner, int year, double km, double payload, double efficiency)
        : Vehicle(reg, owner, year, km), payloadCapacityTons(payload), fuelEfficiencyKmpl(efficiency) {}

    double fuelCost(double kmToTravel) const override {
        // Efficiency drops 5% per ton carried (diesel assumed standard at 93.00/L)
        double adjustedEfficiency = fuelEfficiencyKmpl * (1.0 - (0.05 * payloadCapacityTons));
        if (adjustedEfficiency <= 0) adjustedEfficiency = 0.01; // safeguard
        double fuelPricePerLitre = 93.00; 
        return (kmToTravel / adjustedEfficiency) * fuelPricePerLitre;
    }

    string vehicleType() const override {
        return "Truck";
    }

    void describe() const override {
        Vehicle::describe();
        cout << "Vehicle Type: Truck\n"
             << "Payload Capacity: " << payloadCapacityTons << " tons\n"
             << "Base Fuel Efficiency: " << fuelEfficiencyKmpl << " km/l\n";
    }
};

// ElectricTruck Class (Multilevel Inheritance: Vehicle -> Truck -> ElectricTruck)
class ElectricTruck : public Truck {
private:
    double batteryCapacityKwh;
    double rangePerChargeKm;

public:
    ElectricTruck(const string& reg, const string& owner, int year, double km, double payload, double efficiency, double batteryCap, double range)
        : Truck(reg, owner, year, km, payload, efficiency), batteryCapacityKwh(batteryCap), rangePerChargeKm(range) {}

    double fuelCost(double kmToTravel) const override {
        // Electricity cost: 9.50/kWh based on formula: (km / rangePerChargeKm) * batteryCapacityKwh * electricityCostPerUnit
        double electricityCostPerUnit = 9.50;
        return (kmToTravel / rangePerChargeKm) * batteryCapacityKwh * electricityCostPerUnit;
    }

    string vehicleType() const override {
        return "Electric Truck";
    }

    void describe() const override {
        Vehicle::describe();
        cout << "Vehicle Type: Electric Truck\n"
             << "Payload Capacity: " << payloadCapacityTons << " tons\n"
             << "Battery Capacity: " << batteryCapacityKwh << " kWh\n"
             << "Range per Charge: " << rangePerChargeKm << " km\n";
    }
};

// Van Class (Hierarchical Inheritance directly from Vehicle)
class Van : public Vehicle {
private:
    int seatingCapacity;
    double mileageKmpl;

public:
    Van(const string& reg, const string& owner, int year, double km, int seats, double mileage)
        : Vehicle(reg, owner, year, km), seatingCapacity(seats), mileageKmpl(mileage) {}

    double fuelCost(double kmToTravel) const override {
        // Standard petrol calculation (106.00/L)
        double fuelPricePerLitre = 106.00;
        return (kmToTravel / mileageKmpl) * fuelPricePerLitre;
    }

    string vehicleType() const override {
        return "Van";
    }

    void describe() const override {
        Vehicle::describe();
        cout << "Vehicle Type: Van\n"
             << "Seating Capacity: " << seatingCapacity << "\n"
             << "Mileage: " << mileageKmpl << " km/l\n";
    }
};

// Main function to demonstrate polymorphism
int main() {
    // Creating a polymorphic array of Vehicle pointers
    Vehicle* fleet[4];
    fleet[0] = new Car("MH04AB1234", "John Doe", 2021, 15000.5, "Petrol", 18.5);
    fleet[1] = new Truck("MH04XY5678", "Logistics Corp", 2019, 85000.0, 4.0, 6.5);
    fleet[2] = new ElectricTruck("MH04ET9999", "EcoFreight Ltd", 2023, 5000.0, 2.0, 5.0, 150.0, 300.0);
    fleet[3] = new Van("MH04VN4321", "QuickDeliveries", 2020, 34000.0, 8, 12.0);

    double tripDistance = 150.0; // km to travel for cost report

    for (int i = 0; i < 4; ++i) {
        cout << "----------------------------------------\n";
        fleet[i]->describe();
        cout << "Estimated Fuel/Energy Cost for " << tripDistance << " km: INR " 
             << fixed << setprecision(2) << fleet[i]->fuelCost(tripDistance) << "\n";
    }

    // Clean up memory
    for (int i = 0; i < 4; ++i) {
        delete fleet[i];
    }

    return 0;
}