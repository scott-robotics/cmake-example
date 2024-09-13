cmake_minimum_required(VERSION 3.20)
project(CMakeExampleApp VERSION 1.0 LANGUAGES CXX)

# Import external required libraries
find_package(CMakeExampleLibrary REQUIRED)

# Add the executable
add_executable(MyApp main.cpp)

# Link the executable with the library
# This will also ensure that the correct header locations are included provided
# that target_include_directories was used in the originating package
target_link_libraries(MyApp CMakeExampleLibrary::mylib)
