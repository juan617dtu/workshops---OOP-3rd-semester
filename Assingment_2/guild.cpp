#include "guild.h"

namespace seneca {

    Guild::Guild(const char *name) {

        m_name = name;
    }
    Guild::Guild(const Guild &guild) {

        if (guild.m_characters != nullptr) {
            m_size = guild.m_size;
            m_characters = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i) this->m_characters[i] = guild.m_characters[i]->clone();
            m_name = guild.m_name;
        }
    }
    Guild &Guild::operator=(const Guild &guild) {

        if (this != &guild) {
            delete[] m_characters;
            m_size = guild.m_size;
            m_characters = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i) this->m_characters[i] = guild.m_characters[i]->clone();
            m_name = guild.m_name;
        }
        return *this;
    }
    Guild::Guild(Guild &&guild) noexcept {

        m_name = std::move(guild.m_name);
        m_characters = guild.m_characters;
        m_size = guild.m_size;
        guild.m_characters = nullptr;
        guild.m_name = "";
        guild.m_size = 0;
    }
    Guild &Guild::operator=(Guild &&guild) noexcept {

        if (this != &guild) {
            delete[] m_characters;
            m_size = guild.m_size;
            m_characters = guild.m_characters;
            m_name = std::move(guild.m_name);
            guild.m_characters = nullptr;
            guild.m_name = "";
            guild.m_size = 0;
        }
        return *this;
    }
    Guild::~Guild() {

        delete[] m_characters;
        m_characters = nullptr;
    }
    void Guild::addMember(Character *c) {

        if (c != nullptr) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]->getName() == c->getName()) return;
            }
            const size_t new_size = m_size + 1;
            auto** new_characters = new Character*[new_size];
            for (size_t i = 0; i < m_size; ++i) new_characters[i] = m_characters[i];
            c->setHealthMax(c->getHealthMax() + 300);
            new_characters[m_size] = c;
            delete[] m_characters;
            m_characters = new_characters;
            m_size = new_size;
        }
    }
    void Guild::removeMember(const std::string &c) {

        if (!c.empty()) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]->getName() == c) {
                    m_characters[i]->setHealthMax(m_characters[i]->getHealthMax() - 300);
                    for (size_t j = i; j < m_size - 1; ++j) m_characters[j] = m_characters[j + 1];
                    m_size--;
                }
            }
        }
    }
    Character *Guild::operator[](size_t idx) const {

        if (idx >= m_size) return nullptr;
        return m_characters[idx];
    }
    void Guild::showMembers() const {

        if (m_characters != nullptr) {
            std::cout << "[Guild] " << m_name << '\n';
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]) std::cout << "    " << i + 1 << ": " << *m_characters[i] << '\n';
            }
        }
        else std::cout << "No guild.\n";
    }

}
