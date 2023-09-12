cmake_minimum_required(VERSION 3.22)
project(MDBS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MDBS
        Library/Database.cpp
        Library/Database.h
        main.cpp
        Library/Record.cpp
        Library/Record.h
        Library/Transaction.cpp
        Library/Transaction.h)
