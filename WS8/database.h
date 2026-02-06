//
// Created by masti on 2/5/2026.
//

#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H
#define ARRAY_SIZE 20
#include <fstream>
#include <memory>
#include <iomanip>

namespace seneca {

    enum class Err_Status
    {
        Err_Success,
        Err_NotFound,
        Err_OutOfMemory,
      };
    template <typename T>
    class Database {

        unsigned int m_entries{};
        std::string m_keys[ARRAY_SIZE]{};
        T m_values[ARRAY_SIZE]{};
        std::string m_name{};
        static std::shared_ptr<Database> m_instance;
        explicit Database(const std::string& filename) {

            std::cout << '[' << this << "] Database(const std::string&)\n";
            m_name = filename;
            std::ifstream file(filename);
            std::string key;
            T value;
            while (file >> key >> value and m_entries < ARRAY_SIZE) {
                //if (file.fail() and !file.eof()) break;
                std::ranges::replace(key, '_', ' ');
                encryptDecrypt(value);
                m_keys[m_entries] = key;
                m_values[m_entries] = value;
                m_entries++;
            }
            file.close();
        }

        static void encryptDecrypt(T&) { /* nothing */ }
    public:

        static std::shared_ptr<Database> getInstance(const std::string& dbFileName) {

            if (m_instance == nullptr) m_instance = std::shared_ptr<Database>(new Database(dbFileName));
            return m_instance;
        }
        Err_Status GetValue(const std::string& key, T& value) {

            for (int i = 0u; i < m_entries; ++i) {
                if (m_keys[i] == key) {
                    value = m_values[i];
                    return Err_Status::Err_Success;
                }
            }
            return Err_Status::Err_NotFound;
        }
        Err_Status SetValue(const std::string& key, const T& value) {

            if (m_entries < ARRAY_SIZE) {
                m_keys[m_entries] = key;
                m_values[m_entries] = value;
                m_entries++;
                return Err_Status::Err_Success;
            }
            return Err_Status::Err_OutOfMemory;
        }
        ~Database() {

            std::cout << '[' << this << "] ~Database()\n";
            const std::string backup = m_name + ".bkp.txt";
            std::ofstream backup_file(backup, std::ios::binary);
            for (int i = 0u; i < m_entries; ++i) {
                T temp = m_values[i];
                encryptDecrypt(temp);
                backup_file << std::left << std::setw(25) << m_keys[i] << " -> " << temp << '\n';
            }
            backup_file.close();
        }
    };
    template<typename T>
    std::shared_ptr<Database<T>> Database<T>::m_instance = nullptr;
    template<>
    inline void Database<std::string>::encryptDecrypt(std::string &value) {
        constexpr char secret[]{ "secret encryption key" };
        for (auto& parameter_char : value) {
            for (auto& secret_char : secret) parameter_char = parameter_char ^ secret_char;
        }
    }
    template<>
    inline void Database<long long>::encryptDecrypt(long long& value) {
        constexpr char secret[]{ "super secret encryption key" };
        const auto byte_pointer = reinterpret_cast<char*>(&value);
        for (size_t i = 0; i < sizeof(value); ++i) {
            for (auto& secret_char : secret) byte_pointer[i] ^= secret_char;
        }
    }
}
#endif //SENECA_DATABASE_H
