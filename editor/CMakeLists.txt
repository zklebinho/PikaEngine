add_executable(pikaeditor
    src/main.cpp
)

target_link_libraries(pikaeditor PRIVATE pikaengine)
target_compile_features(pikaeditor PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pikaeditor PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pikaeditor PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
