#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca {

    class FoodOrder {

        char m_customer_name[10]{};
        char* m_food_desc{};
        double m_food_price{};
        bool m_is_daily_special{};

    public:
        void read(std::istream& is);
        void display() const;
        FoodOrder(){};
        FoodOrder(const FoodOrder& other);
        FoodOrder& operator=(const FoodOrder& other);
        ~FoodOrder();
    };
}
#endif //FOODORDER_H

