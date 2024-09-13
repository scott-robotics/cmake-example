cmake_minimum_required(VERSION 3.20)
project(CMakeExampleLibrary VERSION 1.0 LANGUAGES CXX)

# ---------------------------------------------------------------------------------------
# BUILD
# ---------------------------------------------------------------------------------------

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ---------------------------------------------------------------------------------------
# Configurable headers
# ---------------------------------------------------------------------------------------
# This allows us to pass CMake variables (like version) to a header file
configure_file(
  "${PROJECT_SOURCE_DIR}/ExampleConfig.hpp.in"
  "${PROJECT_BINARY_DIR}/include/mylib/ExampleConfig.hpp"
)

# ---------------------------------------------------------------------------------------
# Import external libraries
# ---------------------------------------------------------------------------------------
# Some common and easily-attainable libraries
find_package(Eigen3 REQUIRED)
find_package(Boost CONFIG)

# ---------------------------------------------------------------------------------------
# Build local libraries
# ---------------------------------------------------------------------------------------
add_library(mylib STATIC src/mylib.cpp)

# Instructs cmake to package the includes with the library target. PUBLIC headers are 
# requrired in downstream packages, while PRIVATE headers are required in the build
# only, ie. they only in exist in private headers and .cpp files
target_include_directories(mylib 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

# Link our library to dependent libraries.
# Not needed here because Boost::shared_ptr and Eigen are header-only
# target_link_libraries(mylib boost)

# ---------------------------------------------------------------------------------------
# INSTALL
# ---------------------------------------------------------------------------------------

set(PROJECT_CONFIG_IN "${CMAKE_CURRENT_LIST_DIR}/cmake/CMakeExampleLibraryConfig.cmake.in")
set(PROJECT_CONFIG_OUT "${CMAKE_CURRENT_BINARY_DIR}/CMakeExampleLibraryConfig.cmake")
set(EXPORT_DESTINATION_DIR "lib/cmake/${PROJECT_NAME}")
set(EXPORT_CONFIGURATION_FILE "${PROJECT_NAME}.cmake")

# ---------------------------------------------------------------------------------------
# Libraries and Include files
# ---------------------------------------------------------------------------------------
install(TARGETS mylib
    EXPORT CMakeExampleLibrary
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(
  DIRECTORY
    include/
    ${PROJECT_BINARY_DIR}/include/
  DESTINATION
    include
)

# ---------------------------------------------------------------------------------------
# Install CMake config files
# ---------------------------------------------------------------------------------------
# Export targets for use by find_package
install(EXPORT CMakeExampleLibrary
  DESTINATION ${EXPORT_DESTINATION_DIR}
  FILE ${EXPORT_CONFIGURATION_FILE}
  NAMESPACE CMakeExampleLibrary::
)

# Configure the Config.cmake file, populating it with anything specific from this build
configure_file(${PROJECT_CONFIG_IN} ${PROJECT_CONFIG_OUT} @ONLY)

# Install package config file
install(
  FILES ${PROJECT_CONFIG_OUT}
  DESTINATION ${EXPORT_DESTINATION_DIR}
)
