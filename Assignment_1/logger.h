//
// Created by masti on 12/16/2025.
//

#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"

namespace seneca {

    class Logger {

        Event* m_event_ptr{nullptr};
        size_t m_size{};//number of valid elements
        size_t m_capacity{};//allocated space

    public:

        Logger() = default;
        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;
        void addEvent(const Event& event);
        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);
    };
}
#endif //SENECA_LOGGER_H
