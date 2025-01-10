#ifndef ELEVATORSYSTEM_HPP
#define ELEVATORSYSTEM_HPP


#include "elevator.hpp"
#include <iostream>

#include <string>
#include <vector>

using std::cout, std::cin, std::endl, std::string, std::vector;

namespace jk {
    class Elevator;
    /**
     * @brief Represents the elevator system, managing multiple elevators and floors.
     */
    class ElevatorSystem {
    private:
        int m_numElevators;        ///< Number of elevators in the system.
        int m_numFloors;           ///< Number of floors in the building.
        string m_floorPlan;        ///< Visual representation of the floor plan.

    public:
        /**
         * @brief Default constructor. Initializes with 2 elevators and 10 floors.
         */
        ElevatorSystem();

        /**
         * @brief Parameterized constructor. Initializes with custom number of elevators and floors.
         * @param f Number of floors. Defaults to 10 if invalid.
         * @param e Number of elevators. Defaults to 2 if invalid.
         */
        ElevatorSystem(int f, int e);

        /**
         * @brief Clears and rebuilds the floor plan.
         */
        void clearFloorPlan();

        /**
         * @brief Sets the number of floors in the building.
         * @param f Number of floors.
         */
        void setFloorNum(int f);

        /**
         * @brief Sets the number of elevators in the system.
         * @param e Number of elevators.
         */
        void setElevatorNum(int e);

        /**
         * @brief Gets the number of floors.
         * @return Number of floors.
         */
        int getFloorNum() const;

        /**
         * @brief Gets the number of elevators.
         * @return Number of elevators.
         */
        int getElevatorNum() const;

        /**
         * @brief Gets the current floor plan.
         * @return Floor plan as a string.
         */
        string getFloorPlan() const;

        /**
         * @brief Handles corridor button press to call an elevator.
         * @param floor The floor where the button was pressed.
         * @param dir Direction (1 for up, 0 for down).
         * @param e Array of elevators in the system.
         * @return ID of the selected elevator.
         */
        int corridorButton(int& floor, int& dir, Elevator* e);

        /**
         * @brief Checks if an elevator is on the specified floor.
         * @param floor Floor to check.
         * @param e Elevator instance.
         * @return 1 if elevator is on the floor, -1 otherwise.
         */
        int isElevatorHere(int floor, Elevator& e);

        /**
         * @brief Displays the current positions and statuses of all elevators.
         * @param e Array of elevators in the system.
         */
        void displayElevators(Elevator* e);
    };
}

#endif