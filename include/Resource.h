```cpp
#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <vector>
#include "WaitingList.h"

// Represents one university resource
class Resource {
private:
    std::string id; // Unique resource ID
    std::string name; // Resource name or description
    std::string type; // Category, such as laptop or study room
    bool isAvailable; // True if the resource is available
    WaitingList waitingQueue; // Queue of students waiting for this resource

public:
    // Constructors
    Resource();
    Resource(std::string ID, std::string Name, std::string Type, bool Availability = true);

    // Getter functions
    [[nodiscard]] std::string getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] bool getAvailability() const;

    WaitingList& getWaitingQueue(); // Returns the waiting queue for this resource

    void setAvailability(bool availability); // Updates resource availability

    void display() const; // Displays resource information

    void displayWaitingQueue() const; // Displays the resource's waiting queue

    static void mergeSortResources(std::vector<Resource*>& resources); // Merge sort: sorts resource pointers by resource ID

    static Resource* binarySearchResource(const std::vector<Resource*>& resources,const std::string& targetID); // Binary search: finds a resource by ID in a sorted vector

private:

    static void mergeSortHelper(std::vector<Resource*>& resources, int left, int right); // Recursively divides and sorts the vector

    static void merge(std::vector<Resource*>& resources, int left, int mid, int right); // Merges two sorted sections

};

#endif
