#include "pika/Engine.hpp"

#include <iostream>

int main() {
    std::cout << "PikaEngine Empty Starter\n";
    pika::Engine engine;
    engine.setTickCallback([](float dt) {
        std::cout << "[Empty] Tick dt=" << dt << "\n";
    });
    engine.runFrames(3);
    return 0;
}
