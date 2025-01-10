#include "elevatorsystem.hpp"
#include "elevator.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::cout, std::cin, std::endl, std::vector, std::string;

namespace jk {

    ElevatorSystem::ElevatorSystem() : m_numElevators(2), m_numFloors(10) {
        clearFloorPlan();
    }

    ElevatorSystem::ElevatorSystem(int f, int e) {
        m_numFloors = (f > 2) ? f : 10;
        m_numElevators = (e > 0) ? e : 2;
        clearFloorPlan();
    }

    void ElevatorSystem::clearFloorPlan() {
        m_floorPlan.clear();
        for (int i = 0; i < m_numFloors; i++) {
            for (int j = 0; j < m_numElevators; j++) {
                m_floorPlan.append("X");
            }
            m_floorPlan.append("|");
            m_floorPlan.append(std::to_string(i % 10));
            m_floorPlan.append("\n");
        }
    }

    void ElevatorSystem::setFloorNum(int f) {
        m_numFloors = (f > 0) ? f : 10;
    }

    void ElevatorSystem::setElevatorNum(int e) {
        m_numElevators = (e > 0) ? e : 2;
    }

    int ElevatorSystem::getFloorNum() const {
        return m_numFloors;
    }

    int ElevatorSystem::getElevatorNum() const {
        return m_numElevators;
    }

    string ElevatorSystem::getFloorPlan() const {
        return m_floorPlan;
    }

    int ElevatorSystem::corridorButton(int& floor, int& dir, Elevator* e) {
        cout << "Pushed button" << endl;
        vector<int> timeToWait;
        vector<int> ID;
        int tempID = 0;

        for (int i = 0; i < m_numElevators; i++) {
            if (isElevatorHere(floor, e[i]) == 1 && e[i].getBuffer().empty()) {
                return i;
            }
        }

        cout << "checked free elevators" << endl;

        for (int i = 0; i < m_numElevators; i++) {
            int bufferSize = e[i].getBuffer().size();
            int door = e[i].getDoor();
            if (dir == 1) {
                if ((e[i].getCurrFloor() < e[i].getNextFloor()) &&
                    (e[i].getNextFloor() >= floor) &&
                    (e[i].getCurrFloor() < floor)) {
                    timeToWait.push_back(std::abs(e[i].getCurrFloor() - floor));
                    ID.push_back(i);
                    if (door) {
                        timeToWait.back()++;
                    }
                }
            } else if (dir == 0) {
                if ((e[i].getCurrFloor() > e[i].getNextFloor()) &&
                    (e[i].getNextFloor() <= floor) &&
                    (e[i].getCurrFloor() > floor)) {
                    timeToWait.push_back(std::abs(e[i].getCurrFloor() - floor));
                    ID.push_back(i);
                    if (door) {
                        timeToWait.back()++;
                    }
                }
            }

            if (bufferSize <= 1 && e[i].getNextFloor() == e[i].getCurrFloor()) {
                timeToWait.push_back(std::abs(e[i].getCurrFloor() - floor) + bufferSize);
                if (bufferSize == 1 && door == 0) {
                    timeToWait.back()++;
                }
                ID.push_back(i);
            }
        }

        if (!timeToWait.empty()) {
            cout << endl << endl;
            vector<int> sameTimeID;
            int bestTime = timeToWait[0];
            tempID = ID[0];

            for (size_t i = 0; i < timeToWait.size(); i++) {
                if (timeToWait[i] < bestTime) {
                    tempID = ID[i];
                    bestTime = timeToWait[i];
                }
                cout << i << ": " << timeToWait[i] << " \t";
            }

            for (size_t i = 0; i < timeToWait.size(); i++) {
                if (timeToWait[i] == bestTime) {
                    sameTimeID.push_back(ID[i]);
                }
            }
            if (!sameTimeID.empty()) {
                for (size_t i = 0; i < sameTimeID.size(); i++) {
                    int shortestBuffer = e[sameTimeID[i]].getBuffer().size();
                    if (e[sameTimeID[i]].getBuffer().size() < shortestBuffer) {
                        tempID = sameTimeID[i];
                        shortestBuffer = e[sameTimeID[i]].getBuffer().size();
                    }
                }
            }

            cout << endl << endl << "Picked elevator: " << tempID << endl << endl;
            return tempID;
        }

        for (int i = 0; i < m_numElevators; i++) {
            int shortestBuffer = e[i].getBuffer().size();
            if (e[i].getBuffer().size() < shortestBuffer) {
                tempID = i;
                shortestBuffer = e[i].getBuffer().size();
            }
        }
        return tempID;
    }

    int ElevatorSystem::isElevatorHere(int floor, Elevator& e) {
        return (e.getCurrFloor() == floor) ? 1 : -1;
    }

    void ElevatorSystem::displayElevators(Elevator* e) {
        clearFloorPlan();
        for (int i = 0; i < m_numFloors; i++) {
            for (int id = 0; id < m_numElevators; id++) {
                int isHere = isElevatorHere(i, e[id]);
                string status = e[id].getDoor() ? "O" : "E";
                if (isHere + 1) {
                    int position = (i * (m_numElevators + 3) + id);
                    m_floorPlan.erase(position, 1);
                    m_floorPlan.insert(position, status);
                }
            }
        }
        cout << endl << "Floor plan:" << endl;
        cout << m_floorPlan;
    }

}
