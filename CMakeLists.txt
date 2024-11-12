cmake_minimum_required(VERSION 3.27)

project(CaDiBack VERSION 0.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(cadiback cadiback.cpp)
target_link_libraries(cadiback cadical)
set_target_properties(cadiback PROPERTIES PUBLIC_HEADER "cadiback.h")

install(TARGETS cadiback)
