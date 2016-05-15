project(dates-test)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
                                       "${CMAKE_CURRENT_SOURCE_DIR}/sut/include")

add_subdirectory("sut")
add_subdirectory("testcase")

