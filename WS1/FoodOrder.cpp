#include "FoodOrder.h"
#include <string.h>
#include <iostream>
#include <iomanip>

double g_dailydiscount = 0.0;
double g_taxrate = 0.0;

namespace seneca {

    void FoodOrder::read(std::istream& is) {

        if (is) {
            is.getline(m_customer_name, 10, ',');
            if (m_food_desc) delete [] m_food_desc;
            std::string buffer;
            getline(is, buffer, ',');
            m_food_desc = new char[buffer.length() + 1];
            strcpy(m_food_desc, buffer.c_str());
            is >> m_food_price;
            char temp = 'N';
            is.ignore();
            is >> temp;
            if (temp == 'N') m_is_daily_special = false;
            else m_is_daily_special = true;
        }
    }
    void FoodOrder::display() const {

        static size_t count = 0;
        std::cout << std::left << std::setw(2) << ++count << ". ";
        if (m_customer_name[0]) {
            std::cout << std::setw(10) << m_customer_name << '|'
            << std::setw(25) << m_food_desc << '|'
            << std::fixed << std::setw(12) << std::setprecision(2)
            << m_food_price + (m_food_price * g_taxrate) << '|';
            if (m_is_daily_special) {
                std::cout << std::right << std::setw(13) <<std::setprecision(2)
                << (m_food_price + (m_food_price * g_taxrate)) - g_dailydiscount;
            }
        }
        else { std::cout << "No Order"; }
        std::cout << '\n';
    }
    FoodOrder::~FoodOrder() {

        delete [] m_food_desc;
        m_food_desc = nullptr;
    }
    FoodOrder::FoodOrder(const FoodOrder &other) {

        *this = other;
    }
    FoodOrder &FoodOrder::operator=(const FoodOrder &other) {

        if (this != &other) {
            delete [] m_food_desc;
            m_food_desc = nullptr;
            strcpy(m_customer_name, other.m_customer_name);
            m_food_price = other.m_food_price;
            m_is_daily_special = other.m_is_daily_special;
            if (other.m_food_desc) {
                m_food_desc = new char[strlen(other.m_food_desc) + 1];
                strcpy(m_food_desc, other.m_food_desc);
            }
        }
        return *this;
    }
}

