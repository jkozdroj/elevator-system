#include "elevator.hpp"

namespace jk {

Elevator::Elevator(int id, int cf, int nf, int d, std::vector<int> b)
    : m_id(id), m_currFloor(cf), m_nextFloor(nf), m_isDoorOpen(d), m_buffer(b) {}

Elevator::Elevator() : m_id(0), m_currFloor(0), m_nextFloor(0), m_isDoorOpen(0), m_buffer() {}

void Elevator::setId(int id, int e) {
    if (id <= e && id >= 0) {
        m_id = id;
    }
}

void Elevator::setCurrFloor(int f, int e) {
    if (f <= e - 1 && f >= 0) {
        m_currFloor = f;
    }
}

void Elevator::setNextFloor(int f, int numFloor) {
    if (f <= numFloor - 1 && f >= 0) {
        m_nextFloor = f;
    }
}

void Elevator::setDoor(int d) {
    m_isDoorOpen = (d <= 1 && d >= 0) ? d : 0;
}

void Elevator::setBuffer(std::vector<int> v) {
    m_buffer = v;
}

int Elevator::getCurrFloor() const {
    return m_currFloor;
}

int Elevator::getNextFloor() const {
    return m_nextFloor;
}

int Elevator::getDoor() const {
    return m_isDoorOpen;
}

int Elevator::getId() const {
    return m_id;
}

std::vector<int> Elevator::getBuffer() const {
    return m_buffer;
}

void Elevator::pickedFloor(int& choice, int numFloor) {
    m_buffer.push_back(choice);
    loadFloorFromBuffer();
    std::cout << "Picked floor: " << choice << std::endl;
}

void Elevator::loadFloorFromBuffer() {
    if (!m_buffer.empty()) {
        m_nextFloor = m_buffer.front();
    }
}

int Elevator::haveInBuffer(int floor) {
    for (size_t i = 0; i < m_buffer.size(); i++) {
        if (m_buffer[i] == floor) {
            return i;
        }
    }
    return -1;
}

void Elevator::step() {
    int bufferPos = haveInBuffer(m_currFloor);

    if (bufferPos >= 0) {
        if (m_isDoorOpen) {
            setDoor(0);
            while (bufferPos >= 0) {
                m_buffer.erase(m_buffer.begin() + bufferPos);
                bufferPos = haveInBuffer(m_currFloor);
            }
            loadFloorFromBuffer();
            return;
        } else {
            if (!m_buffer.empty()) {
                setDoor(1);
            }
        }
    }

    if (m_nextFloor > m_currFloor && m_isDoorOpen == 0) {
        m_currFloor++;
    } else if (m_nextFloor < m_currFloor && m_isDoorOpen == 0) {
        m_currFloor--;
    }
}

}