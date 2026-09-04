#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Shader {
private:
    string name;
    string type;

public:
    // Constructor
    Shader(string name, string type)
        : name(move(name)), type(move(type)) {
        cout << "[Shader Compiled]" << endl;
    }

    // Destructor
    ~Shader() {
        cout << "[Shader Destroyed]" << endl;
    }

    // Helper method to return reference count via shared_ptr passed as parameter
    int getReferenceCount(const shared_ptr<Shader>& ptr) const {
        return ptr.use_count();
    }
};

int main() {
    // 1. Create a Shader using make_shared
    auto shader = make_shared<Shader>("main_vert", "vertex");
    cout << "Ref count: " << shader.use_count() << endl; // 1

    {
        // 2 & 3. Assign to two more variables inside block and print ref count
        auto rendererRef = shader;
        cout << "Ref count: " << shader.use_count() << endl; // 2

        auto editorRef = shader;
        cout << "Ref count: " << shader.use_count() << endl; // 3
    }

    // 4. Scope block ends — rendererRef and editorRef go out of scope and release their references
    cout << "Ref count: " << shader.use_count() << endl; // 1

    return 0;
}