cmake_minimum_required(VERSION 4.3)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Project1
        include/CancellationHistory.h
        include/Reservation.h
        include/ReservationManager.h
        include/Resource.h
        include/WaitingList.h
        src/CancellationHistory.cpp
        src/main.cpp
        src/Reservation.cpp
        src/ReservationManager.cpp
        src/Resource.cpp
        src/WaitingList.cpp)
