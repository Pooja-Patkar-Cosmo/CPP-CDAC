#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, char *argv[]){
    SetConsoleOutputCP(CP_UTF8); 

    if (argc < 4){
        cerr << "Usage : ./sensor_monitor <warn_threshold> <critical_threshold> <num_readings>" << endl;
        cerr << "Error : Missing arguments." << endl;
        return 1;
    }

    double warn = stod(argv[1]);
    double critical = stod(argv[2]);
    int num_readings = stod(argv[3]);
    
    cout << endl << "Config  :  Warn=" << warn << "°C " << "  Critical=" << critical << "°C " << "  Readings=" << num_readings << endl;

    
    double readings[num_readings] = {};
    if ((warn < critical) && (num_readings >=1 && num_readings <=500)){
        for (int i = 0; i < num_readings; i++)
            readings[i] = rand () % 70;
    }
    
    else{
        cout << "-----------------------------------------------------------" << endl;
        cerr << "Error        : Validation failed!" << endl << endl << "Requirements : " << "warn < critical AND 1 <= num_readings <= 500" << endl << endl;
        exit (1);    
 

    int normal_count = 0;
    int warning_count = 0;
    int critical_count = 0;
    int shutdown_count = 0;

    for (int i= 0; i < num_readings; i++){
        double c = readings[i];

        if (c >= 0 && c <=29) normal_count++;
        else if (c >= 30 && c <=44) warning_count++;
        else if (c >= 45 && c <=59) critical_count++;
        else if (c >=60)  shutdown_count++;       
    }
    cout << "Results :  ";
    cout << "NORMAL:" << normal_count;
    cout << "  WARNING:" << warning_count;
    cout << "  CRITICAL:" << critical_count;
    cout << "  SHUTDOWN:" << shutdown_count;
    
    return 0;
}
