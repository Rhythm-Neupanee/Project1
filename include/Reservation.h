#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
//stores information about one reservation
class Reservation {
private:
    std::string reservationID; //unique reservation ID
    std::string studentID; //ID of the student
    std::string studentName; //name of the student
    std::string resourceID; //ID of the reserved resource
    std::string date; //reservation date

public:
    Reservation() = default; //default constructor

    //constructor that initializes all reservation information
    Reservation(std::string reservationID, std::string studentID, std::string studentName, std::string resourceID, std::string date);

    //getter functions return reservation information
    std::string getReservationID() const;
    std::string getStudentID() const;
    std::string getStudentName() const;
    std::string getResourceID() const;
    std::string getDate() const;

    //displays the reservation information
    void display() const;
};

//represents one node in the binary search tree
struct ReservationNode {
    Reservation data;
    ReservationNode* left;
    ReservationNode* right;

    //initializes the node with reservation data and empty children 
    ReservationNode(const Reservation& res)
        : data(res), left(nullptr), right(nullptr) {}
};

//manage reservations using a binary seatvh tree
class ReservationList {
private:
    ReservationNode* root; //points to the first node to the tree

    ReservationNode* insertNode(ReservationNode* node, const Reservation& res); //inserts reservation in the correct position by ID

    ReservationNode* findNode(ReservationNode* node, const std::string& reservationID) const; //searches for reservation by ID

    ReservationNode* removeNode(ReservationNode* node, const std::string& reservationID); //removes a reservation while maintaining a BST ordering

    ReservationNode* findMin(ReservationNode* node) const; //finds the smallest ID in a subtree 

    void destroyTree(ReservationNode* node); //deletes all nodes to prevent memory leaks 

    void displayInOrder(ReservationNode* node) const; //displays reservations in ascending ID order

public:

    ReservationList(); //creates an empty reservation tree

    ~ReservationList(); //frees the trees dynamically allocated notes 

    //prevents copying the tree, which could cause memory errors
    ReservationList(const ReservationList&) = delete;
    ReservationList& operator=(const ReservationList&) = delete;

    //adds a reservation to the tree
    void addReservation(const Reservation& res);

    //removes reservation and saves information
    //returns true if found and renewed, false if anything else
    bool removeReservation(const std::string& reservationID,Reservation& removedReservation);

    //returns a pointer to the reservation if found
    //returns nullptr if the reservation does not exist
    Reservation* findReservation(const std::string& reservationID) const;

    //displays all reservation in ascending ID order 
    void displayAllReservations() const;

    //returns true if the tree is empty
    bool isEmpty() const;
};

#endif
