//
// Created by masti on 2/20/2026.
//

#include "Station.h"
#include "Utilities.h"
#include <iomanip>

namespace seneca {

    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 1;

    Station::Station(const std::string &record) {

        Utilities utilities;
        size_t next_pos = 0;
        bool more = true;
        m_id = id_generator++;
        m_item_name = utilities.extractToken(record, next_pos, more);
        const std::string sn = utilities.extractToken(record, next_pos, more);
        m_serialNumber = std::stoi(sn);
        const std::string quantity = utilities.extractToken(record, next_pos, more);
        m_quantity = std::stoi(quantity);
        if (utilities.getFieldWidth() > m_widthField) m_widthField = utilities.getFieldWidth();
        m_description = utilities.extractToken(record, next_pos, more);
    }
    const std::string &Station::getItemName() const {

        return m_item_name;
    }
    size_t Station::getNextSerialNumber() {

        return m_serialNumber++;
    }
    size_t Station::getQuantity() const {

        return m_quantity;
    }
    void Station::updateQuantity() {

        if (m_quantity > 0) m_quantity--;
    }
    void Station::display(std::ostream &os, bool full) const {

        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | "
        << std::left << std::setw(m_widthField) << std::setfill(' ') << m_item_name << " | "
        << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";
        if (full) {
            os << std::right << std::setw(4) << std::setfill(' ') << m_quantity << " | "
            << m_description;
        }
        os << '\n';
    }

}
