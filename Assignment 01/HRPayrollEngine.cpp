#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Employee {
private:
    int empId;
    string name;
    string department;
    char grade;
    double basicSalary;
    bool isActive;

    // Static member shared across all objects
    static int employeeCount;

public:
   
    Employee() {
        empId = 1001 + employeeCount;
        employeeCount++;
        name = "Unknown";
        department = "Engineering";
        grade = 'D';
        basicSalary = 10001.0;
        isActive = true;
    }

    // Setters

    void setName(const string& n) {
        if (n.empty()) {
            cout << "ERROR: Name cannot be empty.\n";
        } else {
            name = n;
        }
    }

    void setDepartment(const string& dept) {
        if (dept == "Engineering" || dept == "HR" || dept == "Finance" || dept == "Operations") {
            department = dept;
        } else {
            cout << "ERROR: '" << dept << "' is not a registered department.\n";
        }
    }

    void setGrade(char g) {
        if (g == 'A' || g == 'B' || g == 'C' || g == 'D') {
            grade = g;
        } else {
            cout << "ERROR: Invalid grade '" << g << "'. Accepted values: A, B, C, D.\n";
        }
    }

    void setBasicSalary(double salary) {
        if (salary > 10000.0 && salary < 500000.0) {
            basicSalary = salary;
        } else {
            cout << "ERROR: Salary must be between Rs.10,000 and Rs.5,000,000. Value rejected.\n";
        }
    }

    void deactivate() {
        isActive = false;
    }

    // Getters 

    int getEmpId() const { return empId; }
    string getName() const { return name; }
    string getDepartment() const { return department; }
    char getGrade() const { return grade; }
    double getBasicSalary() const { return basicSalary; }
    bool getIsActive() const { return isActive; }

    // --- Business Logic Functions (const) ---

    double computeAllowances() const {
        switch (grade) {
            case 'A': return 0.40 * basicSalary; 
            case 'B': return 0.30 * basicSalary; 
            case 'C': return 0.20 * basicSalary; 
            case 'D': return 0.10 * basicSalary; 
            default: return 0.0;
        }
    }

    double computeGrossSalary() const {
        return basicSalary + computeAllowances();
    }

    double computeTax() const {
        double gross = computeGrossSalary();
        if (gross <= 50000.0) {
            return 0.0;
        } else if (gross <= 100000.0) {
            return 0.10 * (gross - 50000.0);
        } else {
            return 5000.0 + 0.20 * (gross - 100000.0);
        }
    }

    double computeNetSalary() const {
        return computeGrossSalary() - computeTax();
    }

    void printPayslip() const {
        if (!isActive) {
            cout << "\nEmployee ID " << empId << " (" << name << ") is inactive. Payslip cannot be generated.\n";
            return;
        }

        int allowancePct = 0;
        if (grade == 'A') allowancePct = 40;
        else if (grade == 'B') allowancePct = 30;
        else if (grade == 'C') allowancePct = 20;
        else if (grade == 'D') allowancePct = 10;

        cout << "\n==================================================" << endl;
        cout << "         EMPLOYEE PAYSLIP - AUG 2026              " << endl;
        cout << "==================================================" << endl;
        cout << left << setw(15) << "Emp ID" << ": " << empId << endl;
        cout << left << setw(15) << "Name" << ": " << name << endl;
        cout << left << setw(15) << "Department" << ": " << department << endl;
        cout << left << setw(15) << "Grade" << ": " << grade << endl;
        cout << left << setw(15) << "Status" << ": " << (isActive ? "Active" : "Inactive") << endl;
        cout << "--------------------------------------------------" << endl;
        cout << fixed << setprecision(2);
        cout << left << setw(15) << "Basic Salary" << ": Rs. " << right << setw(10) << basicSalary << endl;
        cout << left << "Allowances (" << allowancePct << "%)" << setw(5) << "" << ": Rs. " << right << setw(10) << computeAllowances() << endl;
        cout << left << setw(15) << "Gross Salary" << ": Rs. " << right << setw(10) << computeGrossSalary() << endl;
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(15) << "Tax Deduction" << ": Rs. " << right << setw(10) << computeTax() << endl;
        cout << left << setw(15) << "Net Salary" << ": Rs. " << right << setw(10) << computeNetSalary() << endl;
        cout << "==================================================" << endl;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }

    void acceptDetails() {
        string inputName, inputDept;
        char inputGrade;
        double inputSalary;

        cout << "\n--- Entering details for Employee ID: " << empId << " ---\n";

        cout << "Enter Name: ";
        getline(cin >> ws, inputName);
        setName(inputName);

        cout << "Enter department: ";
        getline(cin >> ws, inputDept);
        setDepartment(inputDept);

        cout << "Enter grade: ";
        cin >> inputGrade;
        setGrade(inputGrade);

        cout << "Enter basic salary: ";
        cin >> inputSalary;
        setBasicSalary(inputSalary);
    }
};

// Initialized static member variable
int Employee::employeeCount = 0;

int main() {
    Employee e1;
    Employee* e2 = new Employee();
    Employee* e3 = new Employee();

    e1.acceptDetails();
    e2->acceptDetails();
    e3->acceptDetails();

    e1.printPayslip();
    e2->printPayslip();
    e3->printPayslip();

    e3->deactivate();
    if (!e3->getIsActive()) {
        cout << endl << e3->getName() << " is no longer active. Payroll skipped." << endl;
    }

    cout << "Total Employees : " << Employee::getEmployeeCount() << endl;

    delete e2;
    delete e3;

    return 0;
}
