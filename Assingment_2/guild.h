#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include "character.h"

namespace seneca {

    class Guild {

        std::string m_name{};
        Character** m_characters{};
        size_t m_size{};

    public:

        Guild() = default;
        explicit Guild(const char* name);
        Guild(const Guild& guild);
        Guild& operator=(const Guild& guild);
        Guild(Guild&& guild) noexcept ;
        Guild& operator=(Guild&& guild) noexcept ;
        ~Guild();
        void addMember(Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t idx) const;
        void showMembers() const;
    };
}
#endif //SENECA_GUILD_H

