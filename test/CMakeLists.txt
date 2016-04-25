include_directories("${GTEST_ROOT}/include"
                                     "${CMAKE_CURRENT_SOURCE_DIR}")

link_directories("${GTEST_ROOT}/lib")

file(GLOB_RECURSE files *.cpp)

add_executable(dates_test ${files})

target_link_libraries(dates_test dates gtest pthread)

