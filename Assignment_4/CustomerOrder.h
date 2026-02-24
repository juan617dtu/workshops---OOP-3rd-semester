//
// Created by masti on 2/23/2026.
//

#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"
#include <iostream>
#include <string>

namespace seneca {

    struct Item
    {
        std::string m_itemName;
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };
    class CustomerOrder {

        std::string m_name;
        std::string m_product;
        size_t m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;

    public:

        CustomerOrder() = default;
        CustomerOrder(const std::string& str);
        CustomerOrder(const CustomerOrder& orig);
        CustomerOrder& operator=(const CustomerOrder& orig) = delete;
        CustomerOrder(CustomerOrder&& orig) noexcept;
        CustomerOrder& operator=(CustomerOrder&& orig) noexcept;
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}
#endif //SENECA_CUSTOMERORDER_H
