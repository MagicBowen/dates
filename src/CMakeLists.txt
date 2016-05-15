file(GLOB_RECURSE files *.cpp)

add_library(dates STATIC ${files})

install(TARGETS dates ARCHIVE DESTINATION lib)