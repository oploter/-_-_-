project(main)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")
set(SRC_LIST unique_ptr_test.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})