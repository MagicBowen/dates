file(GLOB_RECURSE files *.h *.cpp)

add_library(sut STATIC ${files})

