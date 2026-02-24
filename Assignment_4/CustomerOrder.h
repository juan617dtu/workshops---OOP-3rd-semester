#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
#include <iostream>
#include <string>
#include <utility>

namespace seneca {

    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(std::string  src) : m_itemName(std::move(src)) {};
    };
    class CustomerOrder {

        std::string m_name;
        std::string m_product;
        size_t m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;

    public:

        CustomerOrder() = default;
        explicit CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder& orig);
        CustomerOrder& operator=(const CustomerOrder& orig) = delete;
        CustomerOrder(CustomerOrder&& orig) noexcept;
        CustomerOrder& operator=(CustomerOrder&& orig) noexcept;
        ~CustomerOrder();
        [[nodiscard]] bool isOrderFilled() const;
        [[nodiscard]] bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os) const;
        void display(std::ostream& os) const;
    };
}
#endif //SENECA_CUSTOMERORDER_H
