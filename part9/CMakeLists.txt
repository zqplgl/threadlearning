set(CMAKE_CXX_STANDARD 11)
add_executable(main main.cpp)
target_link_libraries(main pthread)
