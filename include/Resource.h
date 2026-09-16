#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
using namespace std;

class Resource
{
private:
    string resourceID;
    string resourceName;
    string resourceType;
    bool available;

public:
    Resource();
    Resource(string id, string name, string type, bool status);

string getResourceID() const;
string getResourceName() const;
string getResourceType() const;
bool isAvailable() const;

void setResourceID(string id);
void setResourceName(string name);
void setResourceType(string type);
void setAvailability(bool status);

void display() const;
};

#endif
