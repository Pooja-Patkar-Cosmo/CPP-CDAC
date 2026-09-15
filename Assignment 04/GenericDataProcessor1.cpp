#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// --- Abstract Base Class ---
class DataProcessor {
public:
    // Pure virtual functions — all subclasses MUST implement these
    virtual void loadData(const string& source) = 0;
    virtual void processData() = 0;
    virtual void exportResult(const string& destination) = 0;
    virtual string processorType() const = 0;
    virtual int recordCount() const = 0;

    // Non-pure virtual — base provides a default report format
    virtual void printSummary() const {
        cout << "Processor: " << processorType() << "\n"
             << "Total Records: " << recordCount() << endl;
    }

    // Virtual destructor for safe polymorphic deletion
    virtual ~DataProcessor() = default;
};

// --- Concrete Class 1: CSVProcessor ---
class CSVProcessor : public DataProcessor {
private:
    vector<string> records;

public:
    void loadData(const string& source) override {
        // Simulating reading a CSV: hard-coding 5 sample rows
        records = {
            "row1: apple, fruit",
            "row2: carrot, vegetable",
            "row3: banana, fruit",
            "row4: broccoli, vegetable",
            "row5: cherry, fruit"
        };
        cout << "[CSV EXPORT -> " << source << "] Loaded " << records.size() << " rows.\n";
    }

    void processData() override {
        // Converts each record to uppercase
        for (auto& record : records) {
            transform(record.begin(), record.end(), record.begin(), ::toupper);
        }
    }

    void exportResult(const string& destination) override {
        cout << "[CSV EXPORT -> " << destination << "]\n";
        for (const auto& record : records) {
            cout << "  " << record << endl;
        }
    }

    string processorType() const override {
        return "CSV Processor";
    }

    int recordCount() const override {
        return static_cast<int>(records.size());
    }
};

// --- Concrete Class 2: SensorStreamProcessor ---
class SensorStreamProcessor : public DataProcessor {
private:
    vector<double> readings;
    double meanVal = 0.0;
    double minVal = 0.0;
    double maxVal = 0.0;

public:
    void loadData(const string& source) override {
        // Simulating reading 8 sensor readings
        readings = {23.4, 21.8, 25.1, 22.0, 24.6, 26.2, 21.5, 23.9};
        cout << "[Sensor Stream] Loaded readings from " << source << endl;
    }

    void processData() override {
        if (readings.empty()) return;

        minVal = *min_element(readings.begin(), readings.end());
        maxVal = *max_element(readings.begin(), readings.end());
        double sum = accumulate(readings.begin(), readings.end(), 0.0);
        meanVal = sum / readings.size();
    }

    void exportResult(const string& destination) override {
        cout << "[Sensor Export -> " << destination << "]\n"
             << "  Min: " << minVal << ", Max: " << maxVal << ", Mean: " << meanVal << endl;
    }

    string processorType() const override {
        return "Sensor Stream Processor";
    }

    int recordCount() const override {
        return static_cast<int>(readings.size());
    }
};

// --- Main Program ---
int main() {
    // Verification that attempting to instantiate DataProcessor causes a compile error:
    // DataProcessor dp; // Error: Cannot instantiate abstract class because of pure virtual functions.

    vector<DataProcessor*> pipeline;
    pipeline.push_back(new CSVProcessor());
    pipeline.push_back(new SensorStreamProcessor());

    for (auto* p : pipeline) {
        p->loadData("source_data");
        p->processData();
        p->printSummary();
        p->exportResult("output_dir");
        cout << "---" << endl;
    }

    // Clean up dynamically allocated memory
    for (auto* p : pipeline) {
        delete p;
    }

    return 0;
}