#include <iostream>
#include <string>

using namespace std;

// Part A — enum class for HTTP Status Codes
enum class HttpStatus {
    OK           = 200,
    Created      = 201,
    BadRequest   = 400,
    Unauthorized = 401,
    NotFound     = 404,
    ServerError  = 500
};

// Function to handle and print response based on HTTP status
void handleResponse(HttpStatus status, const string& endpoint) {
    // switch on the underlying integer value using static_cast
    switch (static_cast<int>(status)) {
        case static_cast<int>(HttpStatus::OK):
            cout << "[" << endpoint << "] \t -> 200 OK          : Request successful" << endl;
            break;
        case static_cast<int>(HttpStatus::Created):
            cout << "[" << endpoint << "] \t -> 201 Created     : Resource created successfully" << endl;
            break;
        case static_cast<int>(HttpStatus::BadRequest):
            cout << "[" << endpoint << "] \t -> 400 BadRequest  : Invalid request parameters" << endl;
            break;
        case static_cast<int>(HttpStatus::Unauthorized):
            cout << "[" << endpoint << "] \t -> 401 Unauthorized: Authentication required" << endl;
            break;
        case static_cast<int>(HttpStatus::NotFound):
            cout << "[" << endpoint << "] \t -> 404 Not Found   : Endpoint does not exist" << endl;
            break;
        case static_cast<int>(HttpStatus::ServerError):
            cout << "[" << endpoint << "] \t -> 500 Server Error: Internal server error - retry later" << endl;
            break;
        default:
            cout << "[" << endpoint << "] \t -> Unknown Status Code" << endl;
            break;
    }
}

int main() {
    // Call handleResponse with at least 4 different status codes
    handleResponse(HttpStatus::OK, "GET /api/users");
    handleResponse(HttpStatus::Unauthorized, "POST /api/login");
    handleResponse(HttpStatus::NotFound, "GET /api/products/99");
    handleResponse(HttpStatus::ServerError, "POST /api/order");

    return 0;
}