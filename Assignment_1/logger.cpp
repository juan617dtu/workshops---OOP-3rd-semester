#include "logger.h"

namespace seneca {

    Logger::~Logger() {

        delete[] m_event_ptr;
        m_event_ptr = nullptr;
    }
    Logger::Logger(Logger &&other) noexcept {

        m_event_ptr = other.m_event_ptr;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_event_ptr = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }
    Logger& Logger::operator=(Logger&& other) noexcept {

        if (this != &other) {
            delete[] m_event_ptr;
            m_event_ptr = other.m_event_ptr;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_event_ptr = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }
    void Logger::addEvent(const Event& event) {

        if (m_size == m_capacity) { //check if resize is needed
            const size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity * 2; //decide new capacity
            Event* temp = new Event[new_capacity]; //allocate new array
            for (size_t i = 0; i < m_size; ++i) {
                temp[i] = m_event_ptr[i]; //copy old events into new array
            }
            delete[] m_event_ptr; //free old memory
            m_event_ptr = temp; //update pointer and capacity
            m_capacity = new_capacity;
        }
        m_event_ptr[m_size] = event; //add the new event
        m_size++;
    }
    std::ostream &operator<<(std::ostream &os, const Logger &logger) {

        for (size_t i = 0; i < logger.m_size; ++i) {
            os << logger.m_event_ptr[i] << std::endl;
        }
        return os;
    }

}

