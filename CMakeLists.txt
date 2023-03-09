cmake_minimum_required(VERSION 3.19.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(json_parser)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
