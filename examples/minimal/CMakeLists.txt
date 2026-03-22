add_executable(KYLIE_example_minimal
    main.cpp
)

target_link_libraries(KYLIE_example_minimal PRIVATE KylieEngine)
target_compile_features(KYLIE_example_minimal PRIVATE cxx_std_20)

if(TARGET sample_plugin)
    target_link_libraries(KYLIE_example_minimal PRIVATE sample_plugin)
    target_compile_definitions(KYLIE_example_minimal PRIVATE WITH_SAMPLE_PLUGIN)
endif()

if(KYLIE_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(KYLIE_example_minimal PRIVATE /W4 /permissive-)
    else()
        target_compile_options(KYLIE_example_minimal PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
