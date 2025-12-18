//
// Created by masti on 12/17/2025.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include "dictionary.h"
#include "settings.h"

namespace seneca {

    PartOfSpeech Dictionary::parse_pos(const std::string &pos) const {

        if (pos == "n." || pos == "n. pl.") return PartOfSpeech::Noun;
        if (pos == "adv.") return PartOfSpeech::Adverb;
        if (pos == "a.") return PartOfSpeech::Adjective;
        if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") return PartOfSpeech::Verb;
        if (pos == "prep.") return PartOfSpeech::Preposition;
        if (pos == "pron.") return PartOfSpeech::Pronoun;
        if (pos == "conj.") return PartOfSpeech::Conjunction;
        if (pos == "interj.") return PartOfSpeech::Interjection;
        return PartOfSpeech::Unknown;
    }
    std::string Dictionary::pos_to_string(PartOfSpeech pos) {

        switch (pos) {
            case PartOfSpeech::Noun:
                return "noun";
            case PartOfSpeech::Adverb:
                return "adverb";
            case PartOfSpeech::Verb:
                return "verb";
            case PartOfSpeech::Preposition:
                return "prep";
            case PartOfSpeech::Pronoun:
                return "pron";
            case PartOfSpeech::Conjunction:
                return "conj";
            case PartOfSpeech::Interjection:
                return "interj";
            case PartOfSpeech::Adjective:
                return "adjective";
            default:
                return "unknown";
        }
    }
    Dictionary::Dictionary(const char *filename) {

        std::ifstream file{filename};
        if (!file) {
            m_words = nullptr;
            m_size = 0;
            return;
        }
        std::string line;
        size_t line_count{};
        while (std::getline(file, line)) {
            line_count++;
        }
        m_size = line_count;
        m_words = new Word[m_size];
        file.clear();
        file.seekg(0, std::ios::beg);
        unsigned int index{0};
        while (std::getline(file, line)) {
            std::stringstream ss{line};
            std::string word, pos, def;
            std::getline(ss, word, ',');
            std::getline(ss, pos, ',');
            std::getline(ss, def);
            m_words[index].m_word = word;
            m_words[index].m_pos = parse_pos(pos);
            m_words[index].m_definition = def;
            ++index;
        }
    }
    Dictionary::Dictionary(const Dictionary &other) {

        m_size = other.m_size;
        if (other.m_words != nullptr && m_size > 0) {
            m_words = new Word[m_size];
            for (size_t i = 0; i < m_size; ++i) m_words[i] = other.m_words[i];
        }
    }
    Dictionary &Dictionary::operator=(const Dictionary &other) {

        if (this != &other) {
            delete[] m_words;
            m_words = nullptr;
            m_size = other.m_size;
            if (other.m_words != nullptr && m_size > 0) {
                m_words = new Word[m_size];
                for (size_t i = 0; i < m_size; ++i) m_words[i] = other.m_words[i];
            }
        }
        return *this;
    }
    Dictionary::Dictionary(Dictionary &&other) noexcept{

        m_words = other.m_words;
        m_size = other.m_size;
        other.m_words = nullptr;
        other.m_size = 0;
    }
    Dictionary &Dictionary::operator=(Dictionary &&other) noexcept {

        if (this !=&other) {
            delete[] m_words;
            m_words = other.m_words;
            m_size = other.m_size;
            other.m_words = nullptr;
            other.m_size = 0;
        }
        return *this;
    }
    void Dictionary::searchWord(const char *word) {

        bool found{false};
        for (size_t i{0}; i < m_size; ++i) {
            if (m_words[i].m_word == word) {
                if (!found) {
                    std::cout << m_words[i].m_word;
                    found = true;
                }
                else { std::cout << std::string(m_words[i].m_word.length(), ' '); }
                if (g_settings.m_verbose == true && m_words[i].m_pos != PartOfSpeech::Unknown) {
                    std::cout << " - (" << pos_to_string(m_words[i].m_pos) << ") ";
                }
                else { std::cout << " - "; }
                std::cout << m_words[i].m_definition << std::endl;
                if (!g_settings.m_show_all) return;
            }
        }
        if (!found) std::cout << "Word '" << word << "' was not found in the dictionary.\n";
    }
}
