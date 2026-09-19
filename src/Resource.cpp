#include "../include/Resource.h"
#include <iostream>
#include <utility>

Resource::Resource() : isAvailable(true) {}
Resource::Resource(std::string ID, std::string Name, std::string Type, bool Availability)
    : id(std::move(ID)), name(std::move(Name)), type(std::move(Type)), isAvailable(Availability) {}

std::string Resource::getId() const { return id; }
std::string Resource::getName() const { return name; }
std::string Resource::getType() const { return type; }
bool Resource::getAvailability() const { return isAvailable; }
WaitingList& Resource::getWaitingQueue() { return waitingQueue; }

void Resource::setAvailability(bool availability) { isAvailable = availability; }

void Resource::display() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | Type: " << type
              << " | Status: " << (isAvailable ? "Available" : "Reserved") << "\n";
}

void Resource::displayWaitingQueue() const {
    std::cout << "Waiting Queue for [" << id << " - " << name << "]:\n";
    waitingQueue.display();
}
