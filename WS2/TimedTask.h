//
// Created by masti on 12/10/2025.
//

#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H
#include <chrono>
#define MAX_EVENTS 10

namespace seneca {

    class TimedTask {

        int m_records_stored{};
        std::chrono::steady_clock::time_point m_start{};
        std::chrono::steady_clock::time_point m_end{};
        struct Task {
            std::string task_name;
            std::string time_units;
            std::chrono::steady_clock::duration duration;
        } m_events[MAX_EVENTS]; // Task m_events[MAX_EVENTS];
    public:
        TimedTask() = default;
        void startClock();
        void stopClock();
        void addTask(const char* task_name);
        friend std::ostream& operator<<(std::ostream& os, TimedTask& tt);
    };
}
#endif //SENECA_TIMEDTASK_H
