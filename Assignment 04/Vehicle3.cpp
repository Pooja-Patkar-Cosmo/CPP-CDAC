#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

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

    virtual ~Vehicle() {}

    virtual double fuelCost(double kmToTravel) const = 0;
    virtual void describe() const = 0;
    virtual string vehicleType() const = 0;

    string getRegNo() const { return registrationNo; }
    string getOwnerName() const { return ownerName; }
    double getKmDriven() const { return kmDriven; }
};

// Car Class
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

    string vehicleType() const override { return "Car"; }
    
    string getFuelType() const { return fuelType; }

    void describe() const override {
        Vehicle::describe();
        cout << "Vehicle Type: Car\nFuel Type: " << fuelType << "\n";
    }
};

// Truck Class
class Truck : public Vehicle {
protected:
    double payloadCapacityTons;
    double fuelEfficiencyKmpl;

public:
    Truck(const string& reg, const string& owner, int year, double km, double payload, double efficiency)
        : Vehicle(reg, owner, year, km), payloadCapacityTons(payload), fuelEfficiencyKmpl(efficiency) {}

    double fuelCost(double kmToTravel) const override {
        double adjustedEfficiency = fuelEfficiencyKmpl * (1.0 - (0.05 * payloadCapacityTons));
        if (adjustedEfficiency <= 0) adjustedEfficiency = 0.01;
        return (kmToTravel / adjustedEfficiency) * 93.00;
    }

    string vehicleType() const override { return "Truck"; }
    void describe() const override {}
};

// ElectricTruck Class (Multilevel Inheritance)
class ElectricTruck : public Truck {
private:
    double batteryCapacityKwh;
    double rangePerChargeKm;
    double batteryPercentage; // Added for battery status reporting

public:
    ElectricTruck(const string& reg, const string& owner, int year, double km, double payload, double efficiency, double batteryCap, double range, double battPct = 85.0)
        : Truck(reg, owner, year, km, payload, efficiency), batteryCapacityKwh(batteryCap), rangePerChargeKm(range), batteryPercentage(battPct) {}

    double fuelCost(double kmToTravel) const override {
        return (kmToTravel / rangePerChargeKm) * batteryCapacityKwh * 9.50;
    }

    string vehicleType() const override { return "Electric Truck"; }

    double getBatteryPercentage() const { return batteryPercentage; }

    void describe() const override {}
};

// Van Class (Hierarchical Inheritance)
class Van : public Vehicle {
private:
    int seatingCapacity;
    double mileageKmpl;

public:
    Van(const string& reg, const string& owner, int year, double km, int seats, double mileage)
        : Vehicle(reg, owner, year, km), seatingCapacity(seats), mileageKmpl(mileage) {}

    double fuelCost(double kmToTravel) const override {
        return (kmToTravel / mileageKmpl) * 106.00;
    }

    string vehicleType() const override { return "Van"; }
    void describe() const override {}
};

// Function Requirement: printFleetReport
void printFleetReport(const vector<Vehicle*>& fleet, double tripKm) {
    if (fleet.empty()) return;

    cout << "===== FLEET REPORT — Trip Distance: " << tripKm << " km =====\n";
    cout << left << setw(12) << "Reg" 
         << setw(16) << "Type" 
         << setw(18) << "Owner" 
         << right << setw(10) << "Km Driven" << "\n";

    for (const auto* v : fleet) {
        cout << left << setw(12) << v->getRegNo()
             << setw(16) << v->vehicleType()
             << setw(18) << v->getOwnerName()
             << right << setw(10) << fixed << setprecision(0) << v->getKmDriven() << "\n";
    }

    cout << "\n===== FUEL / CHARGE COST ESTIMATE =====\n";
    
    Vehicle* mostEfficientVehicle = fleet[0];
    double minCost = fleet[0]->fuelCost(tripKm);

    for (const auto* v : fleet) {
        double cost = v->fuelCost(tripKm);
        cout << left << setw(12) << v->getRegNo() 
             << " (" << setw(14) << v->vehicleType() << ") : Rs. " 
             << right << setw(8) << fixed << setprecision(2) << cost;

        // Check for specific vehicle types to display extra context
        if (auto* car = dynamic_cast<const Car*>(v)) {
            cout << "  (" << car->getFuelType() << ")";
        } else if (auto* et = dynamic_cast<const ElectricTruck*>(v)) {
            cout << "  [Battery: " << fixed << setprecision(0) << et->getBatteryPercentage() << "% charged]";
        }
        cout << "\n";

        // Track the most efficient vehicle
        if (cost < minCost) {
            minCost = cost;
            const_cast<Vehicle*&>(mostEfficientVehicle) = const_cast<Vehicle*>(v);
        }
    }

    cout << "\nMost Efficient Vehicle: " << mostEfficientVehicle->getRegNo() 
         << " (" << mostEfficientVehicle->vehicleType() << ") — Rs. " 
         << fixed << setprecision(2) << minCost << " for " << tripKm << " km\n";
}

int main() {
    // Create a vector of Vehicle pointers and add at least 5 vehicles
    vector<Vehicle*> fleet;
    fleet.push_back(new Car("KA01AA001", "Ramesh Kumar", 2021, 45200, "Petrol", 18.5));
    fleet.push_back(new Truck("MH04BB002", "Shyam Logistics", 2018, 123500, 4.0, 6.0));
    fleet.push_back(new ElectricTruck("GJ07CC003", "Green Fleet Co", 2023, 89000, 2.0, 5.0, 150.0, 300.0, 85.0));
    fleet.push_back(new Car("DL02DD004", "Anita Desai", 2022, 22000, "Diesel", 21.0));
    fleet.push_back(new Van("UP16EE005", "Express Travels", 2020, 54000, 10, 11.5));

    double tripDistance = 200.0;

    // Call the fleet report function
    printFleetReport(fleet, tripDistance);

    // Clean up heap memory
    for (auto* v : fleet) {
        delete v;
    }
    fleet.clear();

    return 0;
}