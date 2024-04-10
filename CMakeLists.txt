cmake_minimum_required(VERSION 3.27)
project(C___CA2)

set(CMAKE_CXX_STANDARD 17)

add_executable(C___CA2 game/main.cpp
        bugs/Bug.h
        bugs/Crawler.h
        bugs/Crawler.cpp
        bugs/Bug.cpp
        bugs/Hopper.h
        bugs/Hopper.cpp
        game/Board.cpp
        game/Board.h
        game/Board.h
        bugs/Direction.h)
