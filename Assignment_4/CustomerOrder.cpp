#include "CustomerOrder.h"
#include "Utilities.h"
#include <iomanip>

namespace seneca {

    size_t CustomerOrder::m_widthField = 0u;

    CustomerOrder::CustomerOrder(const std::string& str) {

        Utilities utilities;
        size_t next_pos = 0;
        bool more = false;
        m_name = utilities.extractToken(str, next_pos, more);
        m_product = utilities.extractToken(str, next_pos, more);
        size_t temp_pos = next_pos;
        bool temp_more = more;
        size_t item_count = 0;
        while (temp_more) {
            utilities.extractToken(str, temp_pos, temp_more);
            item_count++;
        }
        m_cntItem = item_count;
        if (m_cntItem > 0) m_lstItem = new Item *[m_cntItem];
        for (int i = 0u; i < m_cntItem; ++i) {
            Item item = utilities.extractToken(str, next_pos, more);
            m_lstItem[i] = new Item(item);
        }
        if (utilities.getFieldWidth() > m_widthField) m_widthField = utilities.getFieldWidth();
    }
    CustomerOrder::CustomerOrder(const CustomerOrder &orig) {

        throw "ERROR: Cannot make copies.";
    }
    CustomerOrder::CustomerOrder(CustomerOrder &&orig) noexcept {

        m_name = std::move(orig.m_name);
        m_product = std::move(orig.m_product);
        m_cntItem = orig.m_cntItem;
        m_lstItem = orig.m_lstItem;
        orig.m_cntItem = 0;
        orig.m_lstItem = nullptr;
    }
    CustomerOrder &CustomerOrder::operator=(CustomerOrder &&orig) noexcept {

        if (this !=&orig) {
            for (size_t i = 0u; i < m_cntItem; ++i) delete m_lstItem[i];
            delete[] m_lstItem;
            m_name = std::move(orig.m_name);
            m_product = std::move(orig.m_product);
            m_cntItem = orig.m_cntItem;
            m_lstItem = orig.m_lstItem;
            orig.m_cntItem = 0;
            orig.m_lstItem = nullptr;
        }
        return *this;
    }
    CustomerOrder::~CustomerOrder() {

        for (size_t i = 0u; i < m_cntItem; ++i) delete m_lstItem[i];
        delete[] m_lstItem;
    }
    bool CustomerOrder::isOrderFilled() const {

        for (size_t i = 0u; i < m_cntItem; ++i) {
            if (!m_lstItem[i]->m_isFilled) return false;
        }
        return true;
    }
    bool CustomerOrder::isItemFilled(const std::string &itemName) const {
        for (size_t i = 0u; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == itemName) {
                if (!m_lstItem[i]->m_isFilled) return false;
            }
        }
        return true;
    }
    void CustomerOrder::fillItem(Station &station, std::ostream &os) {

        for (size_t i = 0u; i < m_cntItem; ++i) {
            if (m_lstItem[i]->m_itemName == station.getItemName() and !m_lstItem[i]->m_isFilled) {
                if (station.getQuantity() > 0) {
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
                else {
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName
                    << "]\n";
                }
                break;
            }
        }
    }
    void CustomerOrder::display(std::ostream &os) const {

        os << m_name << " - " << m_product << '\n';
        for (size_t i = 0u; i < m_cntItem; ++i) {
            os << '[' << std::right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
            << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
            << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << '\n';
        }
    }
}

