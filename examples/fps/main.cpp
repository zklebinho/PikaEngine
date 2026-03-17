#include "pika/Engine.hpp"
#include "ecs/Registry.h"

#include <iostream>

struct Transform {
    float x{0}, y{0}, z{0};
};

struct Camera {
    float pitch{0}, yaw{0};
};

int main() {
    std::cout << "PikaEngine FPS Starter\n";

    pika::ecs::Registry registry;
    auto player = registry.create();
    registry.emplace<Transform>(player, Transform{0, 1.6f, 0});
    registry.emplace<Camera>(player, Camera{0, 0});

    pika::Engine engine;
    engine.setTickCallback([&](float dt) {
        // Placeholder input: move forward and yaw slightly each frame
        auto& t = registry.get<Transform>(player);
        auto& cam = registry.get<Camera>(player);
        t.z -= 2.0f * dt;      // forward
        cam.yaw += 10.0f * dt; // turn
        std::cout << "[FPS] Pos(" << t.x << "," << t.y << "," << t.z << ") Yaw:" << cam.yaw << "\n";
    });

    engine.runFrames(5, 1.0f / 60.0f);
    return 0;
}
