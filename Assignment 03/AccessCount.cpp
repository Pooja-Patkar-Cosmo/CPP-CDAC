#include <iostream>
using namespace std;

class LogBuffer {
private:
    // 1. Mark accessCount as mutable so it can be modified inside const member functions
    mutable int accessCount = 0;

public:
    LogBuffer() = default;

    // Copy constructor (used for: const LogBuffer readOnly(log1);)
    LogBuffer(const LogBuffer& other) : accessCount(0) {}

    // 2. Inside print() (which is const), increment accessCount
    void print() const {
        accessCount++;
        cout << "Printing buffer..." << endl;
    }

    // 3. Add a const getter: int getAccessCount() const;
    int getAccessCount() const {
        return accessCount;
    }
};

int main() {
    LogBuffer log1;

    // 4. In main(), call print() three times on a const LogBuffer object and print its access count
    const LogBuffer readOnly(log1); // copy construct into a const object
    readOnly.print();
    readOnly.print();
    readOnly.print();

    cout << "Times printed: " << readOnly.getAccessCount() << endl; // must print 3

    return 0;
}

/*
 --------------------------------------------------------------------------------------
  EXPLANATION:
 --------------------------------------------------------------------------------------
  1. Why accessCount must be mutable and not just a regular member:
     - When calling print() on a `const` object , the C++ compiler 
       treats all member variables as `const` within that function context.
     - A regular member variable cannot be modified inside a `const` member function.
     - Declaring `accessCount` as `mutable` explicitly informs the compiler that this 
       variable is exempted from const-correctness rules. It allows internal state 
       tracking (like access counters, caching, or mutexes) without breaking the 
       logical constness of the object to the outside world.

  2. What the `const` keyword on a member function actually prevents:
     - The `const` modifier on a member function doesn't allow the implicit `this` pointer 
       from `LogBuffer* const` to `const LogBuffer* const`.
     - This prevents the function from:
         a) Modifying any non-mutable member variables of the object.
         b) Calling any non-const member functions on the same object.
 
*/