cmake_minimum_required(VERSION 3.10)

project(OpenGLProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)



find_package(OpenGL REQUIRED)
set(LIBS ${LIBS} opengl32)
# Add GLFW source directory
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw-3.3.9")  # Replace 'path/to/glfw' with the actual path to GLFW source
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(assimp_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake/assimp-5.3")
find_package(assimp REQUIRED)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

# Add Glad source files (if necessary)
add_library(glad src/glad.c)
set(LIBS ${LIBS} glad)
add_library(STB_IMAGE "src/stb_image.cpp")
set(LIBS ${LIBS} STB_IMAGE)
# set(LIBS ${LIBS} assimp-vc143-mt)



set(PROJECT_DLLS_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(proj6_shader)
add_subdirectory(proj7_texture)
add_subdirectory(proj8_trans)
add_subdirectory(proj9_coords)
add_subdirectory(proj10_camera)
add_subdirectory(proj11_colors)
add_subdirectory(proj12_diffuse)
add_subdirectory(proj13_material)
add_subdirectory(proj14_lightmap)
add_subdirectory(proj15_lightcast)
add_subdirectory(proj16_lightmultiple)
add_subdirectory(proj17_models)