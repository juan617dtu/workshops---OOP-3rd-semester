//
// Created by masti on 1/30/2026.
//

#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"
#include "weapons.h"

namespace seneca {

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>

    class Rogue : public CharacterTpl<T> {

        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility{};
        SecondAbility_t m_secondAbility{};
        Dagger m_weapon{};

    public:

        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense) : CharacterTpl<T>(name, healthMax){

            m_baseDefense = baseDefense;
            m_baseAttack = baseAttack;
        }
        int getAttackAmnt() const override {

            return m_baseAttack + 2 * m_weapon.m_damage;
        }
        int getDefenseAmnt() const override {

            return m_baseDefense;
        }
        Character* clone() const override {

            return new Rogue(*this);
        }
        void attack(Character* enemy) override {

            std::cout << CharacterTpl<T>::getName() << " is attacking " << enemy->getName() << ".\n";
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            int dmg = getDefenseAmnt();
            m_firstAbility.transformDamageDealt(dmg);
            m_secondAbility.transformDamageDealt(dmg);
            std::cout << "    Rogue deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }
        void takeDamage(int dmg) override {

            std::cout << CharacterTpl<T>::getName() << " is attacked for " << dmg << " damage.\n"
            << "    Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";
            int dmg_taken = dmg - getDefenseAmnt();
            if (dmg_taken < 0) dmg_taken = 0;
            m_firstAbility.transformDamageReceived(dmg_taken);
            m_secondAbility.transformDamageReceived(dmg_taken);
            CharacterTpl<T>::takeDamage(dmg_taken);
        }
    };
}
#endif //SENECA_ROGUE_H
