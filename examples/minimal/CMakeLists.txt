add_executable(pika_example_minimal
    main.cpp
)

target_link_libraries(pika_example_minimal PRIVATE pikaengine)
target_compile_features(pika_example_minimal PRIVATE cxx_std_20)

if(TARGET sample_plugin)
    target_link_libraries(pika_example_minimal PRIVATE sample_plugin)
    target_compile_definitions(pika_example_minimal PRIVATE WITH_SAMPLE_PLUGIN)
endif()

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(pika_example_minimal PRIVATE /W4 /permissive-)
    else()
        target_compile_options(pika_example_minimal PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
