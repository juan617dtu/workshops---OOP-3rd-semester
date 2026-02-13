#include "collection.h"
#include <algorithm>

namespace seneca {

    Collection::Collection(const std::string &name) {

        m_name = name;
    }
    const std::string &Collection::name() const {

        return m_name;
    }
    size_t Collection::size() const {

        return m_media_items.size();
    }
    void Collection::setObserver(void (*observer)(const Collection &, const MediaItem &)) {

        m_observer = observer;
    }
    Collection &Collection::operator+=(MediaItem *item) {

        if (!item) return *this;
        bool exists = std::any_of(m_media_items.begin(), m_media_items.end(),
            [item](MediaItem *existing_item) {
                return existing_item->getTitle() == item->getTitle();
        });
        if (exists) {
            delete item;
            return *this;
        }
        m_media_items.push_back(item);
        if (m_observer) m_observer(*this, *item);
        return *this;
    }
    MediaItem *Collection::operator[](const size_t idx) const {

        if (idx >= m_media_items.size()) {
            throw std::out_of_range("Bad index " + std::to_string(idx) +
                ". Collection has " + std::to_string(m_media_items.size()) + " items.");
        }
        return m_media_items[idx];
    }
    MediaItem *Collection::operator[](const std::string &title) const {

        const auto it = std::find_if(m_media_items.begin(), m_media_items.end(),
            [title](const MediaItem* item) {
            return item->getTitle() == title;
        });
        return (it != m_media_items.end()) ? *it : nullptr;
    }
    void Collection::removeQuotes() {

        std::for_each(m_media_items.begin(), m_media_items.end(), [](MediaItem *item) {
            std::string title = item->getTitle();
            std::string summary = item->getSummary();
            if (title[0] == '"') title.erase(0, 1);
            if (title[title.length() - 1] == '"') title.erase(title.length() - 1);
            item->setTitle(title);
            if (summary[0] == '"') summary.erase(0, 1);
            if (summary[summary.length() - 1] == '"') summary.erase(summary.length() - 1);
            item->setSummary(summary);
        });
    }
    void Collection::sort(const std::string &field) {

        std::sort(m_media_items.begin(), m_media_items.end(),
            [field](const MediaItem *a, const MediaItem *b) {
                if (field == "title") return a->getTitle() < b->getTitle();
                if (field == "year") return a->getYear() < b->getYear();
                if (field == "summary") return a->getSummary() < b->getSummary();
                return false;
            });
    }
    std::ostream &operator<<(std::ostream &os, const Collection &col) {

        for (const auto& i : col.m_media_items) {
            if (i) i->display(os);
        }
        return os;
    }
}

