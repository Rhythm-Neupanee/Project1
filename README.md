# Campus Resource Reservation System

## Project Overview
This application is a menu-driven C++ software system that manages campus resources (e.g., study rooms, laptops, calculators, lab equipment). It tracks active reservations using a custom Singly Linked List, handles resource waiting lists using custom FIFO Queues, and manages cancellation history and undo actions using a custom LIFO Stack.

---

## Folder Structure
```text
Project1/
│
├── include/                 # Header files (.h)
│   ├── Resource.h
│   ├── Reservation.h
│   ├── WaitingList.h
│   ├── CancellationHistory.h
│   └── ReservationManager.h
│
├── src/                     # Source files (.cpp)
│   ├── main.cpp
│   ├── Resource.cpp
│   ├── Reservation.cpp
│   ├── WaitingList.cpp
│   ├── CancellationHistory.cpp
│   └── ReservationManager.cpp
│
├── data/                    # Resource input files
│   ├── resources.txt
│   ├── Reservation.txt
│
├── complexity_analysis.txt   # Big-O notation complexity report
├── group_contribution.txt   # Group contribution breakdown table
└── README.md                # System overview and build instructions

Data Structure Used
- std::vector: Stores the central resource inventory loaded from external data files.
- Custom Singly linked List: Dynamically manages all active student reservations across the entire system.
- Custom FIFO Queue: Handles waitlisted students in First-In, First-Out order when an item is unavailable.
- Custom LIFO Stack: Tracks system-wide cancelled reservation to enable Last-In, First-Out undo Functionality.

Compilation & Execution Instructions
This project is configured and fully tested for the UNT CSE CELL machine environment using g++
1. Open your terminal and navigate to the project root directory:
    cd Project1
2. Compile all source files using g++ with C++11 support:
    g++ -std=c++11 src/*.cpp -Iinclude -o app
3. Run the compiled executable:
    ./app

Input File Format
The application imports resource and reservation data from data folder.
Example of files:
  - data/resources.txt
        R101|Study Room 101|Study Room|Available
        R102|Study Room 102|Study Room|Available
        R103|Study Room 103|Study Room|Unavailable
        R104|Study Room 104|Study Room|Available
        R105|Laptop 01|Laptop|Available
        R106|Laptop 02|Laptop|Unavailable

  -data/reservations.txt
        301|1001|Alice Smith|R101|09/15/2026
        302|1002|Bob Johnson|R103|09/16/2026
        303|1003|Sara Lee|R105|09/17/2026
        304|1004|David Kim|R107|09/18/2026
        305|1005|Emma Davis|R109|09/19/2026
        306|1006|Noah Wilson|R111|09/20/2026
        307|1007|Mia Brown|R113|09/21/2026
        308|1008|Liam Garcia|R115|09/22/2026

Features Supported in Milestone 1
1. Resource Inventory: Reads the item file and shows real-time availability.
2. Active Booking: Reserves free items and saves them directly to the main linked list.
3. Waitlists: Automatically puts students in a FIFO queue when a resource is full.
4. Cancellations: Removes reservations, saves them to the cancellation history, and hands the freed resource to the next student in line.
5. Undo System: Pops the latest cancellation off the stack to instantly restore a booking.
