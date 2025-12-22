//
// Created by masti on 12/22/2025.
//

#include "confirmationOrder.h"
#include <iostream>

namespace seneca {

    ConfirmationOrder::ConfirmationOrder(const ConfirmationOrder &other) {

        m_quantity = other.m_quantity;
        if (m_quantity > 0) {
            m_toy = new const Toy *[m_quantity];
            for (size_t i = 0; i < m_quantity; ++i) m_toy[i] = other.m_toy[i]; //copy address only
        }
    }
    ConfirmationOrder &ConfirmationOrder::operator=(const ConfirmationOrder &other) {

        if (this != &other) {
            delete[] m_toy;
            m_quantity = other.m_quantity;
            m_toy = nullptr;
            if (m_quantity > 0) {
                m_toy = new const Toy*[m_quantity];
                for (size_t i = 0; i < m_quantity; ++i) m_toy[i] = other.m_toy[i]; //adress copy only
            }
            else { m_toy = nullptr; }
        }
        return *this;
    }
    ConfirmationOrder::ConfirmationOrder(ConfirmationOrder &&other) noexcept {

        *this = std::move(other);
    }
    ConfirmationOrder &ConfirmationOrder::operator=(ConfirmationOrder &&other) noexcept {

        if (this != &other) {
            delete[] m_toy;
            m_quantity = other.m_quantity;
            m_toy = other.m_toy;
            other.m_quantity = 0;
            other.m_toy = nullptr;
        }
        return *this;
    }
    ConfirmationOrder::~ConfirmationOrder() {

        delete[] m_toy;
        m_toy = nullptr;
    }
    ConfirmationOrder &ConfirmationOrder::operator+=(const Toy &toy) {

        for (size_t i = 0; i < m_quantity; ++i) {
            if (&toy == m_toy[i]) return *this;
        }
        const auto new_array = new const Toy*[m_quantity + 1];
        for (size_t i = 0; i < m_quantity; ++i) new_array[i] = m_toy[i];
        new_array[m_quantity] = &toy;
        delete[] m_toy;
        m_toy = new_array;
        m_quantity++;
        return *this;
    }
    ConfirmationOrder &ConfirmationOrder::operator-=(const Toy &toy) {

        size_t index{};
        bool found = false;
        for (size_t i = 0; i < m_quantity; ++i) {
            if (&toy == m_toy[i]) {
                found = true;
                index = i;
                break;
            }
        }
        if (!found) return *this;
        for (size_t i = index; i < m_quantity - 1; ++i) m_toy[i] = m_toy[i + 1];
        m_quantity--;
        if (m_quantity > 0) {
            const auto new_array = new const Toy*[m_quantity];
            for (size_t i = 0; i < m_quantity; ++i) new_array[i] = m_toy[i];
            delete[] m_toy;
            m_toy = new_array;
        }
        else {
            delete[] m_toy;
            m_toy = nullptr;
        }
        return *this;
    }
    std::ostream &operator<<(std::ostream &os, const ConfirmationOrder &order) {

        os << "--------------------------\nConfirmations to Send (" << order.m_quantity
        << " toys)\n--------------------------\n";
        if (order.m_quantity > 0) {
            for (size_t i = 0; i < order.m_quantity; ++i) {
                os << *order.m_toy[i];
            }
        }
        else { os << "There are no confirmations to send!\n";}
        os << "--------------------------\n";
        return os;
    }

}