cmake_minimum_required (VERSION 3.0)

# DEFINE THIS PROJECT.
set(EXECUTABLE_NAME "Game")
project (${EXECUTABLE_NAME})

# SET THE CODE FOLDER AS AN INCLUDE DIRECTORY.
# This allows us to specify includes in the code as SubFolder/Header.h
# rather than needing the full path to the files.
include_directories("Code")

# INCLUDE DIRECTORIES THAT ARE PART OF THIS BUILD.
add_subdirectory(Box2D)

# GET ALL THE HEADER FILES THAT WILL BE USED FOR THIS PROJECT.
file (GLOB HEADER_FILES
    "Code/**/*.h")

# GET ALL THE SOURCE FILES THAT WILL BE USED FOR THIS PROJECT.
file (GLOB SOURCE_FILES
    "Code/**/*.cpp")

# BUILD THE EXECUTABLE.
add_executable(
    ${EXECUTABLE_NAME}
    "Code/main.cpp"
    ${HEADER_FILES}
    ${SOURCE_FILES})

# LINK TO THE REQUIRED LIBRARIES.
target_link_libraries (Box2D)

# SFML uses a CMake module for configuration rather than a
# CMakeLists file. This is supplied by the library itself.
# The static version of the SFML library will be linked so DLL files do not need to
# be supplied with the executable in order for it to run.
set(SFML_STATIC_LIBRARIES TRUE)

# These variables are needed so CMake can find the various files required
# to build the SFML library.
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/lib")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML-2.4.2/cmake/Modules")
set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SFML-2.4.2/include")
find_package(SFML 2 REQUIRED network audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()