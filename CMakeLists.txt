cmake_minimum_required(VERSION 3.20.0)

set(PROJECT_NAME "KleinEngine")

project(${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/ThirdParty/glfw/include)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

link_directories(${CMAKE_BINARY_DIR}/ThirdParty/glfw/src)
add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/glfw)


if (WIN32)
    link_libraries(glfw3 opengl32)
else()
    link_libraries(glfw GL)
endif()

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_SOURCE_DIR}/src/Shader.hpp
    ${CMAKE_SOURCE_DIR}/src/ImageLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/ImageLoader.hpp
    ${CMAKE_SOURCE_DIR}/src/Window.cpp
    ${CMAKE_SOURCE_DIR}/src/Window.hpp
    ${CMAKE_SOURCE_DIR}/src/ErrorHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/ErrorHandler.hpp
    ${CMAKE_SOURCE_DIR}/src/__macros__only_hpp.hpp
    ${CMAKE_SOURCE_DIR}/src/GL_TYPES.hpp
    ${CMAKE_SOURCE_DIR}/assets/shaders/shader.vert
    ${CMAKE_SOURCE_DIR}/assets/shaders/shader.frag
    ${CMAKE_SOURCE_DIR}/src/ThirdParty/glad.c
    ${CMAKE_SOURCE_DIR}/src/ThirdParty/stb_image.h
)

# set_target_properties(
#     ${PROJECT_NAME} PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
#     VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
# )

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})