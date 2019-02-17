cmake_minimum_required(VERSION 3.6)
project(HashTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Node.cpp Node.h prime_number.h NodeErrs.h HashNode.cpp HashNode.h HConfig.h Hashtree.cpp Hashtree.h HashtreeFile.cpp HashtreeFile.h HashtreeState.h HashTreeQuery.cpp HashTreeQuery.h test.cpp test.h)
add_executable(HashTree ${SOURCE_FILES})