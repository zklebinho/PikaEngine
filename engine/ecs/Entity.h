// Lightweight entity handle
#pragma once

#include <cstdint>

namespace kylie::ecs {

struct Entity {
    using id_type = std::uint32_t;
    using version_type = std::uint32_t;

    id_type id{0};
    version_type version{0};

    bool operator==(const Entity& other) const { return id == other.id && version == other.version; }
    bool operator!=(const Entity& other) const { return !(*this == other); }

    static Entity null() { return {}; }
};

}  // namespace kylie::ecs
