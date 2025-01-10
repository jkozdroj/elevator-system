/**
 * @file elevator.hpp
 * @brief Definition of the Elevator class for managing a single elevator.
 * 
 * The Elevator class provides functionality to operate a single elevator
 * within the system, including moving between floors, managing doors, and 
 * handling a buffer of requested floors.
 */

#ifndef ELEVATOR_HPP
#define ELEVATOR_HPP

#include <iostream>
#include "elevatorsystem.hpp"
#include <vector>

/**
 * @namespace jk
 * @brief Contains classes and functions for the elevator management system.
 */
namespace jk {

/**
 * @class Elevator
 * @brief Represents a single elevator in the system.
 * 
 * The Elevator class models an elevator with functionality to:
 * - Move between floors.
 * - Open and close doors.
 * - Manage a buffer of floor requests.
 */
class Elevator {
private:
    int m_id; ///< Unique identifier for the elevator.
    int m_currFloor; ///< The current floor of the elevator.
    int m_nextFloor; ///< The next destination floor of the elevator.
    int m_isDoorOpen; ///< Status of the elevator door (0 = closed, 1 = open).
    std::vector<int> m_buffer; ///< Buffer containing requested floors.

public:
    /**
     * @brief Parameterized constructor to initialize the elevator.
     * @param id Unique identifier for the elevator.
     * @param cf Current floor of the elevator.
     * @param nf Next destination floor of the elevator.
     * @param d Initial door status (0 = closed, 1 = open).
     * @param b Initial buffer of requested floors.
     */
    Elevator(int id, int cf, int nf, int d, std::vector<int> b);

    /**
     * @brief Default constructor initializing with default values.
     */
    Elevator();

    /**
     * @brief Sets the elevator ID.
     * @param id The ID to set.
     * @param e The maximum allowed ID.
     */
    void setId(int id, int e);

    /**
     * @brief Sets the current floor of the elevator.
     * @param f The floor to set.
     * @param e The total number of floors.
     */
    void setCurrFloor(int f, int e);

    /**
     * @brief Sets the next destination floor of the elevator.
     * @param f The floor to set.
     * @param numFloor Total number of floors.
     */
    void setNextFloor(int f, int numFloor);

    /**
     * @brief Sets the door status of the elevator.
     * @param d Door status to set (0 = closed, 1 = open).
     */
    void setDoor(int d);

    /**
     * @brief Updates the buffer with a new list of floor requests.
     * @param v Vector of requested floors.
     */
    void setBuffer(std::vector<int> v);

    /**
     * @brief Gets the current floor of the elevator.
     * @return Current floor.
     */
    int getCurrFloor() const;

    /**
     * @brief Gets the next destination floor of the elevator.
     * @return Next floor.
     */
    int getNextFloor() const;

    /**
     * @brief Gets the door status of the elevator.
     * @return Door status (0 = closed, 1 = open).
     */
    int getDoor() const;

    /**
     * @brief Gets the ID of the elevator.
     * @return Elevator ID.
     */
    int getId() const;

    /**
     * @brief Gets the buffer of requested floors.
     * @return Vector containing requested floors.
     */
    std::vector<int> getBuffer() const;

    /**
     * @brief Adds a floor to the buffer and processes it.
     * @param choice The floor to add.
     * @param numFloor Total number of floors.
     */
    void pickedFloor(int& choice, int numFloor);

    /**
     * @brief Loads the next floor from the buffer into the destination floor.
     */
    void loadFloorFromBuffer();

    /**
     * @brief Checks if a floor exists in the buffer.
     * @param floor The floor to check.
     * @return Position of the floor in the buffer or -1 if not found.
     */
    int haveInBuffer(int floor);

    /**
     * @brief Moves the elevator one step towards the next destination.
     * 
     * Handles door operations, buffer management, and movement between floors.
     */
    void step();
};

} 

#endif