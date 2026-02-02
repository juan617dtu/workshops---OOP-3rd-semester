//
// Created by masti on 2/2/2026.
//

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"

namespace seneca {

    class Team {

        std::string m_name{};
        Character** m_characters{};
        size_t m_size{};

    public:

        Team() = default;
        explicit Team(const char* name);
        Team(const Team& team);
        Team& operator=(const Team& team);
        Team(Team&& team) noexcept;
        Team& operator=(Team&& team) noexcept;
        ~Team();
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif //SENECA_TEAM_H
