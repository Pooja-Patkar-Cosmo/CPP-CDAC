#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <utility>

using namespace std;

class LedgerEntry {
private:
    string description;
    double* amounts;
    int days;

public:
    static int totalEntries;

    // Helper method to compute total sum of daily amounts
    double getTotal() const {
        double total = 0.0;
        if (amounts) {
            for (int i = 0; i < days; ++i) {
                total += amounts[i];
            }
        }
        return total;
    }

    // Constructor
    LedgerEntry(const string& desc, int days) 
        : description(desc), days(days) {
        amounts = new double[days](); // Initialized to zero
        totalEntries++;
        cout << "[LedgerEntry Created] " << description << " (" << days << " days)" << endl;
    }

    // Copy Constructor - deep copy
    LedgerEntry(const LedgerEntry& other) 
        : description(other.description), days(other.days) {
        amounts = new double[days];
        for (int i = 0; i < days; ++i) {
            amounts[i] = other.amounts[i];
        }
        totalEntries++;
    }

    // Move Constructor - transfer ownership, leave source in valid empty state
    LedgerEntry(LedgerEntry&& other) noexcept 
        : description(other.description), amounts(other.amounts), days(other.days) {
        cout << "[Move Constructor] Ownership transferred from: " << other.description << endl;
        other.amounts = nullptr;
        other.days = 0;
        other.description = "";
        totalEntries++;
    }

    // Copy Assignment Operator - deep copy with self-assignment guard
    LedgerEntry& operator=(const LedgerEntry& other) {
        if (this != &other) {
            delete[] amounts;
            description = other.description;
            days = other.days;
            amounts = new double[days];
            for (int i = 0; i < days; ++i) {
                amounts[i] = other.amounts[i];
            }
        }
        return *this;
    }

    // Move Assignment Operator - transfer ownership with self-assignment guard
    LedgerEntry& operator=(LedgerEntry&& other) noexcept {
        if (this != &other) {
            delete[] amounts;
            description = other.description;
            amounts = other.amounts;
            days = other.days;

            cout << "[Move Assignment] Ownership transferred from: " << other.description << endl;

            other.amounts = nullptr;
            other.days = 0;
            other.description = "";
        }
        return *this;
    }

    // Destructor
    ~LedgerEntry() {
        delete[] amounts;
        totalEntries--;
    }

    // Operator Overloads

    // Add corresponding daily amounts - return a new LedgerEntry
    LedgerEntry operator+(const LedgerEntry& other) const {
        int maxDays = (days > other.days) ? days : other.days;
        LedgerEntry result("Combined", maxDays);
        for (int i = 0; i < maxDays; ++i) {
            double val1 = (i < days) ? amounts[i] : 0.0;
            double val2 = (i < other.days) ? other.amounts[i] : 0.0;
            result.amounts[i] = val1 + val2;
        }
        return result;
    }

    // Compare total sum of amounts
    bool operator==(const LedgerEntry& other) const {
        return this->getTotal() == other.getTotal();
    }

    bool operator>(const LedgerEntry& other) const {
        return this->getTotal() > other.getTotal();
    }

    // Subscript operator - access/modify individual day's amount
    double& operator[](int index) {
        if (index < 0 || index >= days) {
            throw out_of_range("Index out of bounds");
        }
        return amounts[index];
    }

    const double& operator[](int index) const {
        if (index < 0 || index >= days) {
            throw out_of_range("Index out of bounds");
        }
        return amounts[index];
    }

    // Helper for main check requirement
    bool isAmountsNull() const {
        return amounts == nullptr;
    }

    // Stream operators - declared as friend functions
    friend ostream& operator<<(ostream& out, const LedgerEntry& entry);
    friend istream& operator>>(istream& in, LedgerEntry& entry);
};

// Initialize static member
int LedgerEntry::totalEntries = 0;

// Stream Insertion Operator
ostream& operator<<(ostream& out, const LedgerEntry& entry) {
    out << fixed << setprecision(2);
    out << entry.description << " : [";
    if (entry.amounts != nullptr) {
        for (int i = 0; i < entry.days; ++i) {
            out << entry.amounts[i];
            if (i < entry.days - 1) {
                out << ", ";
            }
        }
    }
    out << "] Total: " << entry.getTotal();
    return out;
}

// Stream Extraction Operator
istream& operator>>(istream& in, LedgerEntry& entry) {
    if (entry.amounts != nullptr) {
        for (int i = 0; i < entry.days; ++i) {
            in >> entry.amounts[i];
        }
    }
    return in;
}

int main() {
    // Objective 1 - Constructor & deep copy
    LedgerEntry jan("January Sales", 5);
    jan[0] = 1200.50; jan[1] = 3400.00; jan[2] = 800.75;
    jan[3] = 2100.00; jan[4] = 650.25;

    LedgerEntry feb("February Sales", 5);
    feb[0] = 900.00;  feb[1] = 2200.50; feb[2] = 1750.00;
    feb[3] = 3000.00; feb[4] = 475.50;

    cout << jan << endl;
    cout << feb << endl << endl;

    // Objective 2 - Operator + (sum two ledgers into combined)
    LedgerEntry combined = jan + feb;
    cout << "Combined : " << combined << endl << endl;

    // Objective 3 - Relational operators
    cout << "Jan == Feb : " << (jan == feb ? "Yes" : "No") << endl;
    cout << "Jan > Feb : " << (jan > feb ? "Yes" : "No") << endl << endl;

    // Objective 4 - Move constructor (should NOT deep copy)
    LedgerEntry moved = move(jan);
    cout << "After move, jan.amounts is null: "
         << (jan.isAmountsNull() ? "YES" : "NO") << endl;
    cout << "Moved entry : " << moved << endl << endl;

    // Objective 5 - Move assignment
    LedgerEntry q1("Q1 Total", 5);
    q1 = move(feb); // feb's resources transferred to q1
    cout << "Q1 (moved from feb) : " << q1 << endl << endl;

    // Objective 6 - Static member
    cout << "Live LedgerEntry objects: " << LedgerEntry::totalEntries << endl;

    return 0;
}