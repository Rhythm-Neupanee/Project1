#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
using namespace std;

class Reservation
{
    private:
    int reservationID;
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate;

    public:
    Reservation();
    Reservation(int resID, int stuID, string name, string resourceID, string date);

    int getReservationID() const;
    int getStudentID() const;
    string getStudentName() const;
    string getResourceID() const;
    string getReservationDate() const;

    void setReservationID(int resID);
    void setStudentID(int stuID);
    void setStudentName(string name);
    void setResourceID(string resourceID);
    void setReservationDate(string date);

    void display() const;
};
#endif
