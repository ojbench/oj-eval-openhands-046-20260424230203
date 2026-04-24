
#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    //uncompleted, you should add code into this class
    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        //WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health,attack;
        bool alive,defensive;
        //you only need to define aliveNumber here.
        static int aliveNumber;
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED（实例化）.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        //the function you need to implement or define is as follows.
        //(1) getAliveNumber
        //(2) Constructor
        //(3) launch_attack
        //(4) defend
        Base(const std::string& name, const int health, const int attack) : name(name), health(health), attack(attack), alive(true), defensive(false) {
            aliveNumber++;
        }

        virtual ~Base() {
            if (alive) {
                aliveNumber--;
            }
        }

        static int getAliveNumber() {
            return aliveNumber;
        }

        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }

        virtual void launch_attack(Base* target) = 0;

        virtual void defend(bool flag) = 0;
    };

    // Initialize static member
    int Base::aliveNumber = 0;

    class Fighter:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target) override;

        void defend(bool flag) override {
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        // Fighter deals double damage to Caster
        int damageMultiplier = 1;
        if (dynamic_cast<Caster*>(target)) {
            damageMultiplier = 2;
        }

        int damage = attack * damageMultiplier;
        
        // If target is defending, reduce damage by target's attack
        if (target->isDefensive()) {
            damage = std::max(0, damage - target->attack);
            // Attacker takes counter damage unless attacker is Caster
            if (dynamic_cast<Caster*>(this) == nullptr) {
                health -= target->attack;
            }
        }

        // Apply damage to target
        target->health -= damage;
        
        // Check if target is killed
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            // Output the correct class name of the target
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed" << std::endl;
            }
        }
    }

    void Protector::launch_attack(Base *target) {
        // Protector deals double damage to Fighter
        int damageMultiplier = 1;
        if (dynamic_cast<Fighter*>(target)) {
            damageMultiplier = 2;
        }

        int damage = attack * damageMultiplier;
        
        // If target is defending, reduce damage by target's attack
        if (target->isDefensive()) {
            damage = std::max(0, damage - target->attack);
            // Attacker takes counter damage unless attacker is Caster
            if (dynamic_cast<Caster*>(this) == nullptr) {
                health -= target->attack;
            }
        }

        // Apply damage to target
        target->health -= damage;
        
        // Check if target is killed
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            // Output the correct class name of the target
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed" << std::endl;
            }
        }
    }

    void Caster::launch_attack(Base *target) {
        // Caster deals double damage to Protector
        int damageMultiplier = 1;
        if (dynamic_cast<Protector*>(target)) {
            damageMultiplier = 2;
        }

        int damage = attack * damageMultiplier;
        
        // If target is defending, reduce damage by target's attack
        if (target->isDefensive()) {
            damage = std::max(0, damage - target->attack);
            // Caster doesn't take counter damage
        }

        // Apply damage to target
        target->health -= damage;
        
        // Check if target is killed
        if (target->health <= 0 && target->alive) {
            target->alive = false;
            // Output the correct class name of the target
            if (dynamic_cast<Fighter*>(target)) {
                std::cout << "Fighter " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Protector*>(target)) {
                std::cout << "Protector " << target->name << " is killed" << std::endl;
            } else if (dynamic_cast<Caster*>(target)) {
                std::cout << "Caster " << target->name << " is killed" << std::endl;
            }
        }
    }

}
#endif //ROLE_HPP
