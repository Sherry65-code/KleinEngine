cmake_minimum_required(VERSION 3.20.0)

set(PROJECT_NAME "ProjectGraphics")

project(${PROJECT_NAME})

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
link_directories(${CMAKE_SOURCE_DIR}/dlls)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)

if (MSVC)
    link_libraries(glfw3dll opengl32)
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
    ${CMAKE_SOURCE_DIR}/assets/shaders/shader.v.glsl
    ${CMAKE_SOURCE_DIR}/assets/shaders/shader.f.glsl
    ${CMAKE_SOURCE_DIR}/src/ThirdParty/glad.c
    ${CMAKE_SOURCE_DIR}/src/ThirdParty/stb_image.h
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
file(COPY ${CMAKE_SOURCE_DIR}/dlls/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})