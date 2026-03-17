add_library(pikaengine
    src/Engine.cpp
    src/Module.cpp
    src/Scripting.cpp
    src/NodeGraph.cpp
    renderer/Renderer.cpp
    renderer/Window.cpp
    scripting/ScriptSystem.cpp
    scripting/PythonBridge.cpp
)

target_include_directories(pikaengine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(pikaengine PUBLIC cxx_std_20)

target_compile_definitions(pikaengine PUBLIC $<$<BOOL:${PIKA_ENABLE_LUA}>:PIKA_ENABLE_LUA>)
target_compile_definitions(pikaengine PUBLIC $<$<BOOL:${PIKA_ENABLE_PYTHON}>:PIKA_ENABLE_PYTHON>)

if(PIKA_ENABLE_LUA AND TARGET pika_lua_stub)
    target_link_libraries(pikaengine PUBLIC pika_lua_stub)
endif()

if(TARGET glfw)
    target_link_libraries(pikaengine PUBLIC glfw)
endif()
if(TARGET glad)
    target_link_libraries(pikaengine PUBLIC glad)
endif()
if(TARGET imgui)
    target_link_libraries(pikaengine PUBLIC imgui)
endif()
target_compile_definitions(pikaengine PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

if(PIKA_ENABLE_PYTHON)
    find_package(Python3 COMPONENTS Development)
    if(Python3_Development_FOUND)
        target_include_directories(pikaengine PUBLIC ${Python3_INCLUDE_DIRS})
        target_link_libraries(pikaengine PUBLIC ${Python3_LIBRARIES})
    else()
        message(WARNING "Python development headers not found; Python bridge will build but may fail to link.")
    endif()
endif()

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pikaengine PRIVATE /W4 /permissive- /wd4251)
    else()
        target_compile_options(pikaengine PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()

# Core demo executable
add_executable(pika_core
    core/main.cpp
    core/Engine.cpp
)

target_include_directories(pika_core PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pika_core PRIVATE pikaengine)
target_compile_features(pika_core PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pika_core PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pika_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
