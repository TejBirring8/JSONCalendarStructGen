cmake_minimum_required(VERSION 3.15)
project(NumberOfDaysInMonth)

set(CMAKE_CXX_STANDARD 14)

add_executable(NumberOfDaysInMonth main.cpp Utils/UI.cpp DayOfWeek.cpp)