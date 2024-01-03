cmake_minimum_required(VERSION 3.10)

project(OpenGLProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


find_package(OpenGL REQUIRED)
# Add GLFW source directory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.9")  # Replace 'path/to/glfw' with the actual path to GLFW source

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# Add Glad source files (if necessary)
add_library(glad src/glad.c)


add_subdirectory(proj6_shader)
# Add your own source files



# If using additional libraries (e.g., OpenGL), add them here
# target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})
