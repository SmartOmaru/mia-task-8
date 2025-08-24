#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
    bool attempt_hit(int chance_increase = 0) const {
        // Simple hit chance calculation (could be improved)
        return (rand() % 100) < (accuracy * (100 + chance_increase));
    }
};

class Character {

private:
    int health = 100;
    string name;
    bool current_turn;
    vector<Weapons> arsenal;

protected:
    vector<Weapons>& get_arsenal() { return arsenal; }
    const vector<Weapons>& get_arsenal() const { return arsenal; }

public:
    Character(string name, bool turn = false, int health = 100, vector<Weapons> arsenal)
    : name(name), current_turn(turn), health(health), arsenal(arsenal) {}

    // Getter methods
    int get_health() const { return health; }
    string get_name() const { return name; }
    bool is_turn() const { return current_turn; }
    bool is_alive() const { return health > 0; }

    // Method to take damage and decrease health accordingly
    void take_damage(int damage_taken = 0) { 
        health -= damage_taken;
        if (health < 0) health = 0;
    }

    // Virtual method for attacking depending on character (polymorphism)
    virtual void attack(Character& target) = 0;
};

class Autobot : public Character {

public:
    Autobot(string name, bool turn = false, int health = 100, vector<Weapons> arsenal)
    : Character(name, turn, health, arsenal) {}

    void attack(Character& target) override {
        int chance_increase = 0;
        Weapons& weapon = get_arsenal()[rand() % get_arsenal().size()];

        // Roll for a special mode that increases chance to hit (chance is inversely proportional with health)
        if (rand() % 100 < (100.0 / get_health())) {
            cout << get_name() << " is in last stand mode!" << endl;
            chance_increase = 20;  // Increase chance by 20%
        }

        if (weapon.attempt_hit(chance_increase)) {
            target.take_damage(weapon.get_damage());
            cout << get_name() << " attacks " << target.get_name() << " with " << weapon.get_name()
                 << " for " << weapon.get_damage() << " damage!" << endl;
        } else {
            cout << get_name() << " missed the attack on " << target.get_name() << "!" << endl;
        }
    }
};

class Decepticon : public Character {

public:
    Decepticon(string name, bool turn = false, int health = 100, vector<Weapons> arsenal)
    : Character(name, turn, health, arsenal) {}

    void attack(Character& target) override {
        int damage_increase = 0;
        Weapons& weapon = get_arsenal()[rand() % get_arsenal().size()];

        // Roll for a special mode that increases damage (chance is inversely proportional with health)
        if (rand() % 100 < (100.0 / get_health())) {
            cout << get_name() << " is in all out mode!" << endl;
            damage_increase = static_cast<int>(weapon.get_damage() * 0.2);  // Increase damage by 20%
        }

        if (weapon.attempt_hit()) {
            target.take_damage(weapon.get_damage() + damage_increase);
            cout << get_name() << " attacks " << target.get_name() << " with " << weapon.get_name()
                 << " for " << weapon.get_damage() + damage_increase << " damage!" << endl;
        } else {
            cout << get_name() << " missed the attack on " << target.get_name() << "!" << endl;
        }
    }
};
