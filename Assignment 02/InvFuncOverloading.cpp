#include <iostream>
using namespace std;

double reorderCost(int qty, double unitPrice){   
    return qty * unitPrice;
}         

double reorderCost(double qty, double unitPrice){   
    return qty * unitPrice;
}       

double reorderCost(int qty, double unitPrice, double taxRate) {
    double value = 0.0;
    value = (qty * unitPrice) + ((qty * unitPrice) * taxRate / 100);
    return value;
} 

double applyDiscount(double price, double discountPercent = 10.0){
    return price - (price * discountPercent / 100);
}
// If no discount is passed, apply 10% by default

int main(){
    cout << "--- REORDER COST ---" << endl;
    cout << "Integer value    " << reorderCost(20, 500.00) << endl;
    cout << "Fractional value " << reorderCost(20.00, 500.00) << endl;
    cout << "Value with tax   " << reorderCost(20, 500.00, 12) << endl << endl;

    double price = 20000;
    cout << "--- DISCOUNT ON " << price << " ---" << endl;
    cout << "Default - 10%   " << applyDiscount (price) << endl;
    cout << "Discount of 20% " << applyDiscount(price, 20);

    return 0;
}