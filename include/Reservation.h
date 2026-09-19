#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <utility>

// represents a reservation made by students
class Reservation {
private:
    std::string reservationID; // unique id of the reservation
    std::string studentID; // unique id of the student making the reservation
    std::string studentName; // name of the student making the reservation 
    std::string resourceID; // unique id of the resource being reserved
    std::string date; // date of the reservation

public:
    Reservation(); // default constructor
    Reservation( std::string reservationID,  std::string studentID, std::string studentName,  std::string resourceID,  std::string date);

    // getting the value
    [[nodiscard]] std::string getReservationID() const;
    [[nodiscard]] std::string getStudentID() const;
    [[nodiscard]] std::string getStudentName() const;
    [[nodiscard]] std::string getResourceID() const;
    [[nodiscard]] std::string getDate() const;

    void display() const; // display the reservation information
};

//structure for custom linked list
struct ReservationNode {
    Reservation data; // reservation data
    ReservationNode* next; // pointer to the next node in the list

    ReservationNode(Reservation res) : data(std::move(res)), next(nullptr) {} // constructor to initialize the node with reservation data
};

// linked list class to store reservations
class ReservationList {
private:
    ReservationNode* head; // pointer to the head of the linked list
public:
    ReservationList(); // default constructor
    ~ReservationList(); // destructor to free memory

    void addReservation(const Reservation& res); // add a reservation to the list
    bool removeReservation(const std::string& reservationID, Reservation& removedReservation); // remove a reservation from the list by ID
    Reservation* findReservation(const std::string& reservationID) const; // find a reservation by ID
    void displayAllReservations() const; // display all reservations in the list
    [[nodiscard]] bool isEmpty() const; // check if the list is empty
};

#endif
