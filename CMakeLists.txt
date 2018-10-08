cmake_minimum_required(VERSION 3.8)
project(Graph)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp PriorityQueue.h PriorityQueue.cpp Graph.h Graph.cpp ShortestPath.h ShortestPath.cpp Prim.h Prim.cpp)
add_executable(Graph ${SOURCE_FILES})