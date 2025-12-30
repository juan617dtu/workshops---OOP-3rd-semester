#ifndef SENECA_VERIFYIDENTITYPLUGIN_H
#define SENECA_VERIFYIDENTITYPLUGIN_H
#include <string>
#include "plugin.h"

namespace seneca {

    class VerifyIdentityPlugin : public Plugin {

        std::string m_trusted_email_adresses[10u];

    public:
        explicit VerifyIdentityPlugin(const char* filename);
        void operator()(Message& msg) override;
        void showStats() const override;
    };
}
#endif //SENECA_VERIFYIDENTITYPLUGIN_H

