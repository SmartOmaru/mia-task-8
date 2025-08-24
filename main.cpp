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

    // Accessor methods
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