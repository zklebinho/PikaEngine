set(KYLIE_ENGINE_SRC
    core/EngineApp.cpp
    src/Module.cpp
    src/Scripting.cpp
    src/NodeGraph.cpp
    scripting/ScriptSystem.cpp
    scripting/PythonBridge.cpp
    plugins/PluginManager.cpp
    ai/AIStub.cpp
    sandbox/SandboxScene.cpp
    scene/Scene.cpp
    scene/Entity.cpp
    scene/SceneManager.cpp
    visual_scripting/Graph.cpp
)

if(KYLIE_ENABLE_RENDERER)
    list(APPEND KYLIE_ENGINE_SRC
        renderer/Renderer.cpp
        window/Window.cpp
    )
endif()

add_library(KylieEngine ${KYLIE_ENGINE_SRC})

target_include_directories(KylieEngine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(KylieEngine PUBLIC cxx_std_20)

target_compile_definitions(KylieEngine PUBLIC
    $<$<BOOL:${KYLIE_ENABLE_LUA}>:KYLIE_ENABLE_LUA>
    $<$<BOOL:${KYLIE_ENABLE_PYTHON}>:KYLIE_ENABLE_PYTHON>
    $<$<BOOL:${KYLIE_ENABLE_RENDERER}>:KYLIE_ENABLE_RENDERER>
)

if(KYLIE_ENABLE_LUA AND TARGET KYLIE_lua_stub)
    target_link_libraries(KylieEngine PUBLIC KYLIE_lua_stub)
endif()

if(KYLIE_ENABLE_RENDERER)
    if(TARGET glfw)
        target_link_libraries(KylieEngine PUBLIC glfw)
    endif()
    if(TARGET glad)
        target_link_libraries(KylieEngine PUBLIC glad)
    endif()
    if(TARGET imgui)
        target_link_libraries(KylieEngine PUBLIC imgui)
    endif()
    target_compile_definitions(KylieEngine PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
endif()

if(KYLIE_ENABLE_PYTHON)
    find_package(Python3 COMPONENTS Development)
    if(Python3_Development_FOUND)
        target_include_directories(KylieEngine PUBLIC ${Python3_INCLUDE_DIRS})
        target_link_libraries(KylieEngine PUBLIC ${Python3_LIBRARIES})
    else()
        message(WARNING "Python development headers not found; Python bridge will build but may fail to link.")
    endif()
endif()

if(KYLIE_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(KylieEngine PRIVATE /W4 /permissive- /wd4251)
    else()
        target_compile_options(KylieEngine PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
