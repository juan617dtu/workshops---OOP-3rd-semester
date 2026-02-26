//
// Created by masti on 2/24/2026.
//

#include "LineManager.h"
#include <algorithm>
#include <fstream>

namespace seneca {

    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations) {

        std::ifstream input_file(file);
        if (!input_file) throw std::runtime_error("Could not open file: " + file);
        std::string line;
        while (std::getline(input_file, line)) {
            std::string current_name{};
            std::string next_name{};
            if (line.find('|') != std::string::npos) {
                current_name = line.substr(0, line.find('|'));
                next_name = line.substr(line.find('|') + 1);
            }
            else current_name = line;
            auto current_station = std::find_if(stations.begin(), stations.end(),
                [&current_name](const Workstation *station) {
                return station->getItemName() == current_name;
            });
            if (current_station == stations.end()) {
                throw std::runtime_error("Could not find station " + current_name);
            }
            if (!next_name.empty()) {
                auto next_station = std::find_if(stations.begin(), stations.end(),
                    [&next_name](const Workstation *station) {
                        return station->getItemName() == next_name;
                    });
                if (next_station != stations.end()) (*current_station)->setNextStation(*next_station);
                else throw std::runtime_error("Could not find station " + next_name);
            }
            m_activeLine.push_back(*current_station);
        }
        auto first = std::find_if(m_activeLine.begin(), m_activeLine.end(),
            [this](const Workstation *station) {
           return std::none_of(m_activeLine.begin(), m_activeLine.end(),
               [station](const Workstation *other) {
               return other->getNextStation() == station;
           });
        });
        if (first == m_activeLine.end()) throw std::runtime_error("Unable to determine first station");
        m_firstStation = *first;
        m_cntCustomerOrder = g_pending.size();
    }
    void LineManager::reorderStations() {

        std::vector<Workstation *> reordered_stations;
        Workstation* current_station = m_firstStation;
        while (current_station != nullptr) {
            reordered_stations.push_back(current_station);
            current_station = current_station->getNextStation();
        }
        m_activeLine = std::move(reordered_stations);
    }
    bool LineManager::run(std::ostream &os) {

        static unsigned int current_iteration;
        current_iteration++;
        os << "Line Manager Iteration: " << current_iteration << '\n';
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *station) {
            station->fill(os);
        });
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *station) {
            station->attemptToMoveOrder();
        });
        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }
    void LineManager::display(std::ostream &os) const {

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation *station) {
            station->display(os);
        });
    }
}
