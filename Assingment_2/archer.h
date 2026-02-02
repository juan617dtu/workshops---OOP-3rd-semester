//
// Created by masti on 1/30/2026.
//

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include "characterTpl.h"

namespace seneca {

    template <typename Weapon_t>

    class Archer : public CharacterTpl<SuperHealth> {

        double m_baseDefense{};
        double m_baseAttack{};
        Weapon_t m_weapon{};

    public:

        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
        : CharacterTpl(name, healthMax) {

            m_baseDefense = baseDefense;
            m_baseAttack = baseAttack;
            m_weapon = weapon;
        }
        int getAttackAmnt() const override {

            return m_baseAttack * 1.3;
        }
        int getDefenseAmnt() const override {

            return m_baseDefense * 1.2;
        }
        Character* clone() const override {

            return new Archer(*this);
        }
        void attack(Character* enemy) override {

            std::cout << getName() << " is attacking " << enemy->getName() << ".\n";
            const int dmg = getAttackAmnt();
            std::cout << "Archer deals " << dmg << ' ranged damage!\n';
            enemy->takeDamage(dmg);
        }
        void takeDamage(int dmg) override {

            std::cout << getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";
            int dmg_taken = dmg - getDefenseAmnt();
            if (dmg_taken < 0) dmg_taken = 0;
            CharacterTpl::takeDamage(dmg_taken);
        }
    };
}
#endif //SENECA_ARCHER_H
