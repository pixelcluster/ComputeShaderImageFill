# CMakeList.txt : CMake project for ComputeShaderImageFill, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Add source to this project's executable.
add_executable (ComputeShaderImageFill "ComputeShaderImageFill.cpp" "glad/src/glad.c")

# TODO: Add tests and install targets if needed.
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})
target_include_directories(ComputeShaderImageFill PUBLIC glad/include)
target_link_libraries(ComputeShaderImageFill glfw ${OPENGL_LIBRARIES})


add_custom_command(TARGET ComputeShaderImageFill POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_CURRENT_SOURCE_DIR}/fill-compute.glsl
${CMAKE_CURRENT_SOURCE_DIR}/null-vertex.glsl
${CMAKE_CURRENT_SOURCE_DIR}/null-fragment.glsl 
$<TARGET_FILE_DIR:ComputeShaderImageFill>)