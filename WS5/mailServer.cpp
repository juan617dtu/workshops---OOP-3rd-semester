// Program arguments: ws emails.csv identities.txt spam.txt

#include "mailServer.h"
#include <iomanip>
#include <iostream>
#include "message.h"
#include "plugin.h"
#include <stdexcept>

namespace seneca {

    MailServer::MailServer(const char *name, const char *address) {

        m_userName = name;
        m_userAddres = address;
    }
    MailServer::MailServer(const MailServer &other) {

        *this = other;
    }
    MailServer &MailServer::operator=(const MailServer &other) {

        if (this != &other) {
            delete[] m_inbox;
            this->m_userName = other.m_userName;
            this->m_userAddres = other.m_userAddres;
            this->m_plugin[0] = other.m_plugin[0];
            this->m_plugin[1] = other.m_plugin[1];
            this->m_cnt = other.m_cnt;
            if (other.m_cnt > 0) {
                this->m_inbox = new Message[m_cnt];
                for (auto i = 0u; i < m_cnt; ++i) this->m_inbox[i] = other.m_inbox[i];
            }
            else m_inbox = nullptr;
        }
        return *this;
    }
    MailServer::MailServer(MailServer &&other) noexcept {

        *this = std::move(other);
    }
    MailServer &MailServer::operator=(MailServer &&other) noexcept {

        if (this != &other) {
            delete[] m_inbox;
            this->m_userName = other.m_userName;
            this->m_userAddres = other.m_userAddres;
            this->m_plugin[0] = other.m_plugin[0];
            this->m_plugin[1] = other.m_plugin[1];
            this->m_cnt = other.m_cnt;
            this->m_inbox = other.m_inbox;
            other.m_inbox = nullptr;
        }
        return *this;
    }
    MailServer::~MailServer() {

        delete[] m_inbox;
    }
    void MailServer::receiveMail(Message msg) {

        if (msg.m_toAddress == this->m_userAddres) {
            Message* temp = new Message[m_cnt + 1];
            for (auto i = 0u; i < m_cnt; ++i) temp[i] = this->m_inbox[i];
            temp[m_cnt] = msg;
            delete[] this->m_inbox;
            this->m_inbox = temp;
            this->m_cnt += 1;
            for (Plugin* plugin : m_plugin) {
                if (plugin != nullptr) (*plugin)(m_inbox[m_cnt - 1]);
            }
            if (onNewMailArrived != nullptr) onNewMailArrived(m_inbox[m_cnt - 1]);
        }
        else throw "The message is for another user.";
    }
    void MailServer::addPlugin(Plugin *thePlugin) {

        if (thePlugin != nullptr) {
            if (m_plugin[0] == nullptr) m_plugin[0] = thePlugin;
            else if (m_plugin[1] == nullptr) m_plugin[1] = thePlugin;
        }
    }
    void MailServer::setObserver(void (*observer)(const Message &)) {

        this->onNewMailArrived = observer;
    }
    Message &MailServer::operator[](size_t idx) {

        if (idx >= m_cnt) throw std::out_of_range("Index " + std::to_string(idx) + " is out of range.");
        return this->m_inbox[idx];
    }
    size_t MailServer::getInboxSize() {

        return this->m_cnt;
    }
    void MailServer::showInbox() {

        for (auto i = 0u; i < this->m_cnt; ++i) {
            auto& email = this->m_inbox[i];
            std::cout << std::setw(20) << std::right << email.m_fromName << "  "
            << std::setw(40) << std::left << email.m_fromAddress << "  "
            << std::setw(15) << email.m_date.substr(0, 10) << "  "
            << email.m_subject << '\n';
        }
    }
}



