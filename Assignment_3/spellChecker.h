//
// Created by masti on 2/11/2026.
//

#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#define ARRAY_SIZE 6
#include <string>

namespace seneca {

    class SpellChecker {

        std::string m_badWords[ARRAY_SIZE]{};
        std::string m_goodWords[ARRAY_SIZE]{};
        size_t m_replacements[ARRAY_SIZE]{};

    public:

        explicit SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out) const;
    };
}
#endif //SENECA_SPELLCHECKER_H
