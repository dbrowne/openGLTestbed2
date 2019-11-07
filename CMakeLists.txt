cmake_minimum_required(VERSION 3.15)
project(testbed2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS})
include_directories( "/usr/local/include" "/usr/local/Cellar/glfw/3.3/include")
set(CMAKE_INCLUDE_PATH "/usr/local/lib")
link_directories("/usr/local/lib")


add_executable(testbed2 main.cpp primatives.cpp primatives.h glad.cpp glad.h khrplatform.h Shader.h stb_image.h filesystem.h Color.cpp Color.h extra_funcs.cpp extra_funcs.h)
target_link_libraries(testbed2 ${OPENGL_LIBRARIES} GLEW::GLEW glfw)