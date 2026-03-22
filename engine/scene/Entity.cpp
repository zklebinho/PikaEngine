#include "Entity.h"

namespace kylie::scene {

Entity::Entity(std::uint32_t id, std::string name)
    : id_(id), name_(std::move(name)) {}

}  // namespace kylie::scene
