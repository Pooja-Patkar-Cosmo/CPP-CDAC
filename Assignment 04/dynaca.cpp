#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Base class (must be polymorphic with at least one virtual function for dynamic_cast)
class DataProcessor {
public:
    virtual void process() = 0;
    virtual ~DataProcessor() = default;
};

// Derived Class 1: CSVProcessor
class CSVProcessor : public DataProcessor {
private:
    int records = 150;

public:
    void process() override {
        cout << "Processing CSV stream..." << endl;
    }

    int recordCount() const {
        return records;
    }
};

// Derived Class 2: SensorStreamProcessor
class SensorStreamProcessor : public DataProcessor {
private:
    double meanValue = 42.5;

public:
    void process() override {
        cout << "Processing Sensor stream..." << endl;
    }

    // Added getMean() getter
    double getMean() const {
        return meanValue;
    }
};

int main() {
    // Set up objects and populate the pipeline container
    CSVProcessor csvProc;
    SensorStreamProcessor sensorProc;

    vector<DataProcessor*> pipeline;
    pipeline.push_back(&csvProc);
    pipeline.push_back(&sensorProc);

    // Run the pipeline loop
    for (auto* p : pipeline) {
        p->process();
    }

    cout << "\n--- Safety Check Inspection ---\n";

    /*
     * EXPLANATION: WHY static_cast IS UNSAFE WHILE dynamic_cast IS SAFE HERE
     * 
     * 1. dynamic_cast (Safe):
     *    Performs a runtime check using Type Information (RTTI) to verify if the 
     *    underlying object matches the requested target pointer type. 
     *    If the object is NOT of that type, dynamic_cast safely evaluates to nullptr, 
     *    allowing conditional checks (if/else) without crashing.
     * 
     * 2. static_cast (Unsafe):
     *    Performs downcasting strictly at compile time without any runtime validation.
     *    If static_cast<CSVProcessor*>(p) was executed when 'p' actually points to a 
     *    SensorStreamProcessor, the compiler would forcefully convert the pointer. 
     *    Calling member functions through that incorrect pointer would lead to Undefined Behavior (UB), 
     *    corrupting memory or causing a segmentation fault.
     */
    for (auto* p : pipeline) {
        if (auto* csv = dynamic_cast<CSVProcessor*>(p)) {
            cout << "Found CSV Processor with " << csv->recordCount() << " records." << endl;
        } else if (auto* sensor = dynamic_cast<SensorStreamProcessor*>(p)) {
            cout << "Found Sensor Processor - Mean: " << sensor->getMean() << endl;
        }
    }

    return 0;
}