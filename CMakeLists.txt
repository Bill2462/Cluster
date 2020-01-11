cmake_minimum_required(VERSION 3.5)

project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fconcepts")

include_directories(utils/include)

add_subdirectory(utils)
add_subdirectory(magic)
add_subdirectory(app)
