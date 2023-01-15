cmake_minimum_required (VERSION 3.15)

project("ImGuiRender")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} glfw opengl32)
include_directories(
    imgui
    imgui/backends
)
target_sources(${PROJECT_NAME} PRIVATE
    # app files
    src/main.cpp
    src/gui.cpp
    src/figure.cpp
    src/draw.cpp
    # ImGui files
    imgui/imgui.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_draw.cpp
)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")