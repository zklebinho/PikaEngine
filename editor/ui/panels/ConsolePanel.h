#pragma once

#include <string>
#include <vector>

namespace pika::editor {

class ConsolePanel {
public:
    void draw(const std::vector<std::string>& lines);
};

}  // namespace pika::editor
