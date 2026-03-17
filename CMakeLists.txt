cmake_minimum_required(VERSION 3.20)
project(PikaEngine LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(PikaOptions)

include(FetchContent)
include(FetchGUI)

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

enable_testing()
