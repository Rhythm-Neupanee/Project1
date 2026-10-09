
#include "../include/Reservation.h"
#include <iostream>
#include <utility>

// Parameterized constructor: initializes reservation information
Reservation::Reservation(std::string reservationID, std::string studentID, std::string studentName, std::string resourceID, std::string date)
    : reservationID(std::move(reservationID)), studentID(std::move(studentID)), studentName(std::move(studentName)), resourceID(std::move(resourceID)), date(std::move(date)) {}

// Getter functions: return reservation information
std::string Reservation::getReservationID() const {
    return reservationID;
}

std::string Reservation::getStudentID() const {
    return studentID;
}

std::string Reservation::getStudentName() const {
    return studentName;
}

std::string Reservation::getResourceID() const {
    return resourceID;
}

std::string Reservation::getDate() const {
    return date;
}

// Displays all information about one reservation
void Reservation::display() const {
    std::cout << "Res ID: " << reservationID<< " | Student: " << studentName << " (ID: " << studentID << ")" << " | Resource ID: " << resourceID << " | Date: " << date << "\n";
}

// Binary Search Tree implementation for ReservationList

// Constructor: starts with an empty tree
ReservationList::ReservationList() : root(nullptr) {}

// Destructor: deletes all nodes to prevent memory leaks
ReservationList::~ReservationList() {
    destroyTree(root);
}

// Recursively deletes every node in the tree
void ReservationList::destroyTree(ReservationNode* node) {
    if (node == nullptr) {
        return;
    }

    // Delete the left and right subtrees first
    destroyTree(node->left);
    destroyTree(node->right);

    // Delete the current node after its children
    delete node;
}

// Inserts a reservation based on its reservation ID
ReservationNode* ReservationList::insertNode(
    ReservationNode* node, const Reservation& res) {

    // Create a new node when an empty position is found
    if (node == nullptr) {
        return new ReservationNode(res);
    }

    // Smaller IDs go into the left subtree
    if (res.getReservationID() < node->data.getReservationID()) {
        node->left = insertNode(node->left, res);
    }
    // Larger IDs go into the right subtree
    else if (res.getReservationID() > node->data.getReservationID()) {
        node->right = insertNode(node->right, res);
    }

    // Duplicate IDs are ignored
    return node;
}

// Adds a reservation to the tree
void ReservationList::addReservation(const Reservation& res) {
    root = insertNode(root, res);
}

// Searches for a reservation using its ID
ReservationNode* ReservationList::findNode(
    ReservationNode* node, const std::string& reservationID) const {

    // Stop if the node is empty or the ID matches
    if (node == nullptr ||
        node->data.getReservationID() == reservationID) {
        return node;
    }

    // Search left if the target ID is smaller
    if (reservationID < node->data.getReservationID()) {
        return findNode(node->left, reservationID);
    }

    // Otherwise, search the right subtree
    return findNode(node->right, reservationID);
}

// Returns a pointer to the reservation if it exists
Reservation* ReservationList::findReservation(
    const std::string& reservationID) const {

    ReservationNode* node = findNode(root, reservationID);

    // Return nullptr if the reservation was not found
    if (node == nullptr) {
        return nullptr;
    }

    // Return the reservation stored in the matching node
    return &(node->data);
}

// Finds the smallest ID in a subtree
ReservationNode* ReservationList::findMin(ReservationNode* node) const {
    // The smallest ID is the leftmost node
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }

    return node;
}

// Removes a reservation while maintaining BST ordering
ReservationNode* ReservationList::removeNode(
    ReservationNode* node, const std::string& reservationID) {

    // Base case: the reservation was not found
    if (node == nullptr) {
        return nullptr;
    }

    // Search the left subtree for a smaller ID
    if (reservationID < node->data.getReservationID()) {
        node->left = removeNode(node->left, reservationID);
    }
    // Search the right subtree for a larger ID
    else if (reservationID > node->data.getReservationID()) {
        node->right = removeNode(node->right, reservationID);
    }
    // The matching reservation has been found
    else {
        // Case 1: node has no left child
        if (node->left == nullptr) {
            ReservationNode* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: node has no right child
        if (node->right == nullptr) {
            ReservationNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: node has two children
        // Find the smallest ID in the right subtree
        ReservationNode* temp = findMin(node->right);

        // Copy that reservation into the node being removed
        node->data = temp->data;

        // Remove the duplicate node from the right subtree
        node->right = removeNode(
            node->right, temp->data.getReservationID());
    }

    // Return the updated subtree
    return node;
}

// Removes a reservation by ID and saves its data
bool ReservationList::removeReservation(
    const std::string& reservationID,
    Reservation& removedReservation) {

    // Find the reservation before removing it
    ReservationNode* node = findNode(root, reservationID);

    // Return false if the ID does not exist
    if (node == nullptr) {
        return false;
    }

    // Save the reservation for cancellation history or undo
    removedReservation = node->data;

    // Update the tree after removing the reservation
    root = removeNode(root, reservationID);

    return true;
}

// Displays reservations using in-order traversal
void ReservationList::displayInOrder(ReservationNode* node) const {
    if (node == nullptr) {
        return;
    }

    // Visit left subtree, current node, then right subtree
    displayInOrder(node->left);
    node->data.display();
    displayInOrder(node->right);
}

// Displays every reservation in ascending ID order
void ReservationList::displayAllReservations() const {
    // Handle an empty tree
    if (root == nullptr) {
        std::cout << "No reservations found.\n";
        return;
    }

    // In-order traversal displays sorted reservation IDs
    displayInOrder(root);
}

// Returns true if the tree contains no reservations
bool ReservationList::isEmpty() const {
    return root == nullptr;
}
