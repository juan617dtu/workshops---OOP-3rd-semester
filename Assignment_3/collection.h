#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include <vector>
#include "mediaItem.h"

namespace seneca {

    class Collection {

        std::string m_name{};
        std::vector<MediaItem*> m_media_items;
        void (*m_observer)(const Collection &col, const MediaItem &item){};

    public:

        explicit Collection(const std::string& name);
        Collection(const Collection &col) = delete;
        Collection& operator=(const Collection &col) = delete;
        Collection(Collection &&col) = delete;
        Collection& operator=(Collection &&col) = delete;
        ~Collection() = default;
        const std::string& name() const;
        size_t size() const;
        void setObserver(void (*observer)(const Collection&, const MediaItem&));
        Collection& operator+=(MediaItem* item);
        MediaItem* operator[](size_t idx) const;
        MediaItem* operator[](const std::string& title) const;
        void removeQuotes();
        void sort(const std::string& field);
        friend std::ostream& operator<<(std::ostream& os, const Collection& col);
    };
}
#endif //SENECA_COLLECTION_H

