//
// Created by masti on 12/17/2025.
//

#include "timeMonitor.h"

namespace seneca {

    void TimeMonitor::startEvent(const char *name) {

        m_event_name = name;
        m_start_time = std::chrono::steady_clock::now();
    }
    Event TimeMonitor::stopEvent() {

        auto end_time = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration duration = end_time - m_start_time;
        Event event{m_event_name, duration};
        return event;
    }

}