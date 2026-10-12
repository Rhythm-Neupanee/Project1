#include <iostream>
#include <limits>
#include <string>
#include "../include/ReservationManager.h"

// Function to display the main menu
static void displayMenu() {
    std::cout << "\n--- Campus Resource Reservation System ---\n";
    std::cout << "1. View Resources (Unsorted)\n";
    std::cout << "2. View resources (Sorted)\n";
    std::cout << "3. Create Reservation\n";
    std::cout << "4. Cancel Reservation\n";
    std::cout << "5. View Active Reservations\n";
    std::cout << "6. View Active Reservations (Sorted)\n";
    std::cout << "7. View Waiting Lists\n";
    std::cout << "8. Undo Cancellation\n";
    std::cout << "9. View Cancellation History\n";
    std::cout << "10. Save and Exit\n";
    std::cout << "11. Report: Resource Utilization\n";
    std::cout << "12. Report: Most Requested Resources\n";
    std::cout << "13. Report: Waiting List Statistics\n";
    std::cout << "14. Search Resource by ID\n";
    std::cout << "15. Search Reservation by ID\n";
    std::cout << "Enter Choice: ";
}

int main() {
    ReservationManager manager;
    manager.loadResourcesFromFile("data/resources.txt");   // Load resources from a file
    manager.loadReservationsFromFile("data/reservations.txt");

    int choice =0;
    while (true) {
        displayMenu();
        // Validate user input
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 15.\n";
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            continue;
        }

        if (choice == 10) {
            std::cout << "Saving changes to data files.\n";
            bool resSaved = manager.saveResourcesToFile("data/resources.txt");
            bool revSaved = manager.saveReservationsToFile("data/reservations.txt");
            if (resSaved && revSaved) {
                std::cout << "Data saved. Exiting the program. Goodbye!\n";
            } else {
                std::cout << "Data not saved. Exiting the program.\n";
            }
            break;
        }
        std::string studentID, studentName, resourceID, date, reservationID; // Variables to hold user input
        // Handle user choices
        switch (choice) {
            case 1:
                manager.displayResources();
                break;
            case 2:
                manager.displayResourcesSortedById();
                break;
            case 3:
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
            case 4:
                std::cout << "Enter Reservation ID to cancel: ";
                std::cin >> reservationID;
                manager.cancelReservation(reservationID);
                break;
            case 5:
                manager.displayActiveReservations();
                break;
            case 6:
                manager.displayReservationsSortedByMergeSort();
                break;
            case 7:
                manager.displayWaitingLists();
                break;
            case 8:
                manager.undoCancellation();
                break;
            case 9:
                manager.displayCancellationHistory();
                break;
            case 11:
                manager.generateResourceUtilizationReport();
                break;
            case 12:
                manager.generateMostRequestedResourcesReport();
                break;
            case 13:
                manager.generateWaitingListStatisticsReport();
                break;
            case 14:
                manager.searchResourceById();
                break;
            case 15:
                manager.searchReservationById();
                break;
            default:
                std::cout << "Invalid choice. Please select a number between 1 and 8.\n";
        }
    }
    return 0;
}
