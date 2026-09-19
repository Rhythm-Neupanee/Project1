#include <iostream>
#include <limits>
#include <string>
#include "../include/ReservationManager.h"

// Function to display the main menu
static void displayMenu() {
    std::cout << "\n--- Campus Resource Reservation System ---\n";
    std::cout << "1. View Resources\n";
    std::cout << "2. Create Reservation\n";
    std::cout << "3. Cancel Reservation\n";
    std::cout << "4. View Active Reservations\n";
    std::cout << "5. View Waiting Lists\n";
    std::cout << "6. Undo Cancellation\n";
    std::cout << "7. View Cancellation History\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter Choice: ";
}

int main() {
    ReservationManager manager;
    manager.loadResourcesFromFile("../data/resources.txt");   // Load resources from a file
    manager.loadReservationsFromFile("../data/reservations.txt");

    int choice =0;
    while (true) {
        displayMenu();
        // Validate user input
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            continue;
        }

        if (choice == 8) {
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        }
        std::string studentID, studentName, resourceID, date, reservationID; // Variables to hold user input
        // Handle user choices
        switch (choice) {
            case 1:
                manager.displayResources();
                break;
            case 2:
                std::cout << "Enter Student ID: ";
                std::cin >> studentID;
                std::cout << "Enter Student Name: ";
                std::cin.ignore(); // Ignore the newline character left in the buffer
                std::getline(std::cin, studentName);
                std::cout << "Enter Resource ID: ";
                std::cin >> resourceID;
                std::cout << "Enter Reservation Date (mm/dd/yyyy): ";
                std::cin >> date;
                manager.createReservation(studentID, studentName, resourceID, date);
                break;
            case 3:
                std::cout << "Enter Reservation ID to cancel: ";
                std::cin >> reservationID;
                manager.cancelReservation(reservationID);
                break;
            case 4:
                manager.displayActiveReservations();
                break;
            case 5:
                manager.displayWaitingLists();
                break;
            case 6:
                manager.undoCancellation();
                break;
            case 7:
                manager.displayCancellationHistory();
                break;
            default:
                std::cout << "Invalid choice. Please select a number between 1 and 8.\n";
        }
    }
    return 0;
}
