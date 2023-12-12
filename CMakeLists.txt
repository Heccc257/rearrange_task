cmake_minimum_required(VERSION 3.10)

project(rearrge)

# set(CMAKE_CXX_STANDARD 20)

# Define the source files for the library
# file(GLOB LIB_SOURCE_FILES "src/*.cpp")

# Create the static library 'data_musk' from the source files
# add_library(data_musk STATIC ${LIB_SOURCE_FILES})

# Specify include directories for the library
# target_include_directories(data_musk PRIVATE src)

# Create the 'musk_algo' executable from musk_algo.cpp
add_executable(rearrge main.cpp)

# Link the 'data_musk' library to the 'musk_algo' executable
# target_link_libraries(musk_algo PRIVATE data_musk pthread)

# Set the output directories for the executable and library
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
# set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 添加 -g 选项以生成调试信息
# target_compile_options(data_musk PRIVATE -g)

# Set global optimization flags for the entire project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
