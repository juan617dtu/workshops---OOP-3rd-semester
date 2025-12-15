#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "Pair.h"

namespace seneca {

    template<typename T, unsigned int CAPACITY>
    class Collection {

        T m_items[CAPACITY]{};
        size_t m_num_items{};
        static T m_default;

    public:

        size_t size() { return m_num_items; }

        void display(std::ostream &os = std::cout) {

            os << "----------------------\n" << "| Collection Content |\n" << "----------------------\n";
            for (size_t i = 0; i < m_num_items; ++i) os << m_items[i] << '\n';
            os << "----------------------\n";
        }
        virtual bool add(const T& item) {

            if (m_num_items < CAPACITY) {
                m_items[m_num_items++] = item;
                return true;
            }
            return false;
        }
        T operator[](unsigned int index) {

            if (index < m_num_items) return m_items[index];
            return m_default;
        }
        virtual ~Collection() = default;
    };
    template<typename T, unsigned int CAPACITY>
    T Collection<T, CAPACITY>::m_default{};
    template<>
    Pair Collection<Pair, 100>::m_default = Pair("No Key", "No Value");
}
#endif //SENECA_COLLECTION_H

