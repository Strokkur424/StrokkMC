# Heavily inspired by https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/, as I am bad with CMake
cmake_minimum_required(VERSION 3.27)
project(StrokkMC)

add_executable(StrokkMC src/main.cpp)

set(CMAKE_CXX_STANDARD 23)

add_definitions(-DGLEW_STATIC)
add_subdirectory(libs/glfw EXCLUDE_FROM_ALL)
add_subdirectory(libs/glew EXCLUDE_FROM_ALL)
add_subdirectory(libs/glm EXCLUDE_FROM_ALL)

target_link_libraries(StrokkMC
        PRIVATE glfw
        PRIVATE libglew_static
        PRIVATE glm
)

target_include_directories(StrokkMC
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
)
