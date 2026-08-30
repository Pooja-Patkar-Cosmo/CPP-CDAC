#include <iostream>
#include <iomanip> 
#include <string>
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

    Employee(){
        empId = 1001 + employeeCount; 
        employeeCount ++;              
        name = "Unknown";              
        department = "Engineering";         
        grade = 'D';               
        basicSalary = 10001.0;       
        isActive = true;            
    }


    // Public setters 
    void setName(const string& n){
        if (n.empty())
            cerr << "Error : Name cannot be empty." << endl;
        else 
            name = n;
    }

    void setDepartment(const string& dept){
        if (dept == "Engineering" || dept == "HR" || dept == "Finance" || dept == "Operations")
            department = dept;
        else 
            cerr << "Error: " << dept << " is not a registered department." << endl;
    }

    void setGrade(char g){
          if (g == 'A' || g == 'B' || g == 'C' || g == 'D')
            grade = g;
        else 
            cerr << "Error: Invalid grade " << g << ". Accepted values are " << endl;
    }

    void setBasicSalary(double salary){
        if (salary > 10000 && salary < 500000)
            basicSalary = salary;
        else 
         cout << "ERROR: Salary must be between Rs.10,000 and Rs.5,000,000. Value rejected.\n";
    }

    void deactivate(){
        isActive = false;
    }

    // Public getters — const
    int getEmpId() const { return empId;}
    string getName() const { return name;}
    string getDepartment() const { return department;}
    char getGrade() const { return grade;}
    double getBasicSalary() const { return basicSalary;}
    bool getIsActive() const { return isActive;}

    // Business logic — const  
    double computeAllowances() const{
       switch(grade){
            case 'A': return 0.40 * basicSalary; // Senior / Manager
            case 'B': return 0.30 * basicSalary; // Mid-level
            case 'C': return 0.20 * basicSalary; // Junior
            case 'D': return 0.10 * basicSalary; // Trainee
            default: return 0.0;
        }
    }


    double computeGrossSalary() const{
        return basicSalary + computeAllowances();
    }
  

    double computeTax() const{
        double gross = computeGrossSalary();
        if (gross <= 50000)
            return 0.0;
        else if ( gross <= 100000)
            return 0.10 * (gross - 50000);
        else 
            return 5000 + (0.20 * (gross - 100000));  
    }

    double computeNetSalary() const{
        return computeGrossSalary() - computeTax();
    }
   
    void printPayslip() const{
        if (!isActive){
            cout <<  "\nEmployee ID " << empId << " ( " << name << ") is inactive. Payslip cannot be generated." << endl;
            return ; 
        }

        int allowance_percentage = 0;
        if (grade == 'A') allowance_percentage = 40;
        else if (grade == 'B') allowance_percentage = 30;
        else if (grade == 'C') allowance_percentage = 20;
        else if (grade == 'D') allowance_percentage = 10;


        cout << "\n==================================================" << endl;
        cout << "         EMPLOYEE PAYSLIP - AUG 2026              " << endl;
        cout << "==================================================" << endl;
        cout << left << setw(15) << "Emp ID" << ":" << empId << endl;
        cout << left << setw(15) << "Name" << ":" << name << endl;
        cout << left << setw(15) << "Department" << ":" << department << endl;
        cout << left << setw(15) << "Grade" << ":" << grade << endl;
        cout << left << setw(15) << "Status" << ":" << (isActive ? "Active" : "Inactive") << endl;
        cout << fixed << setprecision(2);
        
        cout << left << setw(20) << "Basic Salary" << ": Rs. " << right << setw(10) << basicSalary << endl;
        cout << left << "Allowances (" << allowance_percentage << "%)" << setw(4) << "" << ": Rs. " << right << setw(10) << computeAllowances() << endl;
        cout << left << setw(20) << "Gross Salary" << ": Rs. " << right << setw(10) << computeGrossSalary() << endl;
        
        cout << "--------------------------------------------------" << endl;
        cout << left << setw(15) << "Tax Deduction" << ": Rs. " << right << setw(10) << computeTax() << endl;
        cout << left << setw(15) << "Net Salary" << ": Rs. " << right << setw(10) << computeNetSalary() << endl;
        cout << "==================================================" << endl;
    }



    static int getEmployeeCount(){
        return employeeCount;
    }

    // Input:
    void acceptDetails(){
        string inputName, inputDept;
        double inputSalary;
        char inputGrade;


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

int Employee :: employeeCount= 0;

int main() {

    // Create objects — one on stack, two on heap
    Employee e1;
    Employee* e2 = new Employee();
    Employee* e3 = new Employee();

    e1.acceptDetails();
    e2->acceptDetails();
    e3->acceptDetails();

    // NOTE
    // e1.empId = 999; 
    // e1.basicSalary = -1000;
    
    // REASON FOR COMPILER ERROR:
    // 'empId' and 'basicSalary' are declared as private members inside the Employee class.
    // In C++, private members cannot be directly accessed or modified from outside the class (such as in main()).

    e1.printPayslip();
    e2->printPayslip();
    e3->printPayslip();
    
    // Simulating a resignation    
    e3->deactivate();
    if (!e3->getIsActive())
        cout << e3->getName() << " is no longer active. Payroll skipped." << endl;

    cout << "Total Employees : " << Employee::getEmployeeCount() << endl;

    delete e2;
    delete e3;

    return 0;
}
