#include "../include/ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor, starts generating IDs from R101
ReservationManager::ReservationManager() : reservationCounter(101) {}

// Reads the resources text file and loads them into the vector
bool ReservationManager::loadResourcesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // skip blank lines

        std::istringstream iss(line);
        std::string id, name, type, availabilityStr;

        // split the line using the pipe delimiter
        std::getline(iss, id, '|');
        std::getline(iss, name, '|');
        std::getline(iss, type, '|');
        std::getline(iss, availabilityStr);

        // clean up windows newline carriage returns just in case
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

// Overwrites the resource text file with the current memory state
bool ReservationManager::saveResourcesToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    // write each resource back using the pipe format
    for (const auto& res : resources) {
        file << res.getId() << "|"
             << res.getName() << "|"
             << res.getType() << "|"
             << (res.getAvailability() ? "Available" : "Reserved") << "\n";
    }
    file.close();
    return true;
}

// Saves active reservations back to the text file so we don't lose data on exit
bool ReservationManager::saveReservationsToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    std::vector<Reservation> resList;
    activeReservations.collectAll(resList); // grab everything from the BST

    for (const auto& res : resList) {
        std::string ID = res.getReservationID();

        // strip the 'R' off before saving to match the original file format
        if (!ID.empty() && ID[0] == 'R') {
            ID = ID.substr(1);
        }

        file << ID << "|"
             << res.getStudentID() << "|"
             << res.getStudentName() << "|"
             << res.getResourceID() << "|"
             << res.getDate() << "\n";
    }
    file.close();
    return true;
}

// Reads the reservations file and rebuilds the BST
bool ReservationManager::loadReservationsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

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

        // add the 'R' back onto the ID so it displays correctly
        std::string fullResID = "R" + resID;
        Reservation newReservation(fullResID, studentID, studentName, resourceID, date);
        activeReservations.addReservation(newReservation);

        // mark the associated resource as taken since it's already booked
        for (auto& res : resources) {
            if (res.getId() == resourceID) {
                res.setAvailability(false);
                break;
            }
        }

        // update the counter so we don't accidentally reuse an old ID
        int idNumber = std::stoi(resID);
        if (idNumber >= reservationCounter) reservationCounter = idNumber + 1;
    }
    file.close();
    return true;
}

void ReservationManager::displayResources() const { // Prints all resources as-is
    if (resources.empty()) {
        std::cout << "No resources available.\n";
        return;
    }
    std::cout << "\n Resources Inventory:\n";
    for (const auto& resource : resources) {
        resource.display();
    }
}

void ReservationManager::displayResourcesSortedById() { // Sorts the resources before printing
    std::vector<Resource*> resList;

    // gather pointers to the resources
    for (auto& res : resources) {
        resList.push_back(&res);
    }

    // sort them using our custom algorithm
    Resource::mergeSortResources(resList);

    std::cout << "\n Sorted by ID:\n";
    for (const auto& res : resList) {
        res->display();
    }
}

void ReservationManager::displayReservationsSortedByMergeSort() { // Prints reservations using the BST merge sort
    std::cout << "\n Sorted by Merge Sort:\n";
    activeReservations.displayReservationsMergeSort();
}

// Try to make a new reservation or add them to the queue
void ReservationManager::createReservation(const std::string& studentID, const std::string& studentName, const std::string& resourceID, const std::string& date) {
    Resource* resource = nullptr;

    // look up the requested resource
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
        // resource is free, reserve it right away
        resource->setAvailability(false);
        std::string reservationID = "R" + std::to_string(reservationCounter++);
        Reservation newReservation(reservationID, studentID, studentName, resourceID, date);
        activeReservations.addReservation(newReservation);

        std::cout << "Reservation created successfully. Reservation ID: " << reservationID << "\n";
    } else {
        // resource is taken, throw the student on the waitlist
        std::cout << "Resource is unavailable. Adding to waiting list.\n";
        resource->getWaitingQueue().enqueue(studentID, studentName);
        std::cout << "Student " << studentName << " (ID: " << studentID << ") added to waiting list.\n";
    }
}

// Cancels a reservation and passes the resource to the next waiting person
void ReservationManager::cancelReservation(const std::string& reservationID) {
    Reservation removedReservation;
    Resource* resource = nullptr;
    std::string resourceID;

    // remove from the BST and push the deleted data to the undo stack
    if (activeReservations.removeReservation(reservationID, removedReservation)) {
        cancellationHistory.push(removedReservation);
        std::cout << "Reservation " << reservationID << " canceled successfully.\n";

        resourceID = removedReservation.getResourceID();

        // find the resource that was just freed up
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

    std::string nextStudentID, nextStudentName;

    // if someone is waiting, give it to them automatically
    if (resource && resource->getWaitingQueue().dequeue(nextStudentID, nextStudentName)) {
        std::string newReservationID = "R" + std::to_string(reservationCounter++);
        Reservation newReservation(newReservationID, nextStudentID, nextStudentName, resourceID, removedReservation.getDate());
        activeReservations.addReservation(newReservation);

        std::cout <<"Resource automatically assigned to waiting student " << nextStudentName << " (New ID: " << newReservationID << ")\n";
    } else if (resource) {
        // nobody was waiting, mark it available again
        resource->setAvailability(true);
    }
}

// Restores the last canceled reservation if the resource is still free
void ReservationManager::undoCancellation() {
    Reservation reservationToRestore;

    // grab the last canceled booking
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
        // resource is still free, put the reservation back in the active tree
        resource->setAvailability(false);
        activeReservations.addReservation(reservationToRestore);
        std::cout << "Reservation " << reservationToRestore.getReservationID() << " restored successfully.\n";
    } else {
        std::cout << "Cannot undo cancellation. Resource " << reservationToRestore.getResourceID() << " is currently unavailable.\n";
    }
}

void ReservationManager::displayActiveReservations() const { // display using BST in-order traversal
    std::cout << "\nActive Reservations:\n";
    activeReservations.displayAllReservations();
}

void ReservationManager::displayWaitingLists() const { // display all queues
    std::cout << "\nWaiting Lists:\n";
    for (const auto& resource : resources) {
         resource.displayWaitingQueue();
    }
}

void ReservationManager::displayCancellationHistory() const { // display the undo stack
    std::cout << "\nCancellation History:\n";
    cancellationHistory.display();
}
