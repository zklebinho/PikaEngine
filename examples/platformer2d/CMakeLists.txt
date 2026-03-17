add_executable(pika_example_platformer2d
    main.cpp
)

target_link_libraries(pika_example_platformer2d PRIVATE pikaengine)
target_compile_features(pika_example_platformer2d PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pika_example_platformer2d PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pika_example_platformer2d PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
