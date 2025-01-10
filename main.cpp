#include <iostream>
#include "elevatorsystem.hpp"

using std::cout, std::cin, std::endl;

//print initial menu
static void initialMenu(int *numFloors, int *numElevators) {
    cout << "Enter number of floors: ";
    cin >> *numFloors;
    cout << endl << "Enter number of elevators: ";
    cin >> *numElevators;
    cout << endl;
}

//print menu 
static void displayOption(int* choice) {
    cout << endl << "Which option you want to choose?" << endl;
    cout << "0. Close program." << endl;
    cout << "1. Pick floor in the elevator." << endl;
    cout << "2. Press button in the lobby." << endl;
    cout << "3. Next step." << endl;
    cin >> *choice;
}


int main()
{
    int userChoice{};
    int numElevators{};
    int numFloors{};

    initialMenu(&numFloors, &numElevators);

    //initialize system with given parameters
    jk::ElevatorSystem elevatorSystem(numFloors,numElevators);
    jk::Elevator *elevator = new jk::Elevator[elevatorSystem.getElevatorNum()];

    //set id for each elevator
    for (int i = 0; i < numElevators; i++) {
        elevator[i].setId(i, elevatorSystem.getElevatorNum());
    }

    //ask user for input and display floor plan
    while (1) {
        elevatorSystem.displayElevators(elevator);
        displayOption(&userChoice);
        
        int choosenElevator{};
        int choosenFloor{};
        int choosenDirection{};

        switch (userChoice) {
        case 0:
            return 0;
            break;
        case 1:
            cout << "Pick elevator (0-" << numElevators - 1 << ")" << endl;
            cin >> choosenElevator;
            cout << "Pick floor (0-" << numFloors - 1 << ")" << endl;
            cin >> choosenFloor;
            elevator[choosenElevator].pickedFloor(choosenFloor, elevatorSystem.getFloorNum());
            break;
        case 2:
            cout << "Pick floor (0-" << numFloors - 1 << ")" << endl;
            cin >> choosenFloor;
            cout << "Pick direction (1- UP , 0 - DOWN)" << endl;
            cin >> choosenDirection;
            choosenElevator = elevatorSystem.corridorButton(choosenFloor, choosenDirection, elevator);
            elevator[choosenElevator].pickedFloor(choosenFloor, elevatorSystem.getFloorNum());
            break;
        case 3:
            cout <<endl << "Stepped" << endl;
            for(int i = 0; i < elevatorSystem.getElevatorNum(); i++) {
                elevator[i].step();
            }
            break;
        default:
            break;

        }
    }
}
