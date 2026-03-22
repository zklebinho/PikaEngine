#include "kylie/Engine.hpp"

#include <iostream>

int main() {
    std::cout << "KylieEngine Empty Starter\n";
    kylie::Engine engine;
    engine.setTickCallback([](float dt) {
        std::cout << "[Empty] Tick dt=" << dt << "\n";
    });
    engine.runFrames(3);
    return 0;
}
