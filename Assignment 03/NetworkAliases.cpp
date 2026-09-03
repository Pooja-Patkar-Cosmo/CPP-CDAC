#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

// Type Aliases using 'using'
using Header    = pair<string, string>;
using HeaderList = vector<Header>;
using Port      = unsigned int;
using IPAddress = string;

// Type Alias using 'typedef'
typedef unsigned long long RequestId;

// Function to print all HTTP headers
void printHeaders(const HeaderList& headers) {
    cout << "Headers:" << endl;
    for (const auto& header : headers) {
        cout << "  " << header.first;
        
        // Alignment formatting for key-value pair output
        if (header.first.length() < 15) {
            cout << string(15 - header.first.length(), ' ');
        }
        cout << " : " << header.second << endl;
    }
}

int main() {
    // Variables using the newly defined aliases
    RequestId reqId = 1748293847;
    Port serverPort = 8080;

    // Create a HeaderList with 3 key-value headers
    HeaderList headers = {
        {"Content-Type", "application/json"},
        {"Authorization", "Bearer eyJhbGci..."},
        {"Accept-Language", "en-US"}
    };

    // Output server details
    cout << "Request ID : " << reqId << endl;
    cout << "Server Port : " << serverPort << endl << endl;

    // Call printHeaders
    printHeaders(headers);

    return 0;
}