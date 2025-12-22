//
// Created by masti on 12/19/2025.
//

#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#define HST 0.13
#include <string>

namespace seneca {

    class Toy {

        unsigned int m_id{};
        std::string m_name{};
        int m_items_num{};
        double m_price{};
        double m_harmonized_sales_tax = HST;

    public:
        Toy() = default;
        void update(int numItems);
        //function to trim leading and trailing whitespace from a string
        static std::string remove_spaces(const std::string& s);
        explicit Toy(const std::string& toy);
        friend std::ostream& operator<<(std::ostream& os, const Toy& toy);
    };
}
#endif //SENECA_TOY_H
