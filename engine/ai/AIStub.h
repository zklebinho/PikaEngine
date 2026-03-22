#pragma once

#include <string>
#include <iostream>

namespace pika::ai {

// Placeholder for future local AI integration
class AIStub {
public:
    void initialize() {
        std::cout << "[AI] AIStub initialized (placeholder)\n";
    }

    void update(float deltaSeconds) {
        (void)deltaSeconds;
        // Future: run local inference or planner.
    }

    void shutdown() {
        std::cout << "[AI] AIStub shutdown (placeholder)\n";
    }
};

}  // namespace pika::ai
