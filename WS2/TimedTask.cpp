#include "TimedTask.h"

namespace seneca {

    void TimedTask::startClock() {

        m_start = std::chrono::steady_clock::now();
    }
    void TimedTask::stopClock() {

        m_end = std::chrono::steady_clock::now();
    }
    void TimedTask::addTask(const char* task_name) {

        if (m_records_stored < MAX_EVENTS && task_name != nullptr) {
            m_events[m_records_stored].task_name = task_name;
            m_events[m_records_stored].time_units = "nanoseconds";
            m_events[m_records_stored].duration =
                std::chrono::duration_cast<std::chrono::nanoseconds>(m_end - m_start);
            m_records_stored++;
        }
    }
    std::ostream &operator<<(std::ostream &os, TimedTask &tt) {

        os << "Execution Times:\n" << "--------------------------\n";
        for (size_t i = 0; i < tt.m_records_stored; ++i) {
            os << std::left << std::setw(21) <<
                tt.m_events[i].task_name << ' ' << std::right << std::setw(13) << tt.m_events[i].duration << ' '
            << tt.m_events[i].time_units << '\n';
        }
        os << "--------------------------\n";
        return os;
    }
}

