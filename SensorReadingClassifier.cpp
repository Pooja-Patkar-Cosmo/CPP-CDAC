#include <iostream>
#include <windows.h> // Required for SetConsoleOutputCP
using namespace std;

int main(){

    SetConsoleOutputCP(CP_UTF8); 

    double c;
    int status_code;

    cout << "Enter the temperature in °C: ";
    cin >> c ;

    if (c < 0) status_code = -1;
    else if (c >= 0 && c <=29) status_code = 0;
    else if (c >= 30 && c <=44) status_code = 1;
    else if (c >= 45 && c <=59) status_code = 2;
    else if (c >=60) status_code = 3;

    string status;
    string action;

    switch(status_code){
        case -1 :
            status = "SENSOR_ERROR";
            action = "Sensor fault — check wiring";
            break;

        case 0:
            status = "NORMAL";
            action = "No action required";
            break;

        case 1:
            status = "WARNING";  
            action = "Alert sent to supervisor";
            break;

        case 2:
            status = "CRITICAL";
            action = "CRITICAL Cooling system triggered";
            break;
            
        case 3:
            status = "SHUTDOWN";
            action = "Emergency shutdown initiated";
            break;

        default: 
            cout << "Unknown Status and Action";
            break;
    }


    //Reading 
    string r = c > 25 ? "Above Average" : "Below Average";
    
    //Calculate temparature in Farenheit
    double f = (c * 9/5) + 32;

    cout << endl << "Temperature : " << c << "°C / " << f << "°F" << endl;;
    cout << "Status      : " << status << endl;
    cout << "Action      : " << action << endl;
    cout << "Reading     : " << r << endl;
    
    return 0;
}

