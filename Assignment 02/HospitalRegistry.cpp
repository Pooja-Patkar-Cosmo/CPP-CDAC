#include <iostream>
#include <string>

using namespace std;

class Patient {
private:
    int patientId;
    string name;
    int age;
    string ward;
    const string bloodGroup; // Initialized in constructor initializer list

public:
    // Constructor 1 - Default
    Patient() 
        : patientId(0), name("Unknown"), age(0), ward("General"), bloodGroup("O+") {
        cout << "[Constructor] Default patient registered.\n";
    }

    // Constructor 2 - Emergency admission
    Patient(int id, const string& name) 
        : patientId(id), name(name), age(0), ward("General"), bloodGroup("O+") {
        cout << "[Constructor] Emergency: " << this->name << "\n";
    }

    // Constructor 3 - Full admission details
    Patient(int id, const string& name, int age, const string& ward, const string& bg) 
        : patientId(id), name(name), age(age), ward(ward), bloodGroup(bg) {
        cout << "[Constructor] Full admission: " << this->name << "\n";
    }

    // Destructor
    ~Patient() {
        cout << "[Destructor] Patient " << name << " discharged.\n";
    }

    // Function to accept input for array elements after default construction
    void acceptDetails() {
        cout << "Enter Patient ID: ";
        cin >> patientId;

        cout << "Enter Patient Name: ";
        cin >> name;

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Ward Name: ";
        cin >> ward;

        // Note: bloodGroup is const and set at construction time
    }

    void displayRecord() const {
        cout << "\nPatient Record:\n";
        cout << "  ID        : " << patientId << "\n";
        cout << "  Name      : " << name << "\n";
        cout << "  Age       : " << age << "\n";
        cout << "  Ward      : " << ward << "\n";
        cout << "  Blood Grp : " << bloodGroup << "\n";
    }

    void transferWard(const string& newWard) {
        cout << "\nWard Transfer: " << name << " -> " << newWard << "\n";
        ward = newWard;
    }
};

int main() {
    // 1. Create stack objects (triggers first 3 constructor messages)
    Patient p1(1001, "Meera Joshi", 34, "Cardiology", "B+");
    Patient p2(1002, "Raj Patel");
    Patient p3;
    cout << endl;

    // 2. Dynamically allocate array of 4 objects on heap
    // ALL 4 DEFAULT CONSTRUCTORS RUN HERE IMMEDIATELY AT ONCE
    Patient* wardPatients = new Patient[4];

    // Display sample stack object record as shown in expected output
    p1.displayRecord();

    // 3. Separate loop to accept input AFTER all constructors have printed
    cout << "\n=== Enter Details for Ward Patients ===\n";
    for (int i = 0; i < 4; i++) {
        cout << "\n--- Patient " << (i + 1) << " ---\n";
        wardPatients[i].acceptDetails();
    }

    // 4. Display all heap array records
    cout << "\n=== Displaying Ward Patient Records ===\n";
    for (int i = 0; i < 4; i++) {
        wardPatients[i].displayRecord();
    }

    // 5. Ward transfer demonstration
    p2.transferWard("ICU");

    // 6. Explicit deletion triggers destructors for the dynamic array
    delete[] wardPatients;
    cout << endl;

    // 7. Stack objects go out of scope at main return in reverse order
    return 0;
}