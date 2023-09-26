project(main)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror")
set(SRC_LIST main.cpp question.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})