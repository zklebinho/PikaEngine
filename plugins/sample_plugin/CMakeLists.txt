add_library(sample_plugin SHARED
    Plugin.cpp
)

target_link_libraries(sample_plugin PRIVATE pikaengine)
target_compile_features(sample_plugin PRIVATE cxx_std_20)

if(PIKA_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(sample_plugin PRIVATE /W4 /permissive-)
    else()
        target_compile_options(sample_plugin PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
