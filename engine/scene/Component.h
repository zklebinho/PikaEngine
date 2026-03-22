#pragma once

#include <string>

namespace kylie::scene {

class Component {
public:
    virtual ~Component() = default;
    virtual std::string type() const = 0;
};

}  // namespace kylie::scene
