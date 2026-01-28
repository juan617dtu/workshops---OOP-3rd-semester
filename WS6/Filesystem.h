#ifndef SENECA_FILESYSTEM_H
#define SENECA_FILESYSTEM_H
#include "Directory.h"

namespace seneca {

    class Filesystem {

        Directory* m_root{};
        Directory* m_current{};
        std::string trim(const std::string& str);

    public:

        Filesystem(const char* file_name, const std::string& root_directory = "");
        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem(Filesystem&& other) noexcept;
        Filesystem& operator=(Filesystem&& other) noexcept;
        Filesystem& operator+=(Resource* res);
        Directory* change_directory(const std::string& dir_name = "");
        Directory* get_current_directory() const;
        ~Filesystem();
    };
}
#endif //SENECA_FILESYSTEM_H

