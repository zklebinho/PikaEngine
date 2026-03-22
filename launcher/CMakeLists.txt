add_executable(pika_launcher
    main.cpp
)

target_include_directories(pika_launcher PRIVATE
    ${CMAKE_SOURCE_DIR}/editor/src
    ${CMAKE_SOURCE_DIR}/editor
)

target_link_libraries(pika_launcher PRIVATE pikaengine)
if(TARGET pikaeditor_lib)
    target_link_libraries(pika_launcher PRIVATE pikaeditor_lib)
endif()
if(TARGET imgui)
    target_link_libraries(pika_launcher PRIVATE imgui)
endif()
if(TARGET glfw)
    target_link_libraries(pika_launcher PRIVATE glfw)
endif()
if(TARGET glad)
    target_link_libraries(pika_launcher PRIVATE glad)
endif()

target_compile_features(pika_launcher PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pika_launcher PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pika_launcher PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
