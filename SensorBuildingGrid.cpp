#include <iostream>
#include <iomanip>
#include <windows.h>
#include <cmath> 
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8); 
    double readings[3][3] = {};

    for ( int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++)
            cin >> readings[i][j];   
    }

    double max_value = readings[0][0];
    int floor = 0;
    int room = 0;
    int warning_count = 0;
    cout << fixed << setprecision(2);

    cout << "          "<< "Room 1" << "   Room 2" << "   Room 3" << endl;
    cout << "---------------------------------" << endl;
    for ( int i =0; i< 3; i++){
        cout << "Floor " << i+1 << " : ";
        for (int j = 0; j < 3; j++){
            cout << readings[i][j] << "    ";

            if (readings[i][j] > max_value) {
                max_value = readings[i][j];
                floor = i+1;
                room = j+1;
            }

            if (readings[i][j] >= 30){
                warning_count++;
            }

        }
        cout << endl;

        
    } 

    //To find the hottest room
    cout << endl << "Hottest room  : " << " Floor " << floor << ", Room " << room;
    cout << " -> " << max_value << "°C" << endl << endl;

    // Finding the Hottest floor
    double floor1_sum = 0.0, floor2_sum = 0.0, floor3_sum = 0.0;
    
    for (int j=0; j < 3; j++){
        floor1_sum += readings[0][j];
        floor2_sum += readings[1][j];
        floor3_sum += readings[2][j];
    }

    // Floor avg
    double avg1 = floor1_sum / 3;
    double avg2 = floor2_sum / 3;
    double avg3 = floor3_sum / 3;
    double max_floor_avg = max(avg1, max(avg2, avg3));

    int hottest_floor = 0;
    if (max_floor_avg == avg1) hottest_floor = 1;
    else if (max_floor_avg == avg2) hottest_floor = 2;
    else hottest_floor = 3;

    cout << "Hottest Floor : " << "Floor " << hottest_floor << " (avg " << max_floor_avg << "°C)" << endl << endl;
    cout << "Rooms at WARNING or above : " << warning_count << endl;

    return 0;
}



