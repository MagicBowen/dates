file(GLOB_RECURSE files *.cpp)

add_library(sut STATIC ${files})

