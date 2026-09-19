#include "../include/ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Initialize counter so generated IDs start at R101
ReservationManager::ReservationManager() : reservationCounter(101) {}

// Read available resources from the file
bool ReservationManager::loadResourcesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string id, name, type, availabilityStr;

        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, type, '|');
        std::getline(iss, availabilityStr);

        // remove windows newline carriage returns if present
        if (!availabilityStr.empty() && availabilityStr.back() == '\r') {
            availabilityStr.pop_back();
        }

        bool availability = (availabilityStr == "Available");
        resources.emplace_back(id, name, type, availability);
    }
    file.close();
    std::cout << "Resources loaded successfully from " << filename << std::endl;
    return true;
}

//read existing reservations and update affected resources/counters
bool ReservationManager::loadReservationsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string resID, studentID, studentName, resourceID, date;

        std::getline(iss, resID, '|');
        std::getline(iss, studentID, '|');
        std::getline(iss, studentName, '|');
        std::getline(iss, resourceID, '|');
        std::getline(iss, date);

        if (!date.empty() && date.back() == '\r') date.pop_back();

        std::string fullResID = "R" + resID;
        Reservation newReservation(fullResID, studentID, studentName, resourceID, date);
        activeReservations.addReservation(newReservation);

        //mark assigned resources as taken
        for (auto& res : resources) {
            if (res.getId() == resourceID) {
                res.setAvailability(false);
                break;
            }
        }
        //prevent duplicate IDs
        int idNum = std::stoi(resID);
        if (idNum >= reservationCounter) reservationCounter = idNum + 1;
    }
    file.close();
    std::cout << "Reservations loaded successfully from " << filename << std::endl;
    return true;
}

void ReservationManager::displayResources() const {
    if (resources.empty()) {
        std::cout << "No resources available.\n";
        return;
    }
    std::cout << "\n Resources Inventory:\n";
    for (const auto& resource : resources) {
        resource.display();
    }
}

// Reserve a resource directly if open, or queue the student if it's currently taken
void ReservationManager::createReservation(const std::string& studentID, const std::string& studentName, const std::string& resourceID, const std::string& date) {
    Resource* resource = nullptr;
    for (auto& res : resources) {
        if (res.getId() == resourceID) {
            resource = &res;
            break;
        }
    }
    if (!resource) {
        std::cout << "Error: Resource with ID " << resourceID << " not found.\n";
        return;
    }
    if (resource->getAvailability()) {
        resource->setAvailability(false);
        std::string reservationID = "R" + std::to_string(reservationCounter++);
        Reservation newReservation(reservationID, studentID, studentName, resourceID, date);
        activeReservations.addReservation(newReservation);
        std::cout << "Reservation created successfully. Reservation ID: " << reservationID << "\n";
    } else {
        std::cout << "Resource is unavailable. Adding to waiting list.\n";
        resource->getWaitingQueue().enqueue(studentID, studentName);
        std::cout << "Student " << studentName << " (ID: " << studentID << ") added to waiting list.\n";
    }
}

//cancel active booking and pass resource to the next waiting person
void ReservationManager::cancelReservation(const std::string& reservationID) {
    Reservation removedReservation;
    Resource* resource = nullptr;
    std::string resourceID;
    if (activeReservations.removeReservation(reservationID, removedReservation)) {
        cancellationHistory.push(removedReservation);
        std::cout << "Reservation " << reservationID << " canceled successfully.\n";

        resourceID = removedReservation.getResourceID();
        for (auto& res : resources) {
            if (res.getId() == resourceID) {
                resource = &res;
                break;
            }
        }
    } else {
        std::cout << "Error: Reservation with ID " << reservationID << " not found.\n";
        return;
    }

    //assign to waitlisted student , otherwise mark resource as available
    std::string nextStudentID, nextStudentName;
    if (resource && resource->getWaitingQueue().dequeue(nextStudentID, nextStudentName)) {
        std::string newReservationID = "R" + std::to_string(reservationCounter++);
        Reservation newReservation(newReservationID, nextStudentID, nextStudentName, resourceID, removedReservation.getDate());
        activeReservations.addReservation(newReservation);
        std::cout <<"Resource automatically assigned to waiting student " << nextStudentName << " (New ID: " << newReservationID << ")\n";
    } else if (resource) {
        resource->setAvailability(true);
    }
}

//restore the last cancelled booking if the resource is still free
void ReservationManager::undoCancellation() {
    Reservation reservationToRestore;
    if (!cancellationHistory.pop(reservationToRestore)) {
        std::cout << "No cancellations to undo.\n";
        return;
    }
    Resource* resource = nullptr;
    for (auto& res : resources) {
        if (res.getId() == reservationToRestore.getResourceID()) {
            resource = &res;
            break;
        }
    }
    if (resource && resource->getAvailability()) {
        resource->setAvailability(false);
        activeReservations.addReservation(reservationToRestore);
        std::cout << "Reservation " << reservationToRestore.getReservationID() << " restored successfully.\n";
    } else {
        std::cout << "Cannot undo cancellation. Resource " << reservationToRestore.getResourceID() << " is currently unavailable.\n";
    }
}

void ReservationManager::displayActiveReservations() const {
    std::cout << "\nActive Reservations:\n";
    activeReservations.displayAllReservations();
}

void ReservationManager::displayWaitingLists() const {
    std::cout << "\nWaiting Lists:\n";
    for (const auto& resource : resources) {
         resource.displayWaitingQueue();
    }
}

void ReservationManager::displayCancellationHistory() const {
    std::cout << "\nCancellation History:\n";
    cancellationHistory.display();
}
