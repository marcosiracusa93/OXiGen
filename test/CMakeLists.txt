#in TEST_BUILD:     cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_CXX_STANDARD=11 ../test


# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.5.1)

#add necessary flags to build passes out-of-source
add_definitions(-Wall -fno-rtti)

# Project's name
project(prova)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "LLVM include dirs: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Definitions: ${LLVM_DEFINITIONS}")

set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/../include" )
set( SOURCES_DIR "${PROJECT_SOURCE_DIR}/../src")
set( TEST_DIR "${PROJECT_SOURCE_DIR}/../test")

include_directories(${LLVM_INCLUDE_DIRS} ${INCLUDE_DIR})
add_definitions(${LLVM_DEFINITIONS})

file (GLOB SOURCES 
        ${INCLUDE_DIR}/*.h
        ${INCLUDE_DIR}/*/*.h
        ${SOURCES_DIR}/*.cpp
        )
        
file(GLOB BOOST_TEST ${TEST_DIR}/boostTests/boostTest.cpp)
file(GLOB STREAM_ANALYSIS_TEST ${TEST_DIR}/streamAnalyzerTests/streamsAnalyzerTest.cpp)

list( REMOVE_ITEM SOURCES ${SOURCES_DIR}/main.cpp)

# The executable to build
add_executable(boostTest ${SOURCES} ${BOOST_TEST})
add_executable(streamAnalysisTest ${SOURCES} ${STREAM_ANALYSIS_TEST})

# Set the path for binaries
set( EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/../test/bin" )

# Build a compilation database for YouCompleteMe
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core passes)

message(STATUS "LLVM Libraries: ${llvm_libs}")

# Link against LLVM libraries
target_link_libraries(boostTest ${llvm_libs})
target_link_libraries(streamAnalysisTest ${llvm_libs})