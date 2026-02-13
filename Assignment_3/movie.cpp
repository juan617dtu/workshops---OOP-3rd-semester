//
// Created by masti on 2/10/2026.
//

#include "movie.h"
#include "settings.h"
#include <iomanip>

namespace seneca {

    Movie::Movie(const std::string &title, const std::string &summary, const unsigned short year) :
    MediaItem(title, summary, year) {}

    void Movie::display(std::ostream &out) const {

        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
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
    Movie *Movie::createItem(const std::string &strMovie) {

        size_t char_pos = strMovie.find('#');
        if (strMovie.empty() or char_pos != std::string::npos) throw "Not a valid movie.";
        std::string str = strMovie;
        std::string title = str.substr(0, str.find(','));
        trim(title);
        size_t first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string year_str = str.substr(0, str.find(','));
        trim(year_str);
        const unsigned short year = std::stoi(year_str);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string summary = str;
        trim(summary);
        Movie *movie = new Movie(title, summary, year);
        return movie;
    }
}