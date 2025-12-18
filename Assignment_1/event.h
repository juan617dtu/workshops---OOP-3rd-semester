#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H
#include <chrono>

namespace seneca {

    class Event {

        std::string m_event{};
        std::chrono::nanoseconds m_duration{};

    public:

        Event() = default;
        //in line implementation: m_event = parameter1, m_duration = parameter2
        Event(const char* name, const std::chrono::nanoseconds& duration) : m_event{name}, m_duration{duration} {};
        friend std::ostream& operator<<(std::ostream& os, const Event& event);
    };
}
#endif //SENECA_EVENT_H

