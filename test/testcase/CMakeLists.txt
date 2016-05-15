include_directories("${GTEST_ROOT}/include"
                                      "${CMAKE_CURRENT_SOURCE_DIR}")

link_directories("${GTEST_ROOT}/lib")

file(GLOB_RECURSE files *.h *.cpp)

add_executable(dates-test ${files})

target_link_libraries(dates-test dates sut gtest pthread ccinfra)

