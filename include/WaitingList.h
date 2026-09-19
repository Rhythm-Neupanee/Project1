#ifndef WaitingList_h
#define WaitingList_h

#include <string>
#include <utility>

// for student information waiting queue
struct  WaitingNode {
    std::string studentID;
    std::string studentName;
    WaitingNode* next;

    WaitingNode(std::string id, std::string name) : studentID(std::move(id)), studentName(std::move(name)), next(nullptr) {}
};

// FIFO queue for managing the waiting list
class WaitingList {
private:
    WaitingNode* front;     // Pointer to the front of the queue
    WaitingNode* rear;      // Pointer to the rear of the queue
public:
    WaitingList();
    ~WaitingList();
    
    void enqueue(const std::string& id, const std::string& name); // Add a student to the waiting list
    bool dequeue(std::string& id, std::string& name);   // Remove a student from the waiting list
    bool isEmpty() const;    // Check if the waiting list is empty
    void display() const;    // Display the waiting list
};
#endif
