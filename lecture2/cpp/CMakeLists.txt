project(fooString)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Werror -fsanitize=address")
set(SRC_LIST fooString.cpp main.cpp doctest_main.o)

add_executable(${PROJECT_NAME} ${SRC_LIST})