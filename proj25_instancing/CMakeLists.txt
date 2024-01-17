cmake_minimum_required(VERSION 3.10)

project(proj25_instancing)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)


set(SOURCES src/main.cpp 
        src/instancing_quad.cpp shaders/instancing_quad.fs shaders/instancing_quad.vs
        src/asteroids.cpp shaders/asteroids.fs shaders/asteroids.vs
        src/asteroids_instancing.cpp shaders/asteroids_instancing.fs shaders/asteroids_instancing.vs 
                            shaders/planet.fs shaders/planet.vs)
add_executable(${PROJECT_NAME} ${SOURCES})

file(GLOB MY_VERT "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vs")
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


file(GLOB MY_FRAG "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.fs")
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


file(GLOB MY_FRAG "${PROJECT_DLLS_DIRECTORY}/*.dll")
foreach(CurrentHeaderFile IN LISTS MY_FRAG)
    add_custom_command(
        TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Copying files"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different   
            "${CurrentHeaderFile}"
            "$(OutDir)"
        COMMENT "Copying dll files to build directory"
	)
endforeach()
 
 
target_link_libraries(${PROJECT_NAME} ${LIBS} glfw)