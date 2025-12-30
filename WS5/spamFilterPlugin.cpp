//
// Created by masti on 12/24/2025.
//

#include "spamFilterPlugin.h"
#include <fstream>
#include <iostream>

#include "message.h"

namespace seneca {

    SpamFilterPlugin::SpamFilterPlugin(const char *filename) {

        std::ifstream ifs(filename);
        if (!ifs.is_open()) {
            std::cerr << "Can't open file " << filename << std::endl;// Handle error: log, exit, or attempt recovery
            return;
        }
        for (auto & i : m_spam_filter) std::getline(ifs, i);
    }
    void SpamFilterPlugin::operator()(Message& msg) {
        for (const auto& i : m_spam_filter) {
            if (!i.empty() and msg.m_subject.find(i) != std::string::npos) {
                msg.m_subject.insert(0, "[SPAM] ");
                m_spam_emails++;
            }
        }
    }
    void SpamFilterPlugin::showStats() const {

        std::cout << "[Spam Filter Plugin] Identified " << m_spam_emails << " spam messages.\n";
    }
}
