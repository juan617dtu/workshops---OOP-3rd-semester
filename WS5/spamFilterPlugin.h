//
// Created by masti on 12/24/2025.
//

#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H
#include <string>
#include "plugin.h"

namespace seneca {

    struct Message;

    class SpamFilterPlugin : public Plugin{

        std::string m_spam_filter[5];
        size_t m_spam_emails{};

    public:

        explicit SpamFilterPlugin(const char* filename);
        void operator()(Message& msg) override;
        void showStats() const override;
    };
}
#endif //SENECA_SPAMFILTERPLUGIN_H
