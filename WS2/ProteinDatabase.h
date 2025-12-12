#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H
#include <string>

namespace seneca {

    class ProteinDatabase {

        std::string* m_ids { nullptr };
        std::string* m_amino_acids { nullptr }; // = nullptr
        size_t m_proteins_stored { 0 };

    public:
        ProteinDatabase();
        ProteinDatabase(const std::string& file);
        ProteinDatabase(const ProteinDatabase& other);
        ProteinDatabase(ProteinDatabase&& other) noexcept;
        ProteinDatabase& operator=(const ProteinDatabase& other);
        ProteinDatabase& operator=(ProteinDatabase&& other  ) noexcept;
        ~ProteinDatabase();
        size_t size() const;
        std::string operator[](size_t i) const;
        std::string getUID(size_t i) const;
    };
}
#endif //SENECA_PROTEINDATABASE_H

