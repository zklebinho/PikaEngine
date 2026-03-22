#include "kylie/Engine.hpp"
#include "ecs/Registry.h"

#include <iostream>

struct Transform {
    float x{0}, y{0};
};

struct Velocity {
    float dx{0}, dy{0};
};

int main() {
    std::cout << "KylieEngine 2D Platformer Starter\n";

    // Basic ECS setup
    kylie::ecs::Registry registry;
    auto player = registry.create();
    registry.emplace<Transform>(player, Transform{0.0f, 0.0f});
    registry.emplace<Velocity>(player, Velocity{1.0f, 0.0f});  // move right

    // Simple physics/update loop
    kylie::Engine engine;
    engine.setTickCallback([&](float dt) {
        registry.forEach<Velocity>([&](kylie::ecs::Entity e, Velocity& vel) {
            auto& t = registry.get<Transform>(e);
            t.x += vel.dx * dt;
            t.y += vel.dy * dt;
        });
        auto& t = registry.get<Transform>(player);
        std::cout << "[Platformer] Player pos: (" << t.x << ", " << t.y << ")\n";
    });

    engine.runFrames(5, 1.0f / 60.0f);
    return 0;
}
