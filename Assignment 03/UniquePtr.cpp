#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Texture {
private:
    string name;
    int width;
    int height;

public:
    // Constructor
    Texture(string name, int width, int height)
        : name(move(name)), width(width), height(height) {
        cout << "[Texture Loaded]" << endl;
    }

    // Destructor
    ~Texture() {
        cout << "[Texture Released]" << endl;
    }

    // Method to display dimensions
    void display() const {
        cout << "Texture: " << name << " (" << width << "x" << height << ")" << endl;
    }
};

int main() {
    // 1. Create a Texture using make_unique
    auto tex1 = make_unique<Texture>("player_sprite", 512, 512);

    // 2. Call display() through the unique_ptr
    tex1->display();

    // 3. Attempt to copy the unique_ptr (commented out with required explanation)
    // unique_ptr<Texture> tex2 = tex1; // Error: unique_ptr copy constructor is deleted to enforce exclusive ownership.

    // 4. Transfer ownership to a second unique_ptr using move()
    unique_ptr<Texture> tex2 = move(tex1);

    // Verify the first pointer is now nullptr
    cout << "tex1 is null: " << (tex1 == nullptr ? "YES" : "NO") << endl;

    // 5. Let it go out of scope — destructor is automatically invoked when main ends
    return 0;
}