#include <iostream>

using namespace std; // Using std namespace for cin/cout

// --- Physics Namespace ---
namespace Physics {
    // Clamps a velocity value (double) between min and max
    double clamp(double val, double min, double max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    // Linear interpolation for physics
    double lerp(double a, double b, double t) {
        return a + t * (b - a);
    }
}

// --- GameMath Namespace ---
namespace GameMath {
    // Clamps an integer stat (e.g., health, level) between min and max
    int clamp(int val, int min, int max) {
        if (val < min) return min;
        if (val > max) return max;
        return val;
    }

    // Lerp for UI animations
    double lerp(double a, double b, double t) {
        return a + t * (b - a);
    }
}

int main() {
    // 1. Direct scope resolution calls (as required)
    cout << "--- Calling using scope resolution operator (::) ---" << endl;
    double velocity = Physics::clamp(120.5, 0.0, 100.0);
    int health = GameMath::clamp(-15, 0, 100);

    cout << "Physics clamped velocity: " << velocity << endl;
    cout << "GameMath clamped health: " << health << endl;

    cout << "\n--- Demonstrating using namespace in block scope ---" << endl;

    // 2. Demonstration of 'using namespace' in a limited block scope for Physics
    {
        using namespace Physics;
        // Calls Physics::clamp and Physics::lerp directly without Physics:: prefix
        cout << "[Physics Scope] Clamped velocity: " << clamp(45.0, 0.0, 50.0) << endl;
        cout << "[Physics Scope] Lerp result: " << lerp(0.0, 10.0, 0.5) << endl;
    }

    // 3. Demonstration of 'using namespace' in a limited block scope for GameMath
    {
        using namespace GameMath;
        // Calls GameMath::clamp and GameMath::lerp directly without GameMath:: prefix
        cout << "[GameMath Scope] Clamped health: " << clamp(150, 0, 100) << endl;
        cout << "[GameMath Scope] Lerp result: " << lerp(0.0, 100.0, 0.25) << endl;
    }

    return 0;
}