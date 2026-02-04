//
// Created by masti on 2/3/2026.
//

#ifndef SENECA_SONGCOLLECTION_H
#define SENECA_SONGCOLLECTION_H
#include <list>
#include <string>
#include <vector>

namespace seneca {

    struct Song {

        std::string m_artist{};
        std::string m_title{};
        std::string m_album{};
        double m_price{};
        int m_year{};
        unsigned int m_length{};
    };
    class SongCollection {

        std::vector<Song> m_songs;
        static std::string trim_whitespace(const std::string& str);

    public:

        explicit SongCollection(const std::string& filename);
        void display(std::ostream& out) const;
        void sort(const std::string &field);
        void cleanAlbum();
        bool inCollection(const std::string &artist) const;
        std::list<Song> getSongsForArtist(const std::string& artist) const;
    };
    std::ostream& operator<<(std::ostream& out, const Song& theSong);
}
#endif //SENECA_SONGCOLLECTION_H
