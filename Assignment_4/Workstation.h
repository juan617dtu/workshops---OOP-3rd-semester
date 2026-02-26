//
// Created by masti on 2/24/2026.
//

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include "CustomerOrder.h"
#include <deque>

namespace seneca {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {

        std::deque<CustomerOrder> m_orders{};
        Workstation* m_pNextStation{};

    public:

        Workstation(const Workstation& other) = delete;
        Workstation& operator=(const Workstation& other) = delete;
        Workstation(Workstation&& other) = delete;
        Workstation& operator=(Workstation&& other) = delete;
        explicit Workstation(const std::string& str);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        [[nodiscard]] Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}
#endif //SENECA_WORKSTATION_H
