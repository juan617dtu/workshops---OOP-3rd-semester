#include "verifyIdentityPlugin.h"
#include <fstream>
#include <iostream>

#include "message.h"

namespace seneca {

        VerifyIdentityPlugin::VerifyIdentityPlugin(const char *filename) {

                std::ifstream ifs(filename);
                if (!ifs.is_open()) {
                        std::cerr << "Error opening file " << filename << std::endl;
                        return;
                }
                for (unsigned int index = 0; index < 10u; ++index) {
                        std::getline(ifs, m_trusted_email_adresses[index]);
                }
                ifs.close();
        }
        void VerifyIdentityPlugin::operator()(Message &msg) {

                for (std::string& user : m_trusted_email_adresses) {
                        if (user == msg.m_fromAddress) {
                                msg.m_subject.insert(0, "[TRUSTED] ");
                                break;
                        }
                }
        }
        void VerifyIdentityPlugin::showStats() const {

                std::cout << "[Identity Checker Plugin] can validate identity for " << m_trusted_email_adresses[0];
                for (size_t index = 1u; index < 10u and !m_trusted_email_adresses[index].empty(); ++index) {
                        std::cout << ", " << m_trusted_email_adresses[index];
                }
                std::cout << std::endl;
        }
}

