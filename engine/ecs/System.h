// System interface for ECS
#pragma once

namespace pika::ecs {

class Registry;

class System {
public:
    virtual ~System() = default;
    virtual void update(Registry& registry, float deltaSeconds) = 0;
};

}  // namespace pika::ecs
