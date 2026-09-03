#include <iostream>
#include <string>

using namespace std;

// Global variable (game difficulty level)
int level = 1;

// Nested namespace
namespace Engine::Audio {
    void playSound(string name) {
        cout << "Playing: " << name << endl;
    }
}

int main() {
    // Local variable (player level) shadowing the global variable
    int level = 5; 

    // Access local variable
    cout << "Player level (local): " << level << endl;

    // Access global variable using the unary scope resolution operator ::
    cout << "Game difficulty level (global): " << ::level << endl;

    // Call the nested namespace function using its full path
    Engine::Audio::playSound("sword_clash");

    return 0;
}