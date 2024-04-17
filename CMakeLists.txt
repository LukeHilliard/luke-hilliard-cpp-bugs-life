cmake_minimum_required(VERSION 3.14)
project(C__CA2)

set(CMAKE_CXX_STANDARD 17)

# Add all source files to the executable
add_executable(C__CA2
        game/main.cpp
        bugs/Bug.h
        bugs/Crawler.h
        bugs/Crawler.cpp
        bugs/Bug.cpp
        bugs/Hopper.h
        bugs/Hopper.cpp
        game/Board.cpp
        game/Board.h
)

# Include SFML
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(C__CA2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
