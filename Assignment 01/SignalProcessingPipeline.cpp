#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;


double computeRMS(double *ptr, int n){

    int i = 0;
    double sum = 0.0;
    double sq = 0.0;

    while(i<n){
        sq = (*(ptr + i)) * (*(ptr + i));
        sum += sq;
        i++;
    }
    
    double mean_of_sq = sum / n;
    double rms = sqrt (mean_of_sq);

    return rms;

}

void normalise(double *ptr, int n){

    double max_value = fabs(*ptr);

    for (int i = 0; i < n; i++){
        if (fabs(*(ptr + i)) > max_value)
            max_value = fabs(*(ptr + i));
    }

    cout << "After normalization      : ";
    for (int i = 0; i < n; i++){
        (*(ptr + i)) /= max_value;
        cout << *(ptr + i) << " ";
    }
    cout << endl;

}

int countZeroCrossings(double *ptr, int n){

    double product = 0.0;
    int crossings = 0;

    for (int i = 0; i < (n-1); i++){
        product =(*(ptr + i)) * (*(ptr+i+1));

        if (product < 0){
            crossings++;
        }
    }
    return crossings;
}

void applyGain(double *ptr, int n, double gainFactor){

    cout << "After gain               : ";
    for (int i = 0; i < n; i++){
        (*(ptr + i)) *= gainFactor;
        cout << *(ptr + i) << " ";
    }
    cout << endl;
}


int main(){
    double signals[] = {0.5, -1.2, 0.8, -0.3, 1.0, -0.9, 0.1};
    double *ptr = signals;
    int n = 7;

    cout << fixed << setprecision(2);
    cout << "RMS of signals           : " << computeRMS(ptr, n) << endl;

    cout << endl;
    cout << "Signals -Before          : ";
    for (int i = 0; i < n; i++){
        cout << (*(ptr + i)) << " ";
    }
    cout << endl;

    normalise(ptr, n);

    cout << endl;
    cout << "Count of Zero-crossings  : " << countZeroCrossings(ptr, n) << endl;

    cout << endl;
    
    cout << "Signals -Before          : ";
    for (int i = 0; i < n; i++){
        cout << (*(ptr + i)) << " ";
    }
    cout << endl;

    applyGain(ptr, n, 2.0);
    return 0;



}