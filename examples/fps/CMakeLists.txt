add_executable(KYLIE_example_fps
    main.cpp
)

target_link_libraries(KYLIE_example_fps PRIVATE KylieEngine)
target_compile_features(KYLIE_example_fps PRIVATE cxx_std_20)

if(KYLIE_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(KYLIE_example_fps PRIVATE /W4 /permissive-)
    else()
        target_compile_options(KYLIE_example_fps PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
