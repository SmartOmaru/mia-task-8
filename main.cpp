#include <iostream>
#include <string>
using namespace std;

class Character {

private:
    int health = 100;
    string name;
    bool current_turn;

public:
    Character(string name, bool turn = false, int health = 100) 
    : name(name), current_turn(turn), health(health) {}

    // Getter methods
    int current_health() const { return health; }
    string get_name() const { return name; }
    bool is_turn() const { return current_turn; }
    bool is_alive() const { return health > 0; }

    // Method to take damage and decrease health accordingly
    void take_damage(int damage_taken = 0) { 
        health -= damage_taken;
        if (health < 0) health = 0;
    }
};

class Weapons {

private:
    string name;
    int damage;
    float accuracy;
    string description;

public:
    Weapons(string name, int damage, float accuracy, string description)
    : name(name), damage(damage), accuracy(accuracy), description(description) {}

    // Getter methods
    string get_name() const { return name; }
    int get_damage() const { return damage; }
    float get_accuracy() const { return accuracy; }
    string get_description() const { return description; }
    

    // Method to see if the attack hits the target
    bool attempt_hit(const Weapons& weapon) const {
        // Simple hit chance calculation (could be improved)
        return (rand() % 100) < (weapon.get_accuracy() * 100);
    }
};