PROJECT(CMakeExampleProject)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_EXAMPLE_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(CMAKE_EXAMPLE_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(CMAKE_EXAMPLE_VERSION ${CMAKE_EXAMPLE_VERSION_MAJOR}.${CMAKE_EXAMPLE_VERSION_MINOR} CACHE STRING "version" FORCE)

set(BUILD_TYPE Release)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")

# CONFIGURABLE HEADERS
######################
# This allows us to pass CMake variables (like version) to a header file
configure_file (
  "${PROJECT_SOURCE_DIR}/ExampleConfig.h.in"
  "${PROJECT_BINARY_DIR}/ExampleConfig.h"
)
# Include the build directory so the header can be found
include_directories("${PROJECT_BINARY_DIR}")

# IMPORT EXTERNAL LIBRARIES
###########################

# Import external required libraries
find_package(Eigen3 REQUIRED)

include_directories(
  ${EIGEN3_INCLUDE_DIR}
)

# BUILD LOCAL LIBRARIES
#######################

# Set MyLib sources files
set(mylib_SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/mylib.cpp
)

# Compile library.
add_library(mylib ${mylib_SOURCE_FILES})

# Project-wide includes
include_directories(
  include
)

# EXECUTABLES
#############

# Add main executable
add_executable(MyLibTest src/main.cpp)
target_link_libraries(MyLibTest mylib)


# INSTALLATION
##############
# This is an example for installing a library that
# can be included in other projects using find_package().
# In this example, we want to export MyLib


# Set install locations (Relative to CMAKE_INSTALL_PREFIX)
set(CMAKE_RUNTIME_INSTALL_DIR "bin")
set(CMAKE_LIBRARY_INSTALL_DIR "lib/${PROJECT_NAME}")
set(CMAKE_ARCHIVE_INSTALL_DIR "lib/${PROJECT_NAME}")
set(CMAKE_INCLUDE_INSTALL_DIR "include/${PROJECT_NAME}")

# Add the install targets
install(TARGETS mylib MyLibTest EXPORT MyLibTargets
  LIBRARY DESTINATION ${CMAKE_LIBRARY_INSTALL_DIR}
  ARCHIVE DESTINATION ${CMAKE_LIBRARY_INSTALL_DIR}
  RUNTIME DESTINATION ${CMAKE_RUNTIME_INSTALL_DIR}
)

# Install MyLib headers
install(
  DIRECTORY include/mylib
  DESTINATION ${CMAKE_INCLUDE_INSTALL_DIR}
)

# Install package config headers (not needed on our case
# if we just want MyLib)
install(
  FILES "${PROJECT_BINARY_DIR}/ExampleConfig.h"
  DESTINATION ${CMAKE_INCLUDE_INSTALL_DIR}
)

# When find_package is called, it will look for the XXXConfig.cmake
# file. This file populates the variables XXX_INCLUDE_DIRS and XXX_LIBRARIES
# so CMake knows where to find all these files. We use a configurable input
# file to attach the install path prefix. The output file is place in the
# build directory
configure_file(
  cmake/MyLibConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/MyLibConfig.cmake"
  @ONLY
)

# Finally, install the config file to  location determined by
# CMAKE_INSTALL_PREFIX. When running CMake on a project wanting
# to import this library, make sure this install prefix path
# exists in the CMAKE_PREFIX_PATH variable. CMake will search
# cmake/XXX and lib/cmake/XXX for the config file.
install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/cmake/MyLibConfig.cmake"
  DESTINATION "lib/cmake/MyLib"
)