#include "event.h"
#include "settings.h"

namespace seneca {

    std::ostream &operator<<(std::ostream &os, const Event &event) {

        static int counter = 0;
        counter++;
        os << std::right << std::setw(2) << counter << ": ";
        os << std::setw(40) << event.m_event << " -> ";
        if (g_settings.m_time_units == "seconds") os << std::setw(2) << event.m_duration << ' '
        << g_settings.m_time_units;
        else if (g_settings.m_time_units == "milliseconds") os << std::setw(5) << event.m_duration << ' '
        << g_settings.m_time_units;
        else if (g_settings.m_time_units == "microseconds") os << std::setw(8) << event.m_duration << ' '
        << g_settings.m_time_units;
        else { os << std::setw(11) << event.m_duration << ' ' << g_settings.m_time_units; }//"nanoseconds"
        return os;
    }


}
