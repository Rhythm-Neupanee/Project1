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

Complexity Analysis

Reservation insertion complexity
Data structure: Singly linked list
Time complexity: O(1)
Description: We insert a new reservation node directly at the head of the list which involves constant- time pointer adjustment. This does not depend on the number of active reservations currently stored.

Reservation removal complexity
Data structure: Singly linked list
Time complexity: O(N)
Description: For the removal of the system must search for the matching Reservation ID. In the worst case scenario which is when the target is at the end of the list or doesn’t exit, this requires a full linear access for all N active reservation nodes before removing or unlinking the target.

Waiting-list processing complexity
Data structure: First-In, First-out(FIFO) Queue
Time complexity: O(1) for both enqueue and dequeue operations.
Description: This maintains a custom pointer to both the front and rear nodes by the help of which we could add students to the rear when resource is full (enqueue) and remove students from the front when the resource frees up (dequeue). Both are isolated pointer updates that execute in constant time.

Undo cancellation complexity
Data structure: Last-In, First-Out (LIFO) Stack 
Time complexity: O(1) for both push and pop operations.
Description: All stack operations occur at a single top pointer. Pushing or popping reservations requires pointer reassignments that operate in constant time.
