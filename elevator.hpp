#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP


#include<iostream>
#include"elevatorsystem.hpp"
#include <vector>

using std::cout, std::cin, std::endl, std::vector;

namespace jk {
	class Elevator {
	private:
		int m_id;
		
		int m_currFloor;
		int m_nextFloor;
		int m_isDoorOpen;
		vector<int> m_buffer;
	public:
		Elevator(int id,int cf, int nf, int d, vector<int> b) :m_id(id), m_currFloor(cf),
			m_nextFloor(nf), m_isDoorOpen(d), m_buffer(b) {}

		Elevator():m_id(0),m_currFloor(0),
			m_nextFloor(0),m_isDoorOpen(0),m_buffer() {}

		void setId(int id, int e) { 
			if(id <= e && id >= 0) { 
				m_id = id;
			}
		}


		void setCurrFloor(int f,int e) {
			if (f <= e-1 && f >= 0) {
				m_currFloor = f;
			}
		}
		void setNextFloor(int f, int numFloor) { 
			if (f <= numFloor -1 && f >= 0) {
				m_nextFloor = f;
			}
		}
		void setDoor(int d) { (d<=1&&d>=-1)?m_isDoorOpen = d: m_isDoorOpen=0; }

		void setBuffer(vector<int> v) { m_buffer = v; }

		int getCurrFloor() const { return m_currFloor; }
		int getNextFloor() const { return m_nextFloor; }
		int getDoor() const { return m_isDoorOpen; }
		int getId() const { return m_id; }
		vector<int> getBuffer() const{ return m_buffer; }

		void pickedFloor(int& choice,int numFloor) {
			
			m_buffer.push_back(choice);
			loadFloorFromBuffer();
			cout << "Picked floor: " << choice << endl;
		}
		
		void loadFloorFromBuffer() {
			if (m_buffer.size() > 0) {
				m_nextFloor = m_buffer[0];
			}
		}
		
		//check if escalator have floor in buffer and return this floor position in buffer
		int haveInBuffer(int floor) {
			for (int i = 0;i < m_buffer.size();i++) {
				if (m_buffer[i] == floor) {
					return i;
				}	
			}
			return -1;
		}


		void step() {
			int bufferPos = haveInBuffer(m_currFloor);
			
			//Destination reached = open door or close door clear buffer and load next destination
			if (bufferPos>=0) {
				//close door and clear all occurences in buffer
				if (m_isDoorOpen) {
					setDoor(0);
					while (bufferPos >= 0) {
						m_buffer.erase(m_buffer.begin() + bufferPos);
						bufferPos = haveInBuffer(m_currFloor);
					}
					loadFloorFromBuffer();
					return;
				}//open door if escalator is on destination floor
				else {
					if (m_buffer.size() > 0) {
						setDoor(1);
					}
				}
			}
			
			//Moving escalator if needed and door is closed
			if (m_nextFloor > m_currFloor&&m_isDoorOpen==0) {
				m_currFloor++;
			}

			if (m_nextFloor < m_currFloor && m_isDoorOpen==0) {
				m_currFloor--;
			}
		}
	};
}

#endif
