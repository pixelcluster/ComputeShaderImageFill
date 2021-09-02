# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.20)

project("ComputeShaderImageFill")

# Include sub-projects.
add_subdirectory(glfw)
add_subdirectory(ComputeShaderImageFill)
