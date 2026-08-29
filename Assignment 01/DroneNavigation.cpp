#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

inline double distanceBetween(double x1, double y1, double x2, double y2){
    double dist = sqrt( pow((x2-x1), 2) + pow((y2-y1), 2));
    return dist;
}

inline double toRadians(double degrees){
    double radian_equivalent = degrees * ( M_PI / 180.0);
    return radian_equivalent;
}

inline double clamp(double value, double minVal, double maxVal){
    // Restrict value to [minVal, maxVal]
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

inline bool isInSafeZone(double x, double y, double cx, double cy, double radius){
    double zone_dist = sqrt( pow((cx-x), 2) + pow((cy-y), 2));

    if (zone_dist <= radius)
        return true;
    else
        return false;
}

int main(){
    double x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0, degrees = 0.0; 
    double value = 0.0, minVal = -50.0, maxVal = 50.0;
    double cx = 0.0, cy = 0.0, radius = 50.0, x= 0.0, y = 0.0;

    cout << "Enter the co-ordinates x1 y1 x2 y2: ";
    cin >> x1 >> y1 >> x2 >> y2;

    cout << endl <<"Enter angle in degrees : ";
    cin >> degrees;

    cout << endl << "Desired value for clamp: ";
    cin >> value;

    cout << endl << "Enter point(x, y) on circular zone : ";
    cin >> x >> y;

    cout << "-----------------------------------------------" << endl;
    cout << fixed << setprecision(1);
    cout << "Distance from home : " << distanceBetween(x1, y1, x2, y2) << endl;
    cout << "Degree to radians  : " << toRadians(degrees) << endl;
    cout << "Clamped value      : " << clamp(value, minVal, maxVal) << endl;
    cout << "Inside safe zone   : ";
    if (isInSafeZone(x, y, cx, cy, radius))
        cout << "Yes";
    else 
        cout << "No";
    return 0;
}




