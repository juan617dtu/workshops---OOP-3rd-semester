//
// Created by masti on 1/29/2026.
//

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"

namespace seneca {

    template <typename T>

    class CharacterTpl : public Character {

        int m_healthMax{};
        T m_health{};

    public:

        CharacterTpl(const char* character_name, int max_health) : Character(character_name) {

            m_healthMax = max_health;
            m_health = max_health;
        }
        void takeDamage(int dmg) override {

            m_health -= dmg;
            if (m_health <= 0) {
                m_health = 0;
                std::cout << "    " << getName() << " has been defeated!\n";
            }
            else {
                std::cout << "    " << getName() << " took " << dmg << " damage, "
            << m_health << " health remaining.\n";
            }
        }
        int getHealth() const override {

            return m_health;
        }
        int getHealthMax() const override {

            return m_healthMax;
        }
        void setHealth(int health) override {

            m_health = health;
        }
        void setHealthMax(int health) override {

            m_healthMax = health;
            m_health = health;
        }
    };
}
#endif //SENECA_CHARACTERTPL_H
