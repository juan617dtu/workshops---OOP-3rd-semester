//
// Created by masti on 12/12/2025.
//

#include "Pair.h"
#include <iomanip>

namespace seneca {

    bool Pair::operator==(const Pair& pair) {

        return this->m_key == pair.m_key;
    }
    std::ostream& operator<<(std::ostream& os, const Pair& pair) {

        os << std::setw(20) << pair.m_key << ": " << pair.m_value;
        return os;
    }
}
