#include <iostream>
#include <string>

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
        : registrationNo(reg), ownerName(owner), yearOfManufacture(year), kmDriven(km) {
        cout << "[Vehicle Constructor] " << registrationNo << " : " << ownerName << "\n";
    }

    virtual ~Vehicle() {
        cout << "[Vehicle Destructor] " << registrationNo << "\n";
    }

    virtual double fuelCost(double kmToTravel) const = 0;
    virtual void describe() const = 0;
    virtual string vehicleType() const = 0;
};

// Truck Class (Single Inheritance from Vehicle)
class Truck : public Vehicle {
protected:
    double payloadCapacityTons;
    double fuelEfficiencyKmpl;

public:
    Truck(const string& reg, const string& owner, int year, double km, double payload, double efficiency)
        : Vehicle(reg, owner, year, km), payloadCapacityTons(payload), fuelEfficiencyKmpl(efficiency) {
        cout << "[Truck Constructor] " << registrationNo << "\n";
    }

    ~Truck() override {
        cout << "[Truck Destructor] " << registrationNo << "\n";
    }

    double fuelCost(double kmToTravel) const override {
        double adjustedEfficiency = fuelEfficiencyKmpl * (1.0 - (0.05 * payloadCapacityTons));
        if (adjustedEfficiency <= 0) adjustedEfficiency = 0.01;
        return (kmToTravel / adjustedEfficiency) * 93.00;
    }

    string vehicleType() const override { return "Truck"; }
    void describe() const override {}
};

// ElectricTruck Class (Multilevel Inheritance: Vehicle -> Truck -> ElectricTruck)
class ElectricTruck : public Truck {
private:
    double batteryCapacityKwh;
    double rangePerChargeKm;

public:
    ElectricTruck(const string& reg, const string& owner, int year, double km, double payload, double efficiency, double batteryCap, double range)
        : Truck(reg, owner, year, km, payload, efficiency), batteryCapacityKwh(batteryCap), rangePerChargeKm(range) {
        cout << "[ElectricTruck Constructor] " << registrationNo << "\n";
    }

    ~ElectricTruck() override {
        cout << "[ElectricTruck Destructor] " << registrationNo << "\n";
    }

    double fuelCost(double kmToTravel) const override {
        return (kmToTravel / rangePerChargeKm) * batteryCapacityKwh * 9.50;
    }

    string vehicleType() const override { return "Electric Truck"; }
    void describe() const override {}
};

int main() {
    {
        // Creating a stack object of type ElectricTruck to observe the chain within a scope
        ElectricTruck myElectricTruck("V-ET001", "Green Logistics", 2023, 1200.0, 3.0, 6.0, 150.0, 300.0);
    } // ...scope ends...

    cout << "...scope ends...\n";

    return 0;
}