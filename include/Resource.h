#ifndef Resource_H
#define Resource_H

#include <string>
#include "WaitingList.h"

// represents the resource of the university
class Resource {
private:
    std::string id;     //unique id for the resource
    std::string name;   //name/description of the resource
    std::string type;   //type of the resource or category like laptop, room, etc
    bool isAvailable;   //availability status of the resource
    WaitingList waitingQueue; // waiting queue for the resource

    public:
    Resource(); // default constructor
    Resource(std::string ID, std::string Name, std::string Type, bool Availability = true);
     
    [[nodiscard]] std::string getId() const; // returns the unique id of the resource
    [[nodiscard]] std::string getName() const; // returns the name/description of the resource
    [[nodiscard]] std::string getType() const; // returns the type/category of the resource
    [[nodiscard]] bool getAvailability() const; // returns the availability status of the resource
    WaitingList& getWaitingQueue(); // returns the waiting queue of the resource

    // display the resource information
    void setAvailability(bool availability);

    void display();

    void display() const;  // sets the availability status of the resource
    void displayWaitingQueue() const; // displays the waiting queue of the resource
};

#endif
