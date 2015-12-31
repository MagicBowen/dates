CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(dates)

MACRO(source_group_by_dir source_files)
	SET(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
	FOREACH(sgbd_file ${${source_files}})
		STRING(REGEX REPLACE ${sgbd_cur_dir}/\(.*\) \\1 sgbd_fpath ${sgbd_file})
		STRING(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
		STRING(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
		IF(MSVC)
			string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
		ENDIF(MSVC)
		IF(sgbd_nogroup)
			SET(sgbd_group_name "\\")
		ENDIF(sgbd_nogroup)
		SOURCE_GROUP(${sgbd_group_name} FILES ${sgbd_file})
	ENDFOREACH(sgbd_file)
ENDMACRO(source_group_by_dir)

SET(CMAKE_CXX_FLAGS -std=c++11)

INCLUDE_DIRECTORIES( 
"${CMAKE_CURRENT_SOURCE_DIR}/include"
"${CMAKE_CURRENT_SOURCE_DIR}/test"
"${CMAKE_CURRENT_SOURCE_DIR}/3th/include"
)

IF(MSVC)
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
    ADD_DEFINITIONS(-DMSVC_VMG_ENABLED) #  /Z7)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /vmg")
ENDIF(MSVC)

FILE(GLOB_RECURSE all_files 
include/*.h
include/*.hpp
include/*.hxx
include/*.tcc
src/*.cpp
src/*.cc
src/*.cxx
test/*.h
test/*.hpp
test/*.hxx
test/*.tcc
test/*.cpp
)

source_group_by_dir(all_files)
message(STATUS "CMAKE_CURRENT_SOURCE_DIR are: ${CMAKE_CURRENT_SOURCE_DIR}")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/3th/lib")

add_executable(dates ${all_files})

target_link_libraries(dates gtest pthread) 

