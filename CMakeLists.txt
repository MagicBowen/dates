cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "dates")

project(${PROJECT_NAME})

message(STATUS "project: ${PROJECT_NAME}")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include"
                                     "${CMAKE_CURRENT_SOURCE_DIR}/depend/ccinfra/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -g -std=c++11")

add_subdirectory("depend/ccinfra")
add_subdirectory("src")

install(DIRECTORY include/dates DESTINATION include)

if(GTEST_ROOT)
    add_subdirectory("test")
endif()

