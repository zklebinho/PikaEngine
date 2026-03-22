cmake_minimum_required(VERSION 3.20)
project(PikaEngine LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(PikaOptions)

include(FetchContent)

if(PIKA_ENABLE_RENDERER OR BUILD_EDITOR OR BUILD_SANDBOX OR BUILD_LAUNCHER)
    include(FetchGUI)
endif()

if(PIKA_ENABLE_LUA)
    include(FetchLua)
endif()

add_subdirectory(engine)

if(BUILD_EDITOR)
    add_subdirectory(editor)
endif()

if(BUILD_PLUGINS)
    add_subdirectory(plugins)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_SANDBOX)
    add_executable(pika_sandbox engine/sandbox/SandboxApp.cpp)
    target_link_libraries(pika_sandbox PRIVATE pikaengine)
    if(TARGET imgui)
        target_link_libraries(pika_sandbox PRIVATE imgui)
    endif()
    if(TARGET glfw)
        target_link_libraries(pika_sandbox PRIVATE glfw)
    endif()
    if(TARGET glad)
        target_link_libraries(pika_sandbox PRIVATE glad)
    endif()
    target_compile_features(pika_sandbox PRIVATE cxx_std_20)
    if(PIKA_STRICT_WARNINGS)
        if(MSVC)
            target_compile_options(pika_sandbox PRIVATE /W4 /permissive-)
        else()
            target_compile_options(pika_sandbox PRIVATE -Wall -Wextra -Wpedantic -Werror)
        endif()
    endif()
endif()

if(BUILD_LAUNCHER)
    add_subdirectory(launcher)
endif()

enable_testing()
