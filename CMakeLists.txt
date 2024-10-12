# Heavily inspired by https://github.com/ArthurSonzogni/OpenGL_CMake_Skeleton/, as I am bad with CMake
cmake_minimum_required(VERSION 3.27)
project(StrokkMC VERSION 0.0.0.0)

add_executable(StrokkMC src/game.cpp
        src/game.h
        src/render/abstract_renderer.h
        src/render/opengl_renderer.h
        src/shader.h
        src/files.h
        src/files.h
        src/shader.cpp
        src/files.cpp)

set(CMAKE_CXX_STANDARD 23)
set_target_properties(StrokkMC
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

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

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${PROJECT_SOURCE_DIR}/bin/assets
)
add_dependencies(StrokkMC copy_assets)