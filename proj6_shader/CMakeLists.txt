cmake_minimum_required(VERSION 3.10)

project(proj6_shader)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(SOURCES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

file(GLOB MY_VERT "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert")
foreach(CurrentHeaderFile IN LISTS MY_VERT)
    add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying files"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different   
            "${CurrentHeaderFile}"
            "$(OutDir)"
        COMMENT "Copying Vertex shader to build directory"
	)
endforeach()


file(GLOB MY_FRAG "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag")
foreach(CurrentHeaderFile IN LISTS MY_FRAG)
    add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying files"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different   
            "${CurrentHeaderFile}"
            "$(OutDir)"
        COMMENT "Copying Vertex shader to build directory"
	)
endforeach()
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw  glad)