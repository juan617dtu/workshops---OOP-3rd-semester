#ifndef SENECA_CONFIRMATIONORDER_H
#define SENECA_CONFIRMATIONORDER_H
#include "toy.h"
#include <string>

namespace seneca {

    class ConfirmationOrder {

        const Toy** m_toy{};
        size_t m_quantity{};

    public:
        ConfirmationOrder() = default;
        ~ConfirmationOrder();
        ConfirmationOrder(const ConfirmationOrder& other);
        ConfirmationOrder& operator=(const ConfirmationOrder& other);
        ConfirmationOrder(ConfirmationOrder&& other) noexcept;
        ConfirmationOrder& operator=(ConfirmationOrder&& other) noexcept;
        ConfirmationOrder& operator+=(const Toy& toy);
        ConfirmationOrder& operator-=(const Toy& toy);
        friend std::ostream& operator<<(std::ostream& os, const ConfirmationOrder& order);
    };
}
#endif //SENECA_CONFIRMATIONORDER_H

