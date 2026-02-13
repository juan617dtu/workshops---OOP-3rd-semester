//
// Created by masti on 2/9/2026.
//

#include "book.h"
#include "settings.h"
#include <iomanip>

namespace seneca {

    Book::Book(const std::string& author, const std::string& title, const std::string& country,
        const unsigned short year, const double price, const std::string& summary): MediaItem(title, summary, year) {

        m_author = author;
        m_country = country;
        m_price = price;
    }
    void Book::display(std::ostream &out) const {

        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
              << std::setfill(' ') << '\n';
        }
    }
    Book *Book::createItem(const std::string &strBook) {

        size_t char_pos = strBook.find('#');
        if (strBook.empty() or char_pos != std::string::npos) throw "Not a valid book.";
        std::string author = strBook.substr(0, strBook.find(','));
        trim(author);
        std::string str = strBook;
        size_t first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string title = str.substr(0, str.find(','));
        trim(title);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string country = str.substr(0, str.find(','));
        trim(country);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string price_str = str.substr(0, str.find(','));
        trim(price_str);
        const double price = std::stod(price_str);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string year_str = str.substr(0, str.find(','));
        trim(year_str);
        const unsigned short year = std::stoi(year_str);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string summary = str;
        trim(summary);
        Book* book = new Book(author, title, country, year, price, summary);
        return book;
    }

}
