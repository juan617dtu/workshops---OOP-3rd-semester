//
// Created by masti on 1/26/2026.
//

#ifndef SENECA_DIRECTORY_H
#define SENECA_DIRECTORY_H
#include <vector>
#include "Resource.h"

namespace seneca {

    class Directory : public Resource {

        std::vector<Resource*> m_contents;
        template<typename T> bool has_flag_set(std::vector<T>, T flag) const;

    public:

        Directory(const std::string& directory_name);
        void update_parent_path(const std::string& parent_path) override;
        NodeType type() const override;
        std::string path() const override;
        std::string name() const override;
        int count() const override;
        size_t size() const override;
        Directory& operator+=(Resource* resource);
        Resource* find(const std::string& resource_name, const std::vector<OpFlags>& flags = {});
        void remove(const std::string& resource_name, const std::vector<OpFlags>& flags = {});
        void display(std::ostream& os, const std::vector<FormatFlags>& flags = {}) const;
        ~Directory();
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;
        Directory(Directory&&) = delete;
        Directory& operator=(Directory&&) = delete;
    };
}
#endif //SENECA_DIRECTORY_H
