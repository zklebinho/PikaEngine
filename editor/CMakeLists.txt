set(EDITOR_SRC
    src/EditorApp.cpp
    ui/EditorUI.cpp
    ui/panels/ScenePanel.cpp
    ui/panels/HierarchyPanel.cpp
    ui/panels/InspectorPanel.cpp
    ui/panels/AssetsPanel.cpp
    ui/panels/ConsolePanel.cpp
    ui/panels/ViewportPanel.cpp
)

add_library(pikaeditor_lib ${EDITOR_SRC})

target_include_directories(pikaeditor_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/ui/panels
)

target_link_libraries(pikaeditor_lib PUBLIC pikaengine)
if(TARGET imgui)
    target_link_libraries(pikaeditor_lib PUBLIC imgui)
endif()
if(TARGET glfw)
    target_link_libraries(pikaeditor_lib PUBLIC glfw)
endif()
if(TARGET glad)
    target_link_libraries(pikaeditor_lib PUBLIC glad)
endif()

target_compile_features(pikaeditor_lib PUBLIC cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pikaeditor_lib PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pikaeditor_lib PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

add_executable(pikaeditor src/main.cpp)
target_link_libraries(pikaeditor PRIVATE pikaeditor_lib)
