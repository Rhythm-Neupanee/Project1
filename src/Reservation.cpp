```cpp
#include "../include/Reservation.h"
#include <iostream>
#include <utility>

// Constructor: initializes reservation information
Reservation::Reservation(std::string reservationID, std::string studentID, std::string studentName, std::string resourceID, std::string date) : reservationID(std::move(reservationID)), studentID(std::move(studentID)), studentName(std::move(studentName)), resourceID(std::move(resourceID)), date(std::move(date)) {}

// Getter functions return reservation information
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

// Displays one reservation's information
void Reservation::display() const {
    std::cout << "Res ID: " << reservationID << " | Student: " << studentName << " (ID: " << studentID << ")" << " | Resource ID: " << resourceID << " | Date: " << date << "\n";
}

// Constructor: creates an empty reservation tree
ReservationList::ReservationList() : root(nullptr) {}

// Destructor: deletes all nodes to prevent memory leaks
ReservationList::~ReservationList() {
    destroyTree(root);
}

// Recursively deletes the left subtree, right subtree,
// and then the current node
void ReservationList::destroyTree(ReservationNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

// Inserts a reservation according to its reservation ID
ReservationNode* ReservationList::insertNode(ReservationNode* node, const Reservation& res) {

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

// Adds a reservation to the binary search tree
void ReservationList::addReservation(const Reservation& res) {
    root = insertNode(root, res);
}

// Searches the tree for a reservation ID
ReservationNode* ReservationList::findNode(ReservationNode* node, const std::string& reservationID) const {

    // Stop if the node is empty or the ID matches
    if (node == nullptr || node->data.getReservationID() == reservationID) {
        return node;
    }

    // Search left when the target ID is smaller
    if (reservationID < node->data.getReservationID()) {
        return findNode(node->left, reservationID);
    }

    // Otherwise, search right
    return findNode(node->right, reservationID);
}

// Returns a pointer to the reservation if found
Reservation* ReservationList::findReservation(const std::string& reservationID) const {

    ReservationNode* node = findNode(root, reservationID);

    // Return nullptr if the reservation does not exist
    if (node == nullptr) {
        return nullptr;
    }

    return &(node->data);
}

// Finds the smallest reservation ID in a subtree
ReservationNode* ReservationList::findMin(ReservationNode* node) const {
    // The smallest ID is at the leftmost node
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }

    return node;
}

// Removes a reservation while maintaining BST ordering
ReservationNode* ReservationList::removeNode(ReservationNode* node, const std::string& reservationID) {

    // Base case: reservation was not found
    if (node == nullptr) {
        return nullptr;
    }

    // Search the left subtree
    if (reservationID < node->data.getReservationID()) {
        node->left = removeNode(node->left, reservationID);
    }
    // Search the right subtree
    else if (reservationID > node->data.getReservationID()) {
        node->right = removeNode(node->right, reservationID);
    }
    // Reservation was found
    else {
        // Case 1: no left child
        if (node->left == nullptr) {
            ReservationNode* temp = node->right;
            delete node;
            return temp;
        }

        // Case 2: no right child
        if (node->right == nullptr) {
            ReservationNode* temp = node->left;
            delete node;
            return temp;
        }

        // Case 3: two children
        // Find the smallest ID in the right subtree
        ReservationNode* temp = findMin(node->right);

        // Copy its reservation data into the current node
        node->data = temp->data;

        // Remove the duplicate node
        node->right = removeNode(
            node->right, temp->data.getReservationID());
    }

    return node;
}

// Removes a reservation and saves its data
bool ReservationList::removeReservation(const std::string& reservationID, Reservation& removedReservation) {

    // Find the reservation before deleting it
    ReservationNode* node = findNode(root, reservationID);

    if (node == nullptr) {
        return false;
    }

    // Save the reservation for cancellation history or undo
    removedReservation = node->data;

    // Update the tree after removal
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

// Displays all reservations in BST order
void ReservationList::displayAllReservations() const {
    if (root == nullptr) {
        std::cout << "No reservations found.\n";
        return;
    }

    displayInOrder(root);
}

// Collects reservations from the tree into a vector
void ReservationList::collectReservations(
    ReservationNode* node,
    std::vector<Reservation>& reservations) const {

    if (node == nullptr) {
        return;
    }

    // Copy the current reservation into the vector
    reservations.push_back(node->data);

    // Visit both subtrees
    collectReservations(node->left, reservations);
    collectReservations(node->right, reservations);
}

// Combines two sorted sections of the vector
void ReservationList::merge(std::vector<Reservation>& reservations, int left, int mid, int right) const {

    std::vector<Reservation> temp;

    int i = left;
    int j = mid + 1;

    // Compare IDs and copy the smaller one first
    while (i <= mid && j <= right) {
        if (reservations[i].getReservationID() <= reservations[j].getReservationID()) {

            temp.push_back(reservations[i]);
            i++;
        }
        else {
            temp.push_back(reservations[j]);
            j++;
        }
    }

    // Copy any remaining items from the left section
    while (i <= mid) {
        temp.push_back(reservations[i]);
        i++;
    }

    // Copy any remaining items from the right section
    while (j <= right) {
        temp.push_back(reservations[j]);
        j++;
    }

    // Copy the merged section back into the original vector
    for (int k = 0; k < static_cast<int>(temp.size()); k++) {
        reservations[left + k] = temp[k];
    }
}

// Recursively sorts the vector using Merge sort
void ReservationList::mergeSort(
    std::vector<Reservation>& reservations,
    int left, int right) const {

    // Base case: one item is already sorted
    if (left >= right) {
        return;
    }

    // Find the middle of the section
    int mid = left + (right - left) / 2;

    // Sort the left half
    mergeSort(reservations, left, mid);

    // Sort the right half
    mergeSort(reservations, mid + 1, right);

    // Merge the sorted halves
    merge(reservations, left, mid, right);
}

// Collects, sorts, and displays all reservations
void ReservationList::displayReservationsMergeSort() const {
    std::vector<Reservation> reservations;

    // Collect every reservation from the BST
    collectReservations(root, reservations);

    if (reservations.empty()) {
        std::cout << "No reservations found.\n";
        return;
    }

    // Sort the copied reservations by ID
    mergeSort(reservations, 0,
              static_cast<int>(reservations.size()) - 1);

    // Display the sorted results
    std::cout << "Reservations sorted by ID using Merge sort:\n";

    for (const Reservation& res : reservations) {
        res.display();
    }
}

// Returns true when the tree is empty
bool ReservationList::isEmpty() const {
    return root == nullptr;
}
