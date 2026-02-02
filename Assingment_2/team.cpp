#include "team.h"

namespace seneca {

    Team::Team(const char *name) {

        m_name = name;
    }
    Team::Team(const Team &team) {

        if (team.m_characters != nullptr) {
            m_size = team.m_size;
            m_characters = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i) this->m_characters[i] = team.m_characters[i]->clone();
            m_name = team.m_name;
        }
    }
    Team &Team::operator=(const Team &team) {

        if (this != &team) {
            delete[] m_characters;
            m_size = team.m_size;
            m_characters = new Character*[m_size];
            for (size_t i = 0; i < m_size; ++i) this->m_characters[i] = team.m_characters[i]->clone();
            m_name = team.m_name;
        }
        return *this;
    }
    Team::Team(Team &&team) noexcept {

        m_size = team.m_size;
        m_characters = team.m_characters;
        m_name = std::move(team.m_name);
        team.m_characters = nullptr;
        team.m_size = 0;
        team.m_name = "";
    }
    Team &Team::operator=(Team &&team) noexcept {

        if (this != &team) {
            delete[] m_characters;
            m_size = team.m_size;
            m_characters = team.m_characters;
            m_name = std::move(team.m_name);
            team.m_characters = nullptr;
            team.m_size = 0;
            team.m_name = "";
        }
        return *this;
    }
    Team::~Team() {

        for (size_t i = 0; i < m_size; ++i) delete m_characters[i];
    }
    void Team::addMember(const Character *c) {

        if (c != nullptr) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]->getName() == c->getName()) return;
            }
            const size_t new_size = m_size + 1;
            auto** new_character = new Character*[new_size];
            for (size_t i = 0; i < m_size; ++i) new_character[i] = m_characters[i];
            new_character[m_size] = c->clone();
            delete[] m_characters;
            m_characters = new_character; //redirect pointer
            m_size = new_size;
        }
    }
    void Team::removeMember(const std::string &c) {

        if (!c.empty()) {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]->getName() == c) {
                    for (size_t j = i; j < m_size - 1; ++j) m_characters[j] = m_characters[j + 1];
                    m_size--;
                }
            }
        }
    }
    Character *Team::operator[](size_t idx) const {

        if (idx >= m_size) return nullptr;
        return m_characters[idx];
    }
    void Team::showMembers() const {

        if (m_characters != nullptr) {
            std::cout << "[Team] " << m_name << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                if (m_characters[i]) std::cout << "    " << i + 1 << ": " << *m_characters[i] << "\n";
            }
        }
        else std::cout << "No team.\n";
    }

}
