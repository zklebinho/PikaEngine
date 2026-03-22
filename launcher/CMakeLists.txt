add_executable(kylie_launcher
    main.cpp
)

target_include_directories(kylie_launcher PRIVATE
    ${CMAKE_SOURCE_DIR}/editor/src
    ${CMAKE_SOURCE_DIR}/editor
)

target_link_libraries(kylie_launcher PRIVATE KylieEngine)
if(TARGET kylieeditor_lib)
    target_link_libraries(kylie_launcher PRIVATE kylieeditor_lib)
endif()
if(TARGET imgui)
    target_link_libraries(kylie_launcher PRIVATE imgui)
endif()
if(TARGET glfw)
    target_link_libraries(kylie_launcher PRIVATE glfw)
endif()
if(TARGET glad)
    target_link_libraries(kylie_launcher PRIVATE glad)
endif()

target_compile_features(kylie_launcher PRIVATE cxx_std_20)

if(KYLIE_STRICT_WARNINGS)
    if(MSVC)
        target_compile_options(kylie_launcher PRIVATE /W4 /permissive-)
    else()
        target_compile_options(kylie_launcher PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endif()
