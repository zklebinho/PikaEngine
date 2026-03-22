#pragma once

#include <string>
#include <vector>

namespace kylie::editor {

class ConsolePanel {
public:
    void draw(const std::vector<std::string>& lines);
};

}  // namespace kylie::editor
