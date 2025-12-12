//Program arguments: ws protein_sequences.txt
#include "ProteinDatabase.h"
#include <fstream>

namespace seneca {

    ProteinDatabase::ProteinDatabase(const std::string &file) {

        m_proteins_stored = 0;
        m_ids = nullptr;
        m_amino_acids = nullptr;
        std::ifstream input_file(file);
        if (!input_file) return;
        std::string line;
        while (std::getline(input_file, line)) if (!line.empty() && line[0] == '>') m_proteins_stored++;
        if (m_proteins_stored == 0) return;
        m_ids = new std::string[m_proteins_stored];
        m_amino_acids = new std::string[m_proteins_stored];
        input_file.clear();
        input_file.seekg(0, std::ios::beg);
        //line.clear();
        int index = -1;
        while (std::getline(input_file, line)) {
            if (line.empty()) continue;
            if (line[0] == '>') {
                index++;
                size_t first = line.find('|');
                size_t second = line.find('|', first + 1);
                if (first != std::string::npos && second != std::string::npos) {
                    m_ids[index] = line.substr(4u, line.find_first_of('|', 4u) - 4u);
                }
                else { m_ids[index] = line.substr(1); }
            }
            else { m_amino_acids[index] += line;}
        }
    }
    ProteinDatabase::ProteinDatabase(const ProteinDatabase &other) {

        *this = other;
    }
    ProteinDatabase &ProteinDatabase::operator=(const ProteinDatabase &other) {

        if (this != &other) {
            m_proteins_stored = other.m_proteins_stored;
            delete [] m_ids;
            m_ids = nullptr;
            delete [] m_amino_acids;
            m_amino_acids = nullptr;
            if (m_proteins_stored != 0) {
                m_ids = new std::string[m_proteins_stored];
                m_amino_acids = new std::string[m_proteins_stored];
                for (size_t i = 0; i < m_proteins_stored; ++i) {
                    m_ids[i] = other.m_ids[i];
                    m_amino_acids[i] = other.m_amino_acids[i];
                }
            }
        }
        return *this;
    }
    ProteinDatabase::ProteinDatabase(ProteinDatabase &&other) noexcept {

        *this = std::move(other);
    }
    ProteinDatabase &ProteinDatabase::operator=(ProteinDatabase &&other) noexcept {

        if (this != &other) {
            m_proteins_stored = other.m_proteins_stored;
            delete [] m_ids;
            m_ids = nullptr;
            delete [] m_amino_acids;
            m_amino_acids = nullptr;
            m_ids = other.m_ids;
            m_amino_acids = other.m_amino_acids;
            other.m_proteins_stored = 0;
            other.m_ids = nullptr;
            other.m_amino_acids = nullptr;
        }
        return *this;
    }
    ProteinDatabase::~ProteinDatabase() {
        delete [] m_ids;
        m_ids = nullptr;
        delete [] m_amino_acids;
        m_amino_acids = nullptr;
    }
    size_t ProteinDatabase::size() const {

        return m_proteins_stored;
    }
    std::string ProteinDatabase::operator[](size_t i) const {

        if (i < m_proteins_stored) return m_amino_acids[i];
        return "";
    }
    std::string ProteinDatabase::getUID(size_t i) const {

        if (i < m_proteins_stored) return m_ids[i];
        return "None";
    }
    ProteinDatabase::ProteinDatabase() {
        m_proteins_stored = 0;
        m_ids = nullptr;
        m_amino_acids = nullptr;
    }

}



