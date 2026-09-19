#ifndef CancellationHistory_h
#define CancellationHistory_h

#include <utility>
#include "Reservation.h"

//single node in the linked-list
struct StackNode {
    Reservation reservation;  // hold canceled reservation data
    StackNode* next;          // pointer to the next node below in the stack
    //initializes the node with reservation data and sets the next pointer to nullptr
    StackNode(Reservation  res) : reservation(std::move(res)), next(nullptr) {}
};

//LIFO stack of canceled reservation
class CancellationHistory {
private:
    StackNode* top;
public:
    CancellationHistory(); //initializes an empty cancellation history stack
    ~CancellationHistory(); //deallocates all dynamically allocated stack node

    void push(const Reservation& res); //add reservation to top
    bool pop(Reservation& res);        //remove top reservation
    bool isEmpty() const;
    void display() const;
};
#endif