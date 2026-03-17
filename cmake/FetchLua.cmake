include(FetchContent)

# Stub for future Lua integration.
# Today we only define an INTERFACE target so builds succeed without external deps.
add_library(pika_lua_stub INTERFACE)

if(PIKA_ENABLE_LUA)
    message(STATUS "PIKA_ENABLE_LUA is ON - linking placeholder lua stub. Replace with real Lua later.")
endif()
