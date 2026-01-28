#include "Filesystem.h"
#include "File.h"
#include <fstream>
#include <regex>

namespace seneca {

    std::string Filesystem::trim(const std::string &str) {

        const std::regex pattern(R"(^\s+|\s+$)");
        // ^\\s+ matches one or more whitespace characters at the beginning of the string
        // | separates the leading and trailing patterns (OR operator)
        // \\s+$ matches one or more whitespace characters at the end of the string
        return std::regex_replace(str, pattern, "");
    }
    Filesystem::Filesystem(const char *file_name, const std::string& root_directory) {

        std::ifstream file(file_name);
        m_root = new Directory(root_directory);
        m_current = m_root;
        if (!file.is_open()) {
            throw std::string("Error opening file");
        }
        std::string line, path;
        while (std::getline(file, line)) {
            if (const size_t path_terminator = line.find('|'); path_terminator != std::string::npos) {
                path = trim(line.substr(0, path_terminator));
                line = trim(line.substr(path_terminator + 1));
            }
            else path = trim(line);
            Directory* current = m_root;
            while (!path.empty()) {
                const size_t separator = path.find('/');
                Resource* resource;
                if (separator != std::string::npos) {
                    std::string name = trim(path.substr(0, separator) + '/');
                    resource = current->find(name);
                    if (!resource) {
                        resource = new Directory(name);
                        resource->update_parent_path(current->path());
                        *current += resource;
                    }
                    auto* directory = dynamic_cast<Directory*>(resource);
                    if (!directory) throw std::invalid_argument(name + " is not a directory!");
                    current = directory;
                    path.erase(0, separator + 1);
                }
                else {
                    resource = new File(path, line);
                    resource->update_parent_path(current->path());
                    *current += resource;
                    path.erase();
                }
            }
        }
    }
    Filesystem::Filesystem(Filesystem &&other) noexcept{

        *this = std::move(other);
    }
    Filesystem &Filesystem::operator=(Filesystem &&other) noexcept {

        if (this != &other) {
            delete m_root;
            m_root = nullptr;
            /*delete m_current; Filesystem owns only the root
            m_current = nullptr;*/
            m_root = other.m_root;
            m_current = other.m_current;
            other.m_current = nullptr;
            other.m_root = nullptr;
        }
        return *this;
    }
    Filesystem &Filesystem::operator+=(Resource *res) {

        *m_current += res;
        return *this;
    }
    Directory *Filesystem::change_directory(const std::string &dir_name) {

        if (dir_name.empty()) {
            m_current = m_root;
            return m_current;
        }
        Resource* resource = m_current->find(dir_name);
        if (!resource) throw std::invalid_argument("Cannot change directory! " + dir_name + " not found!");
        auto* directory = dynamic_cast<Directory*>(resource);
        if (!directory) throw std::invalid_argument(dir_name + " is not a directory!");
        m_current = directory;
        return m_current;
    }
    Directory *Filesystem::get_current_directory() const {

        return m_current;
    }
    Filesystem::~Filesystem() {

        delete m_root;
        m_root = nullptr;
    }
}
