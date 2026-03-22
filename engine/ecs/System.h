// System interface for ECS
#pragma once

namespace kylie::ecs {

class Registry;

class System {
public:
    virtual ~System() = default;
    virtual void update(Registry& registry, float deltaSeconds) = 0;
};

}  // namespace kylie::ecs
