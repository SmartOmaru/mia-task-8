#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Weapons
{

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
    bool attempt_hit(int chance_increase = 0) const
    {
        // Simple hit chance calculation (could be improved)
        int roll = rand() % 100;
        int chance = static_cast<int>(accuracy * 100) + chance_increase;
        if (chance > 100)
            chance = 100;
        return roll < chance;
    }
};

class Character
{

private:
    int health = 100;
    string name;
    bool current_turn;
    vector<Weapons> arsenal;

protected:
    vector<Weapons> &get_arsenal() { return arsenal; }
    const vector<Weapons> &get_arsenal() const { return arsenal; }

public:
    Character(string name, bool turn = false, int health = 100, vector<Weapons> arsenal = {})
        : name(name), current_turn(turn), health(health), arsenal(arsenal) {}

    // Getter methods
    int get_health() const { return health; }
    string get_name() const { return name; }
    bool is_turn() const { return current_turn; }
    bool is_alive() const { return health > 0; }

    // Setter method
    void set_turn(bool turn) { current_turn = turn; }

    // Method to take damage and decrease health accordingly
    void take_damage(int damage_taken = 0)
    {
        health -= damage_taken;
        if (health < 0)
            health = 0;
    }

    // Virtual method for attacking depending on character (polymorphism)
    virtual void attack(Character &target) = 0;
};

class Autobot : public Character
{

public:
    Autobot(string name, bool turn = false, int health = 100, vector<Weapons> arsenal = {})
        : Character(name, turn, health, arsenal) {}

    void attack(Character &target) override
    {
        int damage_increase = 0;

        // Weapon choosing logic
        // Autobots will choose lower accuracy weapons (since they have higher accuracy) when low on health
        Weapons weapon = get_arsenal()[rand() % get_arsenal().size()];
        if (get_health() < 50)
        {
            // Choose a weapon with lower accuracy
            sort(get_arsenal().begin(), get_arsenal().end(),
                 [](const Weapons &a, const Weapons &b)
                 {
                     return a.get_accuracy() > b.get_accuracy();
                 });

            weapon = get_arsenal().front();
        }

        // Roll for a special mode that increases chance to hit (chance is inversely proportional with health)
        int chance = (100 - get_health()) / 2;
        if (rand() % 100 < chance)
        {
            cout << get_name() << " is in last stand mode!" << endl;
            damage_increase = static_cast<int>(weapon.get_damage() * 0.2); // Increase damage by 20%
        }

        if (weapon.attempt_hit())
        {
            target.take_damage(weapon.get_damage() + damage_increase);
            cout << get_name() << " attacks " << target.get_name() << " with " << weapon.get_name()
                 << " for " << weapon.get_damage() + damage_increase << " damage!" << endl;
        }
        else
        {
            cout << get_name() << " missed the attack on " << target.get_name() << "!" << endl;
        }
    }
};

class Decepticon : public Character
{

public:
    Decepticon(string name, bool turn = false, int health = 100, vector<Weapons> arsenal = {})
        : Character(name, turn, health, arsenal) {}

    void attack(Character &target) override
    {
        int chance_increase = 0;

        // Weapon choosing logic
        // Decpticons will choose lower accuracy weapons (since they have higher damage) when low on health
        Weapons weapon = get_arsenal()[rand() % get_arsenal().size()];
        if (get_health() < 50)
        {
            // Choose a weapon with lower accuracy
            sort(get_arsenal().begin(), get_arsenal().end(),
                 [](const Weapons &a, const Weapons &b)
                 {
                     return a.get_accuracy() < b.get_accuracy();
                 });

            weapon = get_arsenal().front();
        }

        // Roll for a special mode that increases damage (chance is inversely proportional with health)
        int chance = (100 - get_health()) / 2;
        if (rand() % 100 < chance)
        {
            cout << get_name() << " is in all out mode!" << endl;
            chance_increase = 20; // Increase chance by 20%
        }

        if (weapon.attempt_hit(chance_increase))
        {
            target.take_damage(weapon.get_damage());
            cout << get_name() << " attacks " << target.get_name() << " with " << weapon.get_name()
                 << " for " << weapon.get_damage() << " damage!" << endl;
        }
        else
        {
            cout << get_name() << " missed the attack on " << target.get_name() << "!" << endl;
        }
    }
};

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned>(time(0)));

    // Create weapon arsenals
    vector<Weapons> Optimus_weapons = {
        Weapons("Ion Rifle", 6, 1, "Optimus Prime’s signature energy rifle"),
        Weapons("Energon Swords", 12, 0.8, "Twin forearm-mounted energy blades"),
        Weapons("Shoulder Cannon", 45, 0.25, "High-powered plasma launcher mounted on Optimus’s shoulder")};

    vector<Weapons> Megatron_weapons = {
        Weapons("Fusion Cannon", 9, 0.9, "Megatron’s signature arm-mounted weapon"),
        Weapons("Fusion Sword", 18, 0.7, "A massive Cybertronian blade used in brutal close combat"),
        Weapons("Tank Mode", 60, 0.15, "His alternate form transforms into a heavily armored tank")};

    // Create characters
    Autobot Optimus("Optimus Prime", true, 100, Optimus_weapons);
    Decepticon Megatron("Megatron", false, 100, Megatron_weapons);

    // Main game loop
    while (Optimus.is_alive() && Megatron.is_alive()) {
        if (Optimus.is_turn()) {
            Optimus.attack(Megatron);
            Optimus.set_turn(false);
            Megatron.set_turn(true);
        } else {
            Megatron.attack(Optimus);
            Megatron.set_turn(false);
            Optimus.set_turn(true);
        }
        if (Optimus.is_alive() && Megatron.is_alive()) {
            cout << "----------------------------------------" << endl;
            cout << Optimus.get_name() << " Health: " << Optimus.get_health() << endl;
            cout << Megatron.get_name() << " Health: " << Megatron.get_health() << endl;
            cout << "----------------------------------------" << endl;
        }
        if (!Optimus.is_alive()) {
            cout << "Megatron wins!" << endl;
            break;
        } else if (!Megatron.is_alive()) {
            cout << "Optimus Prime wins!" << endl;
            break;
        }
    }

    return 0;
}