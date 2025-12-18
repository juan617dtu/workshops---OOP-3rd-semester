//
// Created by masti on 12/17/2025.
//

#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H
#include "event.h"

namespace seneca {

    class TimeMonitor {

        std::chrono::steady_clock::time_point m_start_time{};
        const char* m_event_name{nullptr};

    public:

        void startEvent(const char* name);
        Event stopEvent();
    };
}
#endif //SENECA_TIMEMONITOR_H
