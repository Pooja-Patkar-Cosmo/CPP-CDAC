#include <iostream>
using namespace std;

bool parsePacket(const int* rawData, int size, int** outMin, int** outMax){
    if (size <= 0 )
        return false;

    else{
        *outMin = const_cast<int*>(&rawData[0]);
        *outMax = const_cast<int*>(&rawData[0]);

        for (int i = 0; i < size; i++){
            if ( rawData[i] < **outMin) {
                *outMin = const_cast<int*>(&rawData[i]);
            }
        }

        for (int i = 0; i < size; i++){
            if ( rawData[i] > **outMax) {
                *outMax = const_cast<int*>(&rawData[i]);
            }
        }   
            return true;    
    }

}

int main(){
    int packet[] = {45, 12, 67, 8, 55, 31};
    int* minPtr = nullptr;
    int* maxPtr = nullptr;

    if (parsePacket(packet, 6, &minPtr, &maxPtr)) {
        cout << "Calibration Min : " << *minPtr << " (at index " << minPtr - packet << ")" << endl;
        cout << "Calibration Max : " << *maxPtr << " (at index " << maxPtr - packet << ")" << endl;
    }

    return 0;
}