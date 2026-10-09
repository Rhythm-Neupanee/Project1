
#include "../include/Reservation.h"
#include <iostream>
#include <utility>
#include <vector>

Reservation::Reservation() = default; // Default constructor

// Constructor
Reservation::Reservation(std::string reservationID, std::string studentID, std::string studentName, std::string resourceID, std::string date)
    : reservationID(std::move(reservationID)), studentID(std::move(studentID)), studentName(std::move(studentName)), resourceID(std::move(resourceID)), date(std::move(date)) {}

// Getters
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

void Reservation::display() const { // Display reservation information
    std::cout << "Reservation ID: " << reservationID << " | Student ID: " << studentID << " | Student Name: " << studentName << " | Resource ID: " << resourceID << " | Date: " << date << "\n";
}

ReservationNode::ReservationNode(const Reservation& reservation): data(reservation), left(nullptr), right(nullptr) {} // Create a BST node

ReservationList::ReservationList() : root(nullptr) {} // Constructor for the reservation BST

ReservationList::~ReservationList() { // Destructor
    destroyTree(root);
}

void ReservationList::destroyTree(ReservationNode* node) { // Delete all nodes in the tree
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void ReservationList::addReservation(const Reservation& reservation) { // Insert a reservation into the BST
    root = insertNode(root, reservation);
}

ReservationNode* ReservationList::insertNode(ReservationNode* node, const Reservation& reservation) { // Find the correct location for a reservation
    if (node == nullptr) {
        return new ReservationNode(reservation);
    }

    if (reservation.getReservationID() < node->data.getReservationID()) {
        node->left = insertNode(node->left, reservation);
    } else if (reservation.getReservationID() > node->data.getReservationID()) {
        node->right = insertNode(node->right, reservation);
    }

    return node; // Duplicate reservation IDs are ignored
}

Reservation* ReservationList::findReservation(const std::string& reservationID) { // Search for a reservation by ID in the BST
    ReservationNode* current = root;

    while (current != nullptr) {
        if (reservationID == current->data.getReservationID()) {
            return &current->data;
        }

        if (reservationID < current->data.getReservationID()) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}

ReservationNode* ReservationList::findMinimum(ReservationNode* node) { // Find the node with the smallest reservation ID
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }

    return node;
}

ReservationNode* ReservationList::removeNode(ReservationNode* node, const std::string& reservationID){ // Remove a reservation from the BST
    if (node == nullptr) {
        return nullptr;
    }

    if (reservationID < node->data.getReservationID()) {
        node->left = removeNode(node->left, reservationID);
    } else if (reservationID > node->data.getReservationID()) {
        node->right = removeNode(node->right, reservationID);
    } else {

        if (node->left == nullptr) { // Node has no left child
            ReservationNode* temp = node->right;
            delete node;
            return temp;
        }

        // Node has no right child
        if (node->right == nullptr) {
            ReservationNode* temp = node->left;
            delete node;
            return temp;
        }

        ReservationNode* temp = findMinimum(node->right); // Node has two children
        node->data = temp->data;
        node->right = removeNode(node->right, temp->data.getReservationID());
    }

    return node;
}

bool ReservationList::removeReservation(const std::string& reservationID) { // Public function to remove a reservation
    if (findReservation(reservationID) == nullptr) {
        return false;
    }

    root = removeNode(root, reservationID);
    return true;
}

void ReservationList::displayReservations() const { // Display reservations in ascending ID order
    displayInOrder(root);
}

void ReservationList::displayInOrder(ReservationNode* node) const { // In-order traversal of the BST
    if (node == nullptr) {
        return;
    }

    displayInOrder(node->left);
    node->data.display();
    displayInOrder(node->right);
}

bool ReservationList::isEmpty() const { // Check whether the BST is empty
    return root == nullptr;
}

void ReservationList::collectReservations(ReservationNode* node, std::vector<Reservation>& reservations) const { // Collect reservations from the BST into a vector
    if (node == nullptr) {
        return;
    }

    reservations.push_back(node->data);

    collectReservations(node->left, reservations);
    collectReservations(node->right, reservations);
}

void ReservationList::mergeSort(std::vector<Reservation>& reservations, int left, int right) const { // Sort reservations by reservation ID
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(reservations, left, mid);
    mergeSort(reservations, mid + 1, right);

    merge(reservations, left, mid, right);
}

void ReservationList::merge(std::vector<Reservation>& reservations, int left, int mid, int right) const { // Merge two sorted sections
    std::vector<Reservation> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) { // Compare reservation IDs
        if (reservations[i].getReservationID() <= reservations[j].getReservationID()) {
            temp.push_back(reservations[i]);
            i++;
        } else {
            temp.push_back(reservations[j]);
            j++;
        }
    }

    while (i <= mid) { // Add remaining items from the left section
        temp.push_back(reservations[i]);
        i++;
    }

    while (j <= right) { // Add remaining items from the right section
        temp.push_back(reservations[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++) { // Copy sorted items back into the vector
        reservations[left + k] = temp[k];
    }
}

void ReservationList::displayReservationsMergeSort() const { // Display reservations after applying Merge Sort
    std::vector<Reservation> reservations;

    collectReservations(root, reservations);

    if (!reservations.empty()) {
        mergeSort(reservations, 0, static_cast<int>(reservations.size()) - 1);
    }

    for (const Reservation& reservation : reservations) {
        reservation.display();
    }
}
