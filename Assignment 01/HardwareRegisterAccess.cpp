# include <iostream>
using namespace std;

int main(){

    int statusReg = 0b10110001; // Read-only from firmware side
    int controlReg = 0b00000000; // Firmware writes here
    int dataReg    = 0b11001010; // For reassignment demo

    //-------------------------------------------------------------------------
    // 1. Pointer to Constant Data (const int*)
    
    const int *regPtr1 = &statusReg;
    cout << "regPtr1 : " << *regPtr1 << endl;
   
    // FORBIDDEN WRITE 
    //*regPtr1 = dataReg;
    //Error : Cannot modify value because target data is marked 'const'

    //ALLOWED REPOINTING
    //regPtr1 = &dataReg; 
    //cout << "Address of dataReg : " << &dataReg << endl;
    //cout << "Repointing to dataReg : " << regPtr1 << endl;
    

    //-------------------------------------------------------------------------
   //2. Constant Pointer to Data (int* const)
    int * const regPtr2 = &controlReg;
    //cout << "regPtr2 : " << *regPtr2 << endl;
      
    // ALLOWED WRITE
    //*regPtr2 = dataReg;
    //cout << "controReg : " << controlReg << endl;
    //cout << "regPtr2   : " << *regPtr2 << endl;
    
    // FORBIDDEN REPOINTING:
    //regPtr2 = &dataReg;
    // ERROR:  Cannot repoint because the pointer itself is const


    //-------------------------------------------------------------------------
    // Requirement 3: Constant Pointer to Constant Data (const int* const)
    const int * const regPtr3 = &statusReg;
    cout << "regPtr3 : " << *regPtr3 << endl;
   
    // FORBIDDEN WRITE
    //*regPtr3 = dataReg;
    //ERROR: Cannot modify value because target data is marked 'const'

    // FORBIDDEN REPOINTING
    //regPtr3 = &dataReg;
    // ERROR:  Cannot repoint because the pointer itself is const

    return 0;
}