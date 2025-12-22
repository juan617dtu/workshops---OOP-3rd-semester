//
// Created by masti on 12/19/2025.
//

#ifndef SENECA_SHOPPINGCART_H
#define SENECA_SHOPPINGCART_H
#include <string>
#include "toy.h"

namespace seneca {

    class ShoppingCart {

        std::string m_child_name{};
        unsigned int m_child_age{};
        size_t m_qnty{};
        const Toy** m_toys{}; //is seneca:: necessary?

    public:

        ShoppingCart(const std::string& name, int age, const Toy* toys[], size_t count);
        ~ShoppingCart();
        ShoppingCart(const ShoppingCart& other);
        ShoppingCart& operator=(const ShoppingCart& other);
        ShoppingCart(ShoppingCart&& other) noexcept;
        ShoppingCart& operator=(ShoppingCart&& other) noexcept;
        friend std::ostream& operator<<(std::ostream& os, const ShoppingCart& cart);
    };
}
#endif //SENECA_SHOPPINGCART_H
