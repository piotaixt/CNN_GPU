# Create new project
project (lib-tools)

# Recursively list all .h and .cu/.cpp files instead of manually put them here.
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false *.cpp *.cu)

# Add all the sources to the library
add_library(${PROJECT_NAME} ${SOURCES})

# We need the OpenCV headers to build the lib
include_directories( ${OpenCV_INCLUDE_DIRS} ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})

set_property(TARGET lib-tools PROPERTY CUDA_ARCHITECTURES 30)