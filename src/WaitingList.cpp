#include "../include/WaitingList.h"
#include <iostream>

WaitingList::WaitingList() : front(nullptr), rear(nullptr) {}
// Destructor to free memory
WaitingList::~WaitingList() {
    while (!isEmpty()) {
        std::string id, name;
        dequeue(id, name);
    }
}

// Add a student to the waiting list
void WaitingList::enqueue(const std::string& id, const std::string& name) {
    auto* newNode = new WaitingNode(id, name);
    if (rear == nullptr) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode; // Link the old rear to the new node
    rear = newNode; // Rear always points to the last node
}

// Remove a student from the waiting list
bool WaitingList::dequeue(std::string& id, std::string& name) {
    if (front == nullptr) {
        return false; // Queue is empty
    }
    WaitingNode* temp = front;
    id = temp->studentID;
    name = temp->studentName;
    front = front->next; // Move front to the next node
    if (front == nullptr) {
        rear = nullptr; // If the queue becomes empty, set rear to nullptr
    }
    delete temp; // Free memory of the dequeued node
    return true;
}

// Check if the waiting list is empty
bool WaitingList::isEmpty() const { return front == nullptr; }

// Display the waiting list
void WaitingList::display() const {
    if (front == nullptr) {
        std::cout << "Waiting list is empty." << std::endl;
        return;
    }
    WaitingNode* current = front;
    int position = 1;
    while (current != nullptr) {
        std::cout << "  " << position++ << ". " << current->studentName << " (ID: " << current->studentID << ")\n";
        current = current->next;
    }
}
