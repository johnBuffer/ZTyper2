cmake_minimum_required(VERSION 3.5)
project(ZTyper2 VERSION 1.0.0 LANGUAGES CXX)

set(SFML_DIR "" CACHE PATH "SFML lib path")
set(SFML_LIB_DIR "${SFML_DIR}/lib")
set(SFML_INC_DIR "${SFML_DIR}/include")

find_package(OpenGL)

set(SFML_LIBS "${SFML_LIB_DIR}/sfml-graphics-s.lib"
    "${SFML_LIB_DIR}/sfml-window-s.lib"
    "${SFML_LIB_DIR}/sfml-system-s.lib"
    "${SFML_LIB_DIR}/freetype.lib"
    "${OPENGL_LIBRARIES}"
    "winmm.lib"
)

file(GLOB ENGINE_SRC_FILES ${PROJECT_SOURCE_DIR}/src/Engine/*.cpp)
file(GLOB ENGINE_INC_FILES ${PROJECT_SOURCE_DIR}/include/Engine/*.hpp)
file(GLOB USER_SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB USER_INC_FILES ${PROJECT_SOURCE_DIR}/include/*.hpp)

add_executable(ZTyper2 ${ENGINE_SRC_FILES} ${ENGINE_INC_FILES} ${USER_SRC_FILES} ${USER_INC_FILES})
add_definitions(-DSFML_STATIC)
target_include_directories(ZTyper2 PRIVATE "${SFML_INC_DIR}" "include" "include/Engine")
target_link_libraries(ZTyper2 ${SFML_LIBS})