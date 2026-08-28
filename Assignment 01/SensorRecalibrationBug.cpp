#include <iostream>
using namespace std;

// call by value 
void resetSensorPairV1(int a, int b){
    int temp = 0;

    temp = a;
    a = b;
    b = temp;
}

// call by reference
void resetSensorPairV2(int &a, int &b){
    int temp = 0;

    temp = a;
    a = b;
    b = temp;
}


// call by pointer
void resetSensorPairV3(int *a, int *b){
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int a = 55;
    int b= 12;

    cout << "--- V1 : Call By Value ---" << endl;
    cout << "Before  : " << "A = " << a << "  B=" << b << endl;

    resetSensorPairV1(a,b); 
    cout << "After   : " << "A = " << a << "  B=" << b; 
    cout << "    <- values unchanged" << endl << endl;
    
    
    cout << "--- V2 : Call By Reference ---" << endl;
    cout << "Before  : " << "A = " << a << "  B=" << b << endl;

    resetSensorPairV2(a,b); 
    cout << "After   : " << "A = " << a << "  B=" << b; 
    cout << "    <- values swapped" << endl << endl;

    
    int *p1 = &a;
    int *p2 = &b;
    cout << "--- V3 : Call By Pointer ---" << endl;
    cout << "Before  : " << "A = " << a << "  B=" << b << endl;

    resetSensorPairV3(p1,p2); 
    cout << "After   : " << "A = " << a << "  B=" << b; 
    cout << "    <- values swapped back" << endl << endl;

/*    
    "REASON WHY V1 FAILS:
    1. resetSensorPairV1 uses call-by-value, passing copies of arguments.
    2. The function stores these local copies in its own stack memory.
    3. Swapping occurs exclusively on these temporary local copies.
    4. When the function returns, its stack frame and copies are destroyed.
    5. The original variables in main() remain entirely unchanged.
*/  
    return 0;
}