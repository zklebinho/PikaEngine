add_executable(pikaeditor
    src/main.cpp
)

target_link_libraries(pikaeditor PRIVATE pikaengine)
if(TARGET imgui)
    target_link_libraries(pikaeditor PRIVATE imgui)
endif()
if(TARGET glfw)
    target_link_libraries(pikaeditor PRIVATE glfw)
endif()
if(TARGET glad)
    target_link_libraries(pikaeditor PRIVATE glad)
endif()
target_compile_features(pikaeditor PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pikaeditor PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pikaeditor PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
