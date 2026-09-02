#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

class Product {
private:
    int productId;
    string name;
    double price;
    int quantity;

public:
    void acceptDetails() {
        cout << "\n==== Enter Product Details ====\n";
        cout << "Product ID : ";
        cin >> productId;

        cout << "Name       : ";
        cin >> name;

        cout << "Price      : ";
        cin >> price;

        cout << "Quantity   : ";
        cin >> quantity;
    }

    void displayDetails(int threshold) const {
        // Output row formatted into tidy aligned columns
        cout << left << setw(6) << productId
             << setw(12) << name
             << right << setw(10) << fixed << setprecision(2) << price
             << setw(8) << quantity
             << setw(14) << totalValue();

        if (isLowStock(threshold)) {
            cout << "    \x1b[31m\x2190 LOW STOCK\x1b[0m"; // Optional colored arrow or simple "← LOW STOCK"
        }
        cout << endl;
    }

    double totalValue() const {
        return price * quantity;
    }

    bool isLowStock(int threshold) const {
        return quantity < threshold;
    }

    string getName() const {
        return name;
    }
};

int main() {
    const int SIZE = 5;
    Product prodArr[SIZE]; // Stack allocation for 5 products

    // 1 & 2. Accept details for all 5 products
    for (int i = 0; i < SIZE; i++) {
        cout << "\nProduct " << (i + 1) << " of " << SIZE << ":";
        prodArr[i].acceptDetails();
    }

    // Input low stock threshold from user
    int threshold;
    cout << "\nEnter Low Stock Threshold: ";
    cin >> threshold;

    // 3. Display formatted inventory report table
    cout << "\n===== INVENTORY REPORT =====\n";
    cout << left << setw(6) << "ID"
         << setw(12) << "Name"
         << right << setw(10) << "Price"
         << setw(8) << "Qty"
         << setw(14) << "Total Value" << endl;
    cout << string(52, '-') << endl;

    for (int i = 0; i < SIZE; i++) {
        prodArr[i].displayDetails(threshold);
    }

    // 4. Find product with highest total value
    int maxIndex = 0;
    double maxValue = prodArr[0].totalValue();

    for (int i = 1; i < SIZE; i++) {
        if (prodArr[i].totalValue() > maxValue) {
            maxValue = prodArr[i].totalValue();
            maxIndex = i;
        }
    }

    cout << "\nHighest Value Product : " << prodArr[maxIndex].getName() 
         << " (Rs. " << fixed << setprecision(2) << maxValue << ")" << endl;

    // 5. Print all products below the threshold
    cout << "Low Stock (threshold: " << threshold << ") : ";
    bool first = true;
    for (int i = 0; i < SIZE; i++) {
        if (prodArr[i].isLowStock(threshold)) {
            if (!first) cout << ", ";
            cout << prodArr[i].getName();
            first = false;
        }
    }
    if (first) cout << "None";
    cout << endl;

    return 0;
}