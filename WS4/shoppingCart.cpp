#include <iostream>
#include "shoppingCart.h"

namespace seneca {

    ShoppingCart::ShoppingCart(const std::string &name, int age, const Toy *toys[], size_t count) {

        m_child_name = name;
        m_child_age = age;
        m_toys = nullptr;
        m_qnty = count;
        if (toys && m_qnty > 0) {
            m_toys = new const Toy*[count];
            for (size_t i = 0; i < count; ++i) m_toys[i] = new Toy(*toys[i]);
        }
    }
    ShoppingCart::~ShoppingCart() {

        for (size_t i = 0; i < m_qnty; ++i) delete m_toys[i];
        delete[] m_toys;
    }
    ShoppingCart::ShoppingCart(const ShoppingCart &other) {

        m_child_name = other.m_child_name;
        m_child_age = other.m_child_age;
        m_toys = nullptr;
        m_qnty = other.m_qnty;
        if (other.m_toys && m_qnty > 0) {
            m_toys = new const Toy*[other.m_qnty];
            for (size_t i = 0; i < m_qnty; ++i) m_toys[i] = new Toy(*other.m_toys[i]);
        }
    }
    ShoppingCart &ShoppingCart::operator=(const ShoppingCart &other) {

        if (this != &other) {
            for (size_t i = 0; i < m_qnty; ++i) delete m_toys[i]; //clean up current resources
            delete[] m_toys;
            m_child_name = other.m_child_name; // copy data
            m_child_age = other.m_child_age;
            m_toys = nullptr;
            m_qnty = other.m_qnty;
            if (other.m_toys && m_qnty > 0) {
                m_toys = new const Toy*[other.m_qnty];
                for (size_t i = 0; i < m_qnty; ++i) m_toys[i] = new Toy(*other.m_toys[i]);
            }
        }
        return *this;
    }
    ShoppingCart::ShoppingCart(ShoppingCart &&other) noexcept {

        m_child_name = std::move(other.m_child_name);
        m_child_age = other.m_child_age;
        m_toys = other.m_toys;
        m_qnty = other.m_qnty;
        other.m_toys = nullptr;
        other.m_qnty = 0;
        other.m_child_age = 0;
    }
    ShoppingCart &ShoppingCart::operator=(ShoppingCart &&other) noexcept {

        if (this != &other) {
            for (size_t i = 0; i < m_qnty; ++i) delete m_toys[i];
            delete[] m_toys;
            m_child_name = std::move(other.m_child_name);
            m_child_age = other.m_child_age;
            m_toys = other.m_toys;
            m_qnty = other.m_qnty;
            other.m_toys = nullptr;
            other.m_qnty = 0;
            other.m_child_age = 0;
        }
        return *this;
    }
    std::ostream &operator<<(std::ostream &os, const ShoppingCart &cart) {

        static unsigned int call_count(0);
        call_count++;
        os << "--------------------------\n";
        if (cart.m_toys == nullptr) {
            os << "Order " << call_count << ": This shopping cart is invalid.\n";
        }
        else {
            os << "Order " << call_count << ": Shopping for " << cart.m_child_name << " "
            << cart.m_child_age << " years old ("
            << cart.m_qnty << " toys)\n" << "--------------------------\n";
            if (cart.m_qnty == 0) os << "Empty shopping cart!\n";
            else {
                for (size_t i = 0; i < cart.m_qnty; ++i) os << *cart.m_toys[i];
            }
        }
        os << "--------------------------\n";
        return os;
    }

}
