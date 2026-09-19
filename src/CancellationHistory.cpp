#include "../include/CancellationHistory.h"
#include <iostream>

CancellationHistory::CancellationHistory() : top(nullptr) {}    //Initializes top pointer to nullptr for an empty stack
//pop and delete all nodes to prevent memory leaks
CancellationHistory::~CancellationHistory() {
    while (!isEmpty()) {
        Reservation res;
        pop(res);
    }
}

//pushes a new reservation onto the top
void CancellationHistory::push(const Reservation& res) {
    auto* newNode = new StackNode(res);
    newNode->next = top;
    top = newNode;
}

//pops the top reservation
bool CancellationHistory::pop(Reservation& res) {
    if (top == nullptr) {
        return false;
    }
    StackNode* temp = top;
    res = top->reservation;
    top = top->next;
    delete temp;
    return true;
}

//check if stack is empty
bool CancellationHistory::isEmpty() const {
    return top == nullptr;
}

//display all stored canceled reservation
void CancellationHistory::display() const {
    if (top == nullptr) {
        std::cout << "Cancellation history is empty.\n";
        return;
    }
    StackNode* current = top;
    while (current != nullptr) {
        current->reservation.display();
        current = current->next;
    }
}
