#include <iostream>
#include <iomanip>
#include <windows.h>
#include <vector>
using namespace std;

int main(){
    SetConsoleOutputCP(CP_UTF8); 
    int N;

    cout << "Enter the number of reading: ";
    cin >> N;

    while (N < 1 || N > 100) {
        cout << "Enter a value from 1 to 100: ";
        cin >> N;
    }
    
    vector <double> readings(N);
    cout << "Enter " << N << " readings: "<< endl;

    for (int i= 0; i < readings.size(); i++){
        cin >> readings[i];
    }


    //VALID READINGS ARRAY--------------------------------------------
    vector <double> valid_readings;
    int skip_count = 0;
   
    for (int i=0; i < readings.size(); i++){
        if (readings[i]<0){
            skip_count++;
            continue;
        } 
        else{
            valid_readings.push_back(readings[i]);
        }
    }


    cout << "Readings entered : " << N << endl;
    cout << fixed << setprecision(1);

    cout << "Valid readings   : ";
    for (double a: valid_readings){
        cout << a << "  ";
    }
  
    cout << endl << "Skipped (errors) : " << skip_count << endl << endl;


    //Scanning the first reading at or above 45 °C - the original reading array
    int index= -1;
    double t = 0.0;;
    for (int i = 0; i < readings.size(); i++){
        if (readings[i] >= 45) {
            t = readings[i];
            index = i;
            break;
        }   
    }

    cout << "FIRST CRITICAL   : " << "Index " << index << " -> " << t << "°C" << endl << endl;
 
    //Min, Max and Avg 
    double min_value = valid_readings[0];
    double max_value = valid_readings[0];
    double sum = 0.0;

    for (int i = 0; i < valid_readings.size(); i++){
        
        sum += valid_readings[i];

        if (valid_readings[i] < min_value) {
            min_value = valid_readings[i];
        }

        if (valid_readings[i] > max_value) {
            max_value = valid_readings[i];
        }
           
    }

    double avg = sum / valid_readings.size();

    
    cout << "Min : " << min_value << "°C   Max : " << max_value << "°C";
    
    cout << fixed << setprecision(2);
    cout << "   Avg : " << avg << "°C"<< endl << endl;
    
    // CATEGORY COUNT ------------------------------
    int normal_count = 0;
    int warning_count = 0;
    int critical_count = 0;
    int shutdown_count = 0;

    for (int i= 0; i< valid_readings.size(); i++){
        double c = valid_readings[i];

        if (c >= 0 && c <=29) normal_count++;
        else if (c >= 30 && c <=44) warning_count++;
        else if (c >= 45 && c <=59) critical_count++;
        else if (c >=60)  shutdown_count++;       
    }
        
    cout << "NORMAL: " << normal_count;
    cout << "  WARNING: " << warning_count;
    cout << "  CRITICAL: " << critical_count;
    cout << "  SHUTDOWN: " << shutdown_count;
    
    return 0;
}





