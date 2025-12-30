//
// Created by masti on 12/26/2025.
//

#ifndef SENECA_MAILSERVER_H
#define SENECA_MAILSERVER_H
#include <string>

namespace seneca {

    class Plugin;
    struct Message;

    class MailServer {

        std::string m_userName{};
        std::string m_userAddres{};
        Message* m_inbox{};
        size_t m_cnt{};
        void (*onNewMailArrived)(const Message&){};
        Plugin* m_plugin[2]{};

    public:

        MailServer(const char* name, const char* address);
        MailServer(const MailServer& other);
        MailServer& operator=(const MailServer& other);
        ~MailServer();
        MailServer(MailServer&& other) noexcept;
        MailServer& operator=(MailServer&& other) noexcept;
        void receiveMail(Message msg);
        void addPlugin(Plugin* thePlugin);
        void setObserver(void(*observer)(const Message&));
        Message& operator[](size_t idx);
        size_t getInboxSize();
        void showInbox();
    };
}
#endif //SENECA_MAILSERVER_H
