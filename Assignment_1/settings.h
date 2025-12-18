#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>

namespace seneca {

    struct Settings {

        bool m_show_all{false};
        bool m_verbose{false};
        std::string m_time_units{"nanoseconds"};
    } extern g_settings;
}
#endif //SENECA_SETTINGS_H

