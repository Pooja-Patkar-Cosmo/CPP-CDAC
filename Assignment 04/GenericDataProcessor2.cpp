#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// --- Class Template: DataBuffer<T> ---
template <typename T>
class DataBuffer {
private:
    T* data;            // heap-allocated array
    int capacity;       // maximum capacity
    int head;           // index of oldest element
    int tail;           // index where next element is written
    int count;          // current number of elements

public:
    // Constructor
    DataBuffer(int cap) : capacity(cap), head(0), tail(0), count(0) {
        data = new T[capacity];
    }

    // Destructor
    ~DataBuffer() {
        delete[] data;
    }

    // Add element — overwrites oldest if full
    void push(const T& value) {
        data[tail] = value;
        tail = (tail + 1) % capacity;
        
        if (count < capacity) {
            count++;
        } else {
            head = (head + 1) % capacity; // Overwrote oldest, advance head
        }
    }

    // Remove and return oldest element
    T pop() {
        if (isEmpty()) {
            throw underflow_error("Buffer is empty");
        }
        T oldest = data[head];
        head = (head + 1) % capacity;
        count--;
        return oldest;
    }

    // View oldest without removing
    T peek() const {
        if (isEmpty()) {
            throw underflow_error("Buffer is empty");
        }
        return data[head];
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }

    int size() const {
        return count;
    }

    // Template friend — print all elements in order from oldest to newest
    template <typename U>
    friend ostream& operator<<(ostream& out, const DataBuffer<U>& buf);
};

// Definition of the friend operator<< function template.
// Why it's in the header: C++ templates require the compiler to see the complete 
// definition at instantiation time to generate code for specific types (e.g., int, double, string).
template <typename U>
ostream& operator<<(ostream& out, const DataBuffer<U>& buf) {
    out << "[";
    for (int i = 0; i < buf.count; ++i) {
        int idx = (buf.head + i) % buf.capacity;
        out << buf.data[idx];
        if (i < buf.count - 1) {
            out << ", ";
        }
    }
    out << "]";
    return out;
}

// --- Main Program Demonstration ---
int main() {
    // 1. Integer buffer — simulate sensor tick IDs (Capacity 5)
    DataBuffer<int> tickBuffer(5);
    for (int i = 1; i <= 7; ++i) {
        tickBuffer.push(i * 10); // Should overwrite oldest (10 and 20)
    }
    cout << "Tick Buffer: " << tickBuffer << "  (10 and 20 were overwritten)" << endl;
    cout << endl;

    // 2. Double buffer — simulate temperature readings (Capacity 4)
    DataBuffer<double> tempBuffer(4);
    tempBuffer.push(36.6); 
    tempBuffer.push(37.1);
    tempBuffer.push(38.2); 
    tempBuffer.push(36.9);
    
    cout << "Before pop: " << tempBuffer << endl;
    cout << "Popped: " << tempBuffer.pop() << endl;
    cout << "After pop: " << tempBuffer << endl;
    cout << endl;

    // 3. String buffer — simulate log message queue (Capacity 3)
    DataBuffer<string> logBuffer(3);
    logBuffer.push("INFO: Server started");
    logBuffer.push("WARN: High memory usage");
    logBuffer.push("ERROR: DB connection timeout");
    logBuffer.push("INFO: Retry successful"); // Overwrites "INFO: Server started"
    
    cout << "Log Buffer: " << logBuffer << endl;

    return 0;
}