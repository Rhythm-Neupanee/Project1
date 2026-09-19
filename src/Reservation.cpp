#include "../include/Reservation.h"
#include <iostream>
#include <utility>

Reservation::Reservation() = default; // default constructor
Reservation::Reservation(std::string reservationID, std::string studentID, std::string studentName, std::string resourceID, std::string date)
    : reservationID(std::move(reservationID)), studentID(std::move(studentID)), studentName(std::move(studentName)), resourceID(std::move(resourceID)), date(std::move(date)) {} // parameterized constructor

std::string Reservation::getReservationID() const { return reservationID; } // returns the unique id of the reservation
std::string Reservation::getStudentID() const { return studentID; } // returns the unique id of the student making the reservation
std::string Reservation::getStudentName() const { return studentName; } // returns the name of the student making the reservation
std::string Reservation::getResourceID() const { return resourceID; } // returns the unique id of the resource being reserved
std::string Reservation::getDate() const { return date; } // returns the date of the reservation

void Reservation::display() const {
    std::cout << "Res ID: " << reservationID
              << " | Student: " << studentName << " (ID: " << studentID << ")"
              << " | Resource ID: " << resourceID
              << " | Date: " << date << "\n";
}

//linked list implementation for ReservationList
ReservationList::ReservationList() : head(nullptr) {} // default constructor

//destructor
ReservationList::~ReservationList() {
    ReservationNode* current = head;
    while (current != nullptr) {
        ReservationNode* nextNode = current->next; // store the next node before deleting
        delete current;
        current = nextNode;
    }
}

//insert a new reservation into the central linked list
void ReservationList::addReservation(const Reservation& res) {
    auto* newNode = new ReservationNode(res); // create a new node with the reservation data
    newNode->next = head;
    head = newNode;
}

//remove a reservation from the linked list by its unique id
bool ReservationList::removeReservation(const std::string& reservationID, Reservation& removedReservation) {
    if (head == nullptr) return false;

    if (head->data.getReservationID() == reservationID) {
        ReservationNode* temp = head; // store the current head
        removedReservation = head->data; // store the removed reservation
        head = head->next; // update the head to the next node
        delete temp;
        return true;
    }
    // traverse the list to find the reservation to remove
    ReservationNode* current = head;
    while (current->next != nullptr && current->next->data.getReservationID() != reservationID) {
        current = current->next; // move to the next node
    }

    if (current->next == nullptr) {
        return false; // indicate that the reservation was not found
    }

    ReservationNode* temp = current->next;
    removedReservation = temp->data;
    current->next = temp->next;
    delete temp;
    return true;
}

Reservation* ReservationList::findReservation(const std::string& reservationID) const {
    ReservationNode* current = head;
    while (current != nullptr) {
        if (current->data.getReservationID() == reservationID) {
            return &(current->data);
        }
        current = current->next; // move to the next node
    }
    return nullptr;
}

void ReservationList::displayAllReservations() const {
    if (head == nullptr) {
        std::cout << "No reservations found.\n"; // if the list is empty, display a message
        return;
    }
    ReservationNode* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

bool ReservationList::isEmpty() const {
    return head == nullptr;
}
