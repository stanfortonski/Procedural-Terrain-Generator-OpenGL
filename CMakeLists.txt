cmake_minimum_required(VERSION 3.0)

project(terrain)

include_directories(include)

link_directories(${CMAKE_SOURCE_DIR}/lib)
include_directories(${CMAKE_BINARY_DIR}/include)

add_compile_options(-m64)
set(ENGINE_NAME engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O4")
set(BUILD_SHARED_LIBS True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_BUILD_TYPE Release)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Freetype REQUIRED)

set(LIBS glfw gdi32 opengl32 glew32 assimp zlibstatic)

include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

#make stb_image lib
add_library(stb_image ${CMAKE_SOURCE_DIR}/src/stb_image.cpp)
set(LIBS ${LIBS} stb_image)

#make engine lib
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/engine/*.cpp)
add_library(${ENGINE_NAME} ${SOURCES})

set(LIBS ${LIBS} ${FREETYPE_LIBRARIES})
target_link_libraries(${ENGINE_NAME} ${LIBS})
target_include_directories(${ENGINE_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})

#make exe file
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/generator/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
  ${PROJECT_NAME}
  ${ENGINE_NAME}
)
