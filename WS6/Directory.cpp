//Program arguments: ws filesystem.txt
#include "Directory.h"
#include <iomanip>

namespace seneca {

    Directory::Directory(const std::string& directory_name) {

        m_name = directory_name;
    }
    void Directory::update_parent_path(const std::string &parent_path) {

        m_parent_path = parent_path;
    }
    NodeType Directory::type() const {

        return NodeType::DIR;
    }
    std::string Directory::path() const {

        return m_parent_path + m_name;
    }
    std::string Directory::name() const {

        return m_name;
    }
    int Directory::count() const {

        return m_contents.size();
    }
    size_t Directory::size() const {

        size_t size = 0u;
        for (const auto& content : m_contents) size += content->size();
        return size;
    }
    Directory &Directory::operator+=(Resource *resource) {

        for (const auto& content : m_contents) {
            if (content == resource) throw std::logic_error{"Resource already exists"};
        }
        m_contents.emplace_back(resource);
        return *this;
    }
    template<typename T> bool Directory::has_flag_set(std::vector<T> flags, T flag) const {

        for (const auto& f : flags) {
            if (flag == f) return true;
        }
        return false;
    }
    Resource *Directory::find(const std::string &resource_name, const std::vector<OpFlags> &flags) {

        bool recursive = has_flag_set(flags, OpFlags::RECURSIVE);
        for (const auto& content : m_contents) {
            auto* directory = dynamic_cast<Directory*>(content);
            if (resource_name == content->name()) return content;
            if (content -> type() == NodeType::DIR and recursive) {
                Resource *res = directory->find(resource_name, flags);
                if (res) return res;
            }
        }
        return nullptr;
    }
    void Directory::remove(const std::string &resource_name, const std::vector<OpFlags> &flags) {

        bool recursive = has_flag_set(flags, OpFlags::RECURSIVE);
        for (auto it = m_contents.begin(); it != m_contents.end(); ++it) {
            Resource *resource = *it;
            if (resource->name() == resource_name) {
                if (resource->type() == NodeType::DIR and !recursive) {
                    throw std::invalid_argument{resource_name +
                    "is a directory. Pass the recursive flag to delete directories."};
                }
                delete resource;
                m_contents.erase(it);
                return;
            }
        }
        throw std::string{resource_name + " does not exist in " + name()};
    }
    void Directory::display(std::ostream &os, const std::vector<FormatFlags> &flags) const {

        bool long_format = has_flag_set(flags, FormatFlags::LONG);
        os << "Total size: " << size() << " bytes\n";
        for (const auto& content : m_contents) {
            if (content->type() == NodeType::DIR) os << "D | ";
            else if (content->type() == NodeType::FILE) os << "F | ";
            os << std::left << std::setw(15) << content->name() << " |";
            if (long_format) {
                os << " " << std::right << std::setw(2)
                << (content->count() < 0 ? "" : std::to_string(content->count())) << " | "
                << std::setw(10) << std::to_string(content->size()) + " bytes" << " | ";
            }
            os << '\n';
        }
    }
    Directory::~Directory() {

        for (auto& content : m_contents) {
            delete content;
            content = nullptr;
        }
    }
}



