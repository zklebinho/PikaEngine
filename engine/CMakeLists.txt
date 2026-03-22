set(PIKA_ENGINE_SRC
    core/EngineApp.cpp
    src/Module.cpp
    src/Scripting.cpp
    src/NodeGraph.cpp
    scripting/ScriptSystem.cpp
    scripting/PythonBridge.cpp
    plugins/PluginManager.cpp
    ai/AIStub.cpp
    sandbox/SandboxScene.cpp
)

if(PIKA_ENABLE_RENDERER)
    list(APPEND PIKA_ENGINE_SRC
        renderer/Renderer.cpp
        window/Window.cpp
    )
endif()

add_library(pikaengine ${PIKA_ENGINE_SRC})

target_include_directories(pikaengine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(pikaengine PUBLIC cxx_std_20)

target_compile_definitions(pikaengine PUBLIC
    $<$<BOOL:${PIKA_ENABLE_LUA}>:PIKA_ENABLE_LUA>
    $<$<BOOL:${PIKA_ENABLE_PYTHON}>:PIKA_ENABLE_PYTHON>
    $<$<BOOL:${PIKA_ENABLE_RENDERER}>:PIKA_ENABLE_RENDERER>
)

if(PIKA_ENABLE_LUA AND TARGET pika_lua_stub)
    target_link_libraries(pikaengine PUBLIC pika_lua_stub)
endif()

if(PIKA_ENABLE_RENDERER)
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
endif()

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
