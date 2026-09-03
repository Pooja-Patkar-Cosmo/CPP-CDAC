#include <iostream>
#include <string>

using namespace std;

class Entity {
private:
    string name;
    int health;
    int level;
    string type;

public:
    // Default Constructor using a Member Initializer List
    Entity() : name(""), health(0), level(1), type("Unknown") {}

    // --- Setters returning Entity& using `this` for method chaining ---
    Entity& setName(const string& name) {
        this->name = name;
        return *this;
    }

    Entity& setHealth(int health) {
        this->health = health;
        return *this;
    }

    Entity& setLevel(int level) {
        this->level = level;
        return *this;
    }

    Entity& setType(const string& type) {
        this->type = type;
        return *this;
    }

    // --- Getters (marked const) ---
    string getName() const {
        return this->name;
    }

    int getHealth() const {
        return this->health;
    }

    int getLevel() const {
        return this->level;
    }

    string getType() const {
        return this->type;
    }

    // Display entity details
    void displayInfo() const {
        cout << "[" << type << "] " 
             << "Name: " << name 
             << " | Health: " << health 
             << " | Level: " << level << endl;
    }
};

int main() {
    // Create 3 entities using method chaining
    Entity player, enemy, item;

    player.setName("Aragorn").setHealth(100).setLevel(10).setType("Player");
    enemy.setName("Orc").setHealth(60).setLevel(5).setType("Enemy");
    item.setName("HealthPotion").setHealth(0).setLevel(1).setType("Item");

    // Output information to verify
    cout << "--- Entity Details ---" << endl;
    player.displayInfo();
    enemy.displayInfo();
    item.displayInfo();

    return 0;
}