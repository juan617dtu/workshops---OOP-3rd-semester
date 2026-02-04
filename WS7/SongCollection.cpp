//
// Created by masti on 2/3/2026.
//

#include "SongCollection.h"
#include <fstream>
#include <iomanip>
#include <numeric>
#include <regex>

void printbar(std::ostream& out);

namespace seneca {

    std::string SongCollection::trim_whitespace(const std::string &str) {
        // The regex matches leading whitespace (^) OR trailing whitespace ($)
        const std::regex pattern{R"(^\s+|\s+$)"};
        return std::regex_replace(str, pattern, std::string{});
    }

    SongCollection::SongCollection(const std::string& filename) {

        std::ifstream file(filename);
        if (!file) throw std::runtime_error("SongCollection::SongCollection()");
        std::string line;
        while (std::getline(file, line)) {
            Song song;
            song.m_title = trim_whitespace(line.substr(0, 25));
            song.m_artist = trim_whitespace(line.substr(25, 25));
            song.m_album = trim_whitespace(line.substr(50, 25));
            try {
                song.m_year = std::stoi(trim_whitespace(line.substr(75, 5)));
            } catch (const std::invalid_argument& e) {
                song.m_year = 0;
            }
            song.m_length = std::stoi(trim_whitespace(line.substr(80, 5)));
            song.m_price = std::stod(trim_whitespace(line.substr(85, 5)));
            m_songs.push_back(song);
        }
        file.close();
    }
    void SongCollection::display(std::ostream &out) const {

        std::for_each(m_songs.begin(), m_songs.end(), [&out](const Song& song) {
            out << song << '\n';
        });
        printbar(out);
        const unsigned int playtime = std::accumulate(m_songs.begin(), m_songs.end(), 0u,
            [](const unsigned int sum, const Song& song) { return sum + song.m_length; });
        std::string listening_time = "Total Listening Time: ";
        listening_time += std::to_string(playtime / 3600);
        listening_time += ":";
        listening_time += std::to_string(playtime % 3600 / 60);
        listening_time += ":";
        listening_time += std::to_string(playtime % 60);
        out << "| " << std::setw(84) << listening_time << " |\n";
    }
    void SongCollection::sort(const std::string &field) {

        if (field == "title") {
            std::sort(m_songs.begin(), m_songs.end(), [](const Song& s1, const Song& s2) {
                return s1.m_title < s2.m_title;
            });
        }
        else if (field == "album") {
            std::sort(m_songs.begin(), m_songs.end(), [](const Song& s1, const Song& s2) {
                return s1.m_album < s2.m_album;
            });
        }
        else if (field == "length") {
            std::sort(m_songs.begin(), m_songs.end(), [](const Song& s1, const Song& s2) {
                return s1.m_length < s2.m_length;
            });
        }
    }
    void SongCollection::cleanAlbum() {

        std::transform(m_songs.begin(), m_songs.end(), m_songs.begin(), [](Song& song) {
            if (song.m_album == "[None]") song.m_album = "";
            return song;
        });
    }
    bool SongCollection::inCollection(const std::string &artist) const {

        const bool result = std::any_of(m_songs.begin(), m_songs.end(), [&artist](const Song& song) {
            return song.m_artist == artist;
        });
        return result;
    }
    std::list<Song> SongCollection::getSongsForArtist(const std::string &artist) const {

        std::list<Song> result;
        std::copy_if(m_songs.begin(), m_songs.end(), std::back_inserter(result),
            [&artist](const Song& song) {
                return song.m_artist == artist;
            });
        return result;
    }
    std::ostream &operator<<(std::ostream &out, const Song &theSong) {

        out << "| " << std::left << std::setw(20) << theSong.m_title << " | "
        << std::setw(15) << theSong.m_artist << " | "
        << std::setw(20) << theSong.m_album << " | "
        << std::right << std::setw(6) << (theSong.m_year > 0 ? std::to_string(theSong.m_year) : "") << " | "
        << theSong.m_length / 60 << ':' << std::setw(2) << std::setfill('0') << theSong.m_length % 60 << " | "
        << std::fixed << std::setprecision(2) << theSong.m_price << " | "
        << std::setfill(' ');
        return out;
    }
}
