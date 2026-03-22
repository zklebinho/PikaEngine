#pragma once

#include <string>

namespace pika::editor {

class InspectorPanel {
public:
    void draw(const std::string& selectedName);
};

}  // namespace pika::editor
