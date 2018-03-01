cmake_minimum_required (VERSION 3.0)

# DEFINE THIS PROJECT.
set(EXECUTABLE_NAME "Game")
project (${EXECUTABLE_NAME})
    
# GET ALL THE HEADER FILES THAT ARE PART OF THE BOOST LIBRARY.
file (GLOB BOOST_HEADER_FILES
    "boost_1_66_0/boost/**/*.hpp")
    
# SET THE FOLDER CONTAINING THE BOOST INCLUDE FILES.
# The root folder is used rather than the inner "boost" folder
# so includes can be specified as "boost/boost_file.hpp" rather
# than just "boost_file.hpp".
include_directories("boost_1_66_0")

# SET THE CODE FOLDER AS AN INCLUDE DIRECTORY.
# This allows us to specify includes in the code as SubFolder/Header.h
# rather than needing the full path to the files.
include_directories("Code")

# INCLUDE DIRECTORIES THAT ARE PART OF THIS PROJECT.
add_subdirectory(Box2D)

# GET ALL THE HEADER FILES TAHT ARE SPECIFIC TO THIS PROJECT.
file (GLOB PROJECT_SPECIFIC_HEADER_FILES
    "Code/**/*.h")

# GET ALL THE SOURCE FILES THAT ARE SPECIFIC TO THIS PROJECT.
file (GLOB PROJECT_SPECIFIC_SOURCE_FILES
    "Code/**/*.cpp")

# BUILD THE EXECUTABLE.
add_executable(
    ${EXECUTABLE_NAME}
    "Code/main.cpp"
    ${BOOST_HEADER_FILES}
    ${PROJECT_SPECIFIC_HEADER_FILES}
    ${PROJECT_SPECIFIC_SOURCE_FILES})

# LINK TO THE BOX 2D PHYSICS LIBRARY.
target_link_libraries (Box2D)

# SET VARIABLES REQUIRED BY THE SFML CMAKE MODULE.
# SFML uses a CMake module for configuration rather than a
# CMakeLists file so it has to be configured differently than Box2D. 
# This module is supplied by the library itself.
#
# These variables are needed by the SFML CMake module so CMake can find the files 
# required for building the SFML library.
#
# The static version of the SFML library will be used so DLL files do not need to
# be supplied with the executable in order for it to run.
set(SFML_STATIC_LIBRARIES TRUE)

# CMAKE_SOURCE_DIR is the root directory where
# the top-level CMakeLists file is defined. It is not the directory where
# the CMake application runs.
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/lib")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/cmake/Modules")
set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SFML-2.4.2/include")

# ATTEMPT TO LINK SFML.
# Find the packages of the SFML library that will be used by this project.
# Possible options are: audio, graphics, network, system, and window.
find_package(SFML 2 REQUIRED audio graphics network system window)

# Check if the required SFML packages were found.
if (SFML_FOUND)
    # Set the include files that will be used from the SFML library.
    include_directories(${SFML_INCLUDE_DIR})
    
    # Link SFML with this project.
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()