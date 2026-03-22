include(FetchContent)

# Stub for future Lua integration.
# Today we only define an INTERFACE target so builds succeed without external deps.
add_library(KYLIE_lua_stub INTERFACE)

if(KYLIE_ENABLE_LUA)
    message(STATUS "KYLIE_ENABLE_LUA is ON - linking placeholder lua stub. Replace with real Lua later.")
endif()
