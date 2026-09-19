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
