#ifndef ELEVATORSYSTEM_HPP
#define ELEVATORSYSTEM_HPP

#include <iostream>
#include "elevator.hpp"
#include <string>

using std::cout, std::cin, std::endl, std::string;

namespace jk{
	class ElevatorSystem {
	private:
		int m_numElevators;
		int m_numFloors;
		string m_floorPlan;
	public:
		
		ElevatorSystem() :m_numElevators(2), m_numFloors(10){
			clearFloorPlan();
		}

		ElevatorSystem(int f = 10, int e =2){
			if (f > 2) {
				m_numFloors = f;
			}
			else {
				m_numFloors = 10;
			}

			if (e > 0) {
				m_numElevators = e;
			}
			else {
				m_numElevators = 2;
			}
			clearFloorPlan();
		}	

		void clearFloorPlan() {
			m_floorPlan.erase();
			for (int i = 0; i < m_numFloors;i++) {
				for (int j = 0; j < m_numElevators; j++) {
					m_floorPlan.append("X");
				}
				m_floorPlan.append("|");
				m_floorPlan.append(std::to_string(i % 10));
				m_floorPlan.append("\n");
			}
		}

		void setFloorNum(int f) { f>0 ? m_numFloors = f: m_numFloors = 10; }
		void setElevatorNum(int e) { e> 0 ? m_numElevators = e: m_numElevators = 2; }


		int getFloorNum() const { return m_numFloors; }
		int getElevatorNum() const { return m_numElevators; }
		string getFloorPlan() const { return m_floorPlan; }

		int corridorButton(int& floor, int& dir, Elevator* e) {
			std::cout << "Pushed button"<<endl;
			vector<int> timeToWait = {};
			vector<int> ID = {};
			int tempID = 0;

			//check if any free elevator is here and pick this elevator
			for (int i = 0; i < m_numElevators; i++) {
				if (isElevatorHere(floor, e[i]) == 1 && size(e[i].getBuffer()) == 0) {
					return i;
				}
			}

			cout << "checked free elevators"<<endl;
			
			for (int i = 0; i < m_numElevators;i++) {
				int bufferSize = size(e[i].getBuffer());
				int door = e[i].getDoor();
				if (dir==1) {
				//check elevators below me that goes above me
					if ((e[i].getCurrFloor() < e[i].getNextFloor())
						&&(e[i].getNextFloor()>=floor)&&(e[i].getCurrFloor()<floor)) {
						timeToWait.push_back(abs(e[i].getCurrFloor()-floor));
						ID.push_back(i);
						//check if elevator will start now, or in next step and add time to list
						if (door) {
							timeToWait.at(i)++;
						}
						//cout << i << ": " << timeToWait[i] << " \t";
					}
				} else if(dir==0){
				//check elevators above me that goes below me
					if ((e[i].getCurrFloor() > e[i].getNextFloor())
						&& (e[i].getNextFloor() <= floor) && (e[i].getCurrFloor() > floor)) {
						timeToWait.push_back(abs(e[i].getCurrFloor() - floor));
						ID.push_back(i);
						//check if elevator will start now, or in next step and add time to list
						if (door) {
							timeToWait.at(i)++;
						}
					}
				}
			//check free elevators distance or elevator that will get free next step
				if (bufferSize <= 1 && e[i].getNextFloor() == e[i].getCurrFloor()) {
					//save each elevator distance and additional time needed for elevator to start
					timeToWait.push_back(abs(e[i].getCurrFloor() - floor) + bufferSize);
					//add time if door will open in next step
					if (bufferSize == 1 && door == 0) {
						timeToWait.at(i)++;
					}
					ID.push_back(i);
					//cout << "f: "<< i << ": " << timeToWait[i] << " \t";
				}
			}


			//check all elevators with calculated time and pick the best
			if (size(timeToWait) > 0) {
				cout << endl << endl;
				vector<int> sameTimeID = {};
				int bestTime = timeToWait[0];
				tempID = ID[0];

				for (int i = 0; i < size(timeToWait);i++) {
					if (timeToWait[i] < bestTime) {
						tempID = ID[i];
						bestTime = timeToWait[i];
					}
					cout << i << ": " << timeToWait[i] << " \t";
				}
				//check if there are multiple choices with same time
				//pick elevator with the shortest buffer
				for (int i = 0; i < size(timeToWait);i++) {
					if (timeToWait[i] == bestTime) {
						sameTimeID.push_back(ID[i]);
					}
				}
				if (size(sameTimeID) > 0) {
					for (int i = 0;i < size(sameTimeID);i++) {
						int shortestBuffer = size(e[sameTimeID[i]].getBuffer());
						if (size(e[sameTimeID[i]].getBuffer()) < shortestBuffer) {
							tempID = sameTimeID[i];
							shortestBuffer = size(e[sameTimeID[i]].getBuffer());
						}
					}
				}

				cout << endl << endl << "Picked elevator: " << tempID << endl << endl;
				return tempID;
			}


			//if none of the elevators met above conditions just pick the elevator with shortest buffer
			for (int i = 0;i < m_numElevators;i++) {
				int shortestBuffer = size(e[i].getBuffer());
				if (size(e[i].getBuffer()) < shortestBuffer) {
					tempID = i;
					shortestBuffer = size(e[i].getBuffer());
				}
			}
			return tempID;
		}

		int isElevatorHere(int floor, Elevator& e) {
			if (e.getCurrFloor() == floor) {
				return 1;
			}
			return -1;
		}

		void displayElevators(Elevator* e) {
			clearFloorPlan();
			int size = m_floorPlan.length();
			for (int i = 0; i < m_numFloors; i++) {
				for (int id = 0; id < m_numElevators; id++) {
					int isHere = isElevatorHere(i, e[id]);
					string status = e[id].getDoor() ? "O": "E";
					if (isHere + 1) {
						int position = (i * (m_numElevators+3) + id);
						m_floorPlan.erase(position, 1);
						m_floorPlan.insert(position, status);
					}
				}
			}
			cout << endl<< "Floor plan:" << endl;
			cout << m_floorPlan;
		}
	};
}

#endif