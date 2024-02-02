cmake_minimum_required(VERSION 3.27)
project(steamid_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(steamid
        example.cpp
        SteamID.cpp
        SteamID.hpp)
