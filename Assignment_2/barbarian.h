#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "characterTpl.h"

namespace seneca {

    template <typename T, typename Ability_t, typename Weapon_t>

    class Barbarian : public CharacterTpl<T> {

        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability{};
        Weapon_t m_weapon[2];

    public:

        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon,
            Weapon_t secondaryWeapon) : CharacterTpl<T>(name, healthMax) {

            m_baseDefense = baseDefense;
            m_baseAttack = baseAttack;
            m_weapon[0] = primaryWeapon;
            m_weapon[1] = secondaryWeapon;
        }
        int getAttackAmnt() const override {

            return m_baseAttack + (static_cast<double>(m_weapon[0]) / 2 + static_cast<double>(m_weapon[1]) / 2);
        }
        int getDefenseAmnt() const override {

            return m_baseDefense;
        }
        Character* clone() const override {

            return new Barbarian(*this);
        }
        void attack(Character* enemy) override {

            std::cout << CharacterTpl<T>::getName() << " is attacking " << enemy->getName() << ".\n";
            m_ability.useAbility(this);
            int dmg = getAttackAmnt();
            m_ability.transformDamageDealt(dmg);
            std::cout << "    Barbarian deals " << dmg << " melee damage!\n";
            enemy->takeDamage(dmg);
        }
        void takeDamage(int dmg) override {

            std::cout << CharacterTpl<T>::getName() << " is attacked for " << dmg << " damage.\n"
            << "    Barbarian has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";
            int dmg_taken = dmg - getDefenseAmnt();
            if (dmg_taken < 0) dmg_taken = 0;
            m_ability.transformDamageReceived(dmg_taken);
            CharacterTpl<T>::takeDamage(dmg_taken);
        }
    };
}
#endif //SENECA_BARBARIAN_H

