# CMakeList.txt : CMake project for ComputeShaderImageFill, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (ComputeShaderImageFill "ComputeShaderImageFill.cpp" "ComputeShaderImageFill.h")

# TODO: Add tests and install targets if needed.
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(ComputeShaderImageFill ${OPENGL_LIBRARIES})
