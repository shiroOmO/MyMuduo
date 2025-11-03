cmake_minimum_required(VERSION 3.0)
project(mymuduo)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

add_compile_definitions(MUDEBUG)

include_directories(${PROJECT_SOURCE_DIR}/mymuduo)

aux_source_directory(${PROJECT_SOURCE_DIR}/mymuduo SRC_LIST)

add_executable(demo ${PROJECT_SOURCE_DIR}/example/demo.cpp ${SRC_LIST})

