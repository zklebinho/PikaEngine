#include "pika/Engine.hpp"

#include <iostream>

int main() {
    pika::Engine engine;

    std::cout << "PikaEditor (CLI stub)\n";
    std::cout << "Registered modules:\n";
    for (const auto& name : engine.modules().listModules()) {
        std::cout << " - " << name << "\n";
    }

    std::cout << "Run the minimal example to see the engine tick.\n";
    return 0;
}
