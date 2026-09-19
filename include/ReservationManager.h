#ifndef ReservationManager_h
#define ReservationManager_h

#include "Reservation.h"
#include <map>
#include <string>
#include <vector>
#include "Resource.h"
#include "WaitingList.h"
#include "CancellationHistory.h"

class ReservationManager {
private:
    std::vector<Resource> resources; // list of resources
    ReservationList activeReservations; // list of active reservations
    CancellationHistory cancellationHistory; // stack for cancellation history
    int reservationCounter; // counter to generate unique reservation IDs

public:
    ReservationManager();
    
    bool loadResourcesFromFile(const std::string& filename); // Load resources from a file
    bool loadReservationsFromFile(const std::string& filename);
    void displayResources() const; // Display all resources
    void createReservation(const std::string& studentID, const std::string& studentName, const std::string& resourceID, const std::string& date); // Create a new reservation
    void cancelReservation(const std::string& reservationID); // Cancel an existing reservation
    void undoCancellation(); // Undo the most recent cancellation
    void displayActiveReservations() const; // Display all active reservations
    void displayWaitingLists() const; // Display all waiting lists
    void displayCancellationHistory() const; // Display the cancellation history

};
#endif
