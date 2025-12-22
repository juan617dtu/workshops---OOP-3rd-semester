#include "toy.h"
#include <regex>
#include <iomanip>

namespace seneca {

    std::string Toy::remove_spaces(const std::string& s) {

        // The regex pattern matches:
        // ^\\s+  -> one or more whitespace characters at the beginning of the string
        // |      -> OR
        // \\s+$  -> one or more whitespace characters at the end of the string
        const std::regex pattern(R"(^\s+|\s+$)");
        return std::regex_replace(s, pattern, "");
    }
    void Toy::update(int numItems) {

        m_items_num = numItems;
    }
    Toy::Toy(const std::string &toy) {

        std::string str = remove_spaces(toy);
        std::string id = str.substr(0, str.find(':'));
        id = remove_spaces(id);
        m_id = std::stoi(id);
        size_t first = str.find_first_of(':');
        str.erase(0, first + 1);
        std::string name = str.substr(0, str.find(':'));
        name = remove_spaces(name);
        m_name = name;
        first = str.find_first_of(':');
        str.erase(0, first + 1);
        std::string num = str.substr(0, str.find(':'));
        num = remove_spaces(num);
        m_items_num = std::stoi(num);
        first = str.find_first_of(':');
        std::string price = str.erase(0, first + 1);
        price = remove_spaces(price);
        m_price = std::stod(price);
    }
    std::ostream &operator<<(std::ostream &os, const Toy &toy) {

        std::ios old_state(nullptr);
        old_state.copyfmt(os); //saves stream state
        double subtotal = toy.m_price * toy.m_items_num;
        double tax = subtotal * toy.m_harmonized_sales_tax;
        double total = subtotal + tax;
        os << std::right << std::fixed << std::setprecision(2);
        os << "Toy " << std::setw(8) << std::setfill('0') << toy.m_id << ": "
        << std::setw(24) << std::setfill('.') << toy.m_name << ' '
        << std::setw(2) << std::setfill(' ') << toy.m_items_num << " items @ "
        << std::setw(6) << toy.m_price << "/item  subtotal: "
        << std::setw(7) << subtotal << "  tax: "
        << std::setw(6) << tax << "  total: "
        << std::setw(7) << total << '\n';
        os.copyfmt(old_state); //restores stream state
        return os;
    }

}

