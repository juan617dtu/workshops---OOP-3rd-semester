#include "spellChecker.h"
#include <fstream>
#include <iomanip>
#include <sstream>

namespace seneca {

    SpellChecker::SpellChecker(const char *filename) {

        std::ifstream ifs(filename);
        if (!ifs.is_open()) throw "Bad file name!";
        std::string line;
        size_t index = 0;
        while (std::getline(ifs, line) and index < ARRAY_SIZE) {
            std::stringstream ss(line);
            std::string bad_word;
            std::string good_word;
            if (ss >> bad_word >> good_word) {
                m_badWords[index] = bad_word;
                m_goodWords[index] = good_word;
                m_replacements[index] = 0;
                index++;
            }
        }
    }
    void SpellChecker::operator()(std::string &text) {

        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            size_t position = text.find(m_badWords[i]);
            while (position != std::string::npos) {
                text.replace(position, m_badWords[i].length(), m_goodWords[i].c_str());
                m_replacements[i]++;
                position = text.find(m_badWords[i], position + m_goodWords[i].length());
            }
        }
    }
    void SpellChecker::showStatistics(std::ostream &out) const {

        out << "Spellchecker Statistics\n";
        for (size_t i = 0; i < ARRAY_SIZE; ++i) {
            out << std::setw(15) << std::left << m_badWords[i] << ": " << m_replacements[i] << " replacements\n";
        }
    }
}

