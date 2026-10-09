
#include "../include/Resource.h"
#include <iostream>
#include <utility>
#include <vector>

Resource::Resource() : isAvailable(true) {} // Default constructor

Resource::Resource(std::string ID, std::string Name, std::string Type, bool Availability) : id(std::move(ID)), name(std::move(Name)), type(std::move(Type)), isAvailable(Availability) {} // Constructor

std::string Resource::getId() const  {// Getters
    return id;
}

std::string Resource::getName() const {
    return name;
}

std::string Resource::getType() const {
    return type;
}

bool Resource::getAvailability() const {
    return isAvailable;
}

WaitingList& Resource::getWaitingQueue() { // Return the resource's waiting queue
    return waitingQueue;
}

void Resource::setAvailability(bool availability) { // Set availability
    isAvailable = availability;
}

void Resource::display() const { // Display resource information
    std::cout << "ID: " << id << " | Name: " << name << " | Type: " << type << " | Status: " << (isAvailable ? "Available" : "Reserved")<< "\n";
}

void Resource::displayWaitingQueue() const { // Display waiting queue
    std::cout << "Waiting Queue for [" << id << " - " << name << "]:\n";

    waitingQueue.display();
}

void Resource::mergeSortResources(std::vector<Resource*>& resources) { // Sorts resources by ID in ascending order
    if (resources.size() > 1) {
        mergeSortHelper(resources, 0, static_cast<int>(resources.size()) - 1 );
    }
}

void Resource::mergeSortHelper(std::vector<Resource*>& resources, int left, int right) { // Recursively divides the vector into smaller sections
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortHelper(resources, left, mid);
    mergeSortHelper(resources, mid + 1, right);

    merge(resources, left, mid, right);
}

void Resource::merge(std::vector<Resource*>& resources, int left, int mid, int right) { // Combines two sorted sections
    std::vector<Resource*> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right) { // Compare IDs and add the smaller one first
        if (resources[i]->getId() <= resources[j]->getId()) {
            temp.push_back(resources[i]);
            i++;
        } else {
            temp.push_back(resources[j]);
            j++;
        }
    }

    while (i <= mid) { // Add remaining resources from the left section
        temp.push_back(resources[i]);
        i++;
    }

    while (j <= right) { // Add remaining resources from the right section
        temp.push_back(resources[j]);
        j++;
    }

    for (int k = 0; k < static_cast<int>(temp.size()); k++) { // Copy the sorted section back into the vector
        resources[left + k] = temp[k];
    }
}

// Searches for a resource by ID.
// The vector must be sorted first.
Resource* Resource::binarySearchResource(const std::vector<Resource*>& resources, const std::string& targetID
) {
    int left = 0;
    int right = static_cast<int>(resources.size()) - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        std::string currentID = resources[mid]->getId();

        if (currentID == targetID) { // Resource found
            return resources[mid];
        }

        if (currentID < targetID) { // Search the right half
            left = mid + 1;
        }

        else { // Search the left half
            right = mid - 1;
        }
    }

    return nullptr; // Resource was not found
}
