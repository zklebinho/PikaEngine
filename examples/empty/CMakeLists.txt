add_executable(KYLIE_example_empty
    main.cpp
)

target_link_libraries(KYLIE_example_empty PRIVATE KylieEngine)
target_compile_features(KYLIE_example_empty PRIVATE cxx_std_20)

if(KYLIE_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(KYLIE_example_empty PRIVATE /W4 /permissive-)
    else()
        target_compile_options(KYLIE_example_empty PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
