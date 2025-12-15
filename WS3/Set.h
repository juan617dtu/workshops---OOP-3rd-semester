#ifndef SENECA_SET_H
#define SENECA_SET_H
#include <cmath>
#include "Collection.h"

namespace seneca {

    template<typename T>
    class Set : public Collection<T, 100> {

    public:

        bool add(const T& item) override {

            for (size_t i = 0; i < this->size(); ++i) {
                if (item == (*this)[i]) return false;
            }
            return Collection<T, 100>::add(item);
        }
    };
    template<>
    bool Set<double>::add(const double& item) {

        for (size_t i = 0; i < this->size(); ++i) {
            if (std::fabs((*this)[i] - item) <= 0.01) return false;
        }
        return Collection::add(item);
    }

}
#endif //SENECA_SET_H

