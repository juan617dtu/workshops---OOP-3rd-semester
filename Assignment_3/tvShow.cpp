#include "tvShow.h"
#include <algorithm>
#include "settings.h"
#include <iomanip>
#include <numeric>
#include <sstream>

namespace seneca {

    TvShow::TvShow(const std::string &id, const std::string &title, const std::string &summary,
        const unsigned short year) : MediaItem(title, summary, year) {

        m_id = id;
    }
    unsigned int TvShow::to_seconds(const std::string &time_str) {

        std::stringstream ss(time_str);
        std::string h, m, s;
        std::getline(ss, h, ':');
        std::getline(ss, m, ':');
        std::getline(ss, s, ':');
        return std::stoi(h) * 3600 + std::stoi(m) * 60 + std::stoi(s);
    }
    void TvShow::display(std::ostream &out) const {

        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                  << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
              << std::setfill(' ') << '\n';
        }
    }
    TvShow *TvShow::createItem(const std::string &strShow) {

        size_t char_pos = strShow.find('#');
        if (strShow.empty() or char_pos != std::string::npos) throw "Not a valid show.";
        std::string str = strShow;
        std::string id = str.substr(0, str.find(','));
        trim(id);
        size_t first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string title = str.substr(0, str.find(','));
        trim(title);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string year_str = str.substr(0, str.find(','));
        trim(year_str);
        const unsigned short year = std::stoi(year_str);
        first = str.find_first_of(',');
        str.erase(0, first + 1);
        std::string summary = str;
        trim(summary);
        TvShow* tv_show = new TvShow(id, title, summary, year);
        return tv_show;
    }
    double TvShow::getEpisodeAverageLength() const {

        const double avg = std::accumulate(m_episodes.begin(), m_episodes.end(), 0.0,
            [](const double sum, const TvEpisode& episode) {
            return sum + episode.m_length;
        });
        return avg / static_cast<double>(m_episodes.size());
    }
    std::list<std::string> TvShow::getLongEpisodes() const {

        std::vector<TvEpisode> long_episodes;
        std::list<std::string> result;
        std::copy_if(m_episodes.begin(), m_episodes.end(), std::back_inserter(long_episodes),
            [](const TvEpisode& episode) {
            return episode.m_length >= 3600;
        });
        std::transform(long_episodes.begin(), long_episodes.end(),std::back_inserter(result),
            [](const TvEpisode& episode) {
           return episode.m_title;
        });
        return result;
    }
}

