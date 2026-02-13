#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <list>
#include <sstream>
#include <vector>
#include "mediaItem.h"

namespace seneca {

    class TvShow : public MediaItem {

        std::string m_id{};
        struct TvEpisode
        {
            const TvShow* m_show{};
            unsigned short m_numberOverall{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned int m_length{};
            std::string m_title{};
            std::string m_summary{};
        };
        std::vector<TvEpisode> m_episodes{};
        TvShow(const std::string& id, const std::string& title, const std::string& summary, unsigned short year);
        static unsigned int to_seconds(const std::string& time_str);

    public:

        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            size_t char_pos = strEpisode.find('#');
            if (strEpisode.empty() or char_pos != std::string::npos) {
                throw "Not a valid episode.";
            }
            std::stringstream ss(strEpisode);
            std::vector<std::string> tokens;
            std::string token;
            for (size_t i = 0; i < 7; ++i) {
                std::getline(ss, token, ',');
                trim(token);
                tokens.push_back(token);
            }
            std::getline(ss, token);
            trim(token);
            tokens.push_back(token);
            TvEpisode episode;
            const std::string id = tokens.front();
            episode.m_numberOverall = std::stoi(tokens[1]);
            episode.m_season = tokens[2].empty() ? 1 : std::stoi(tokens[2]); //TODO: to test if it breaks
            episode.m_numberInSeason = std::stoi(tokens[3]);
            episode.m_airDate = tokens[4];
            episode.m_length = to_seconds(tokens[5]);
            episode.m_title = tokens[6];
            episode.m_summary = tokens[7];
            for (size_t i = 0; i < col.size(); ++i) {
                if (auto item = dynamic_cast<TvShow*>(col[i]); item and item->m_id == id) {
                    episode.m_show = item;
                    item->m_episodes.push_back(episode);
                    break;
                }
            }
        }
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
}
#endif //SENECA_TVSHOW_H

