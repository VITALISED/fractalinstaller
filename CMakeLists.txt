cmake_minimum_required(VERSION 3.15)

project(
  renms_fractal_installer
  LANGUAGES CXX
  VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4838")

find_package(OpenGL)

add_subdirectory(glfw)

set(IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/imgui/imconfig.h
    ${CMAKE_SOURCE_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_internal.h
    ${CMAKE_SOURCE_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/imgui/imgui.h
    ${CMAKE_SOURCE_DIR}/imgui/imstb_rectpack.h
    ${CMAKE_SOURCE_DIR}/imgui/imstb_textedit.h
    ${CMAKE_SOURCE_DIR}/imgui/imstb_truetype.h
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp)

set(INSTALLER_HEADERS)

set(INSTALLER_SOURCES
    source/main.cpp
    source/load_texture.h
    source/load_texture.cpp
    source/images/background.h
    source/stb_image.h
    source/create_fonts.h
    source/create_fonts.cpp)

add_executable(installer ${INSTALLER_HEADERS} ${INSTALLER_SOURCES}
                         ${IMGUI_SOURCES} ${OPENGL_INCLUDE_DIR})

target_link_libraries(installer PRIVATE glfw ${OPENGL_LIBRARIES})

target_include_directories(installer PRIVATE ${CMAKE_SOURCE_DIR}/imgui
                                             ${CMAKE_SOURCE_DIR}/glfw/include)