#pragma once

#include <string>

namespace kylie::dimensions {

struct DimensionConfig {
    std::string camera;
    std::string physics;
    std::string rendering;
};

class Dimension1D {
public:
    DimensionConfig configure() const {
        return DimensionConfig{
            .camera = "Orthographic line camera",
            .physics = "1D kinematics",
            .rendering = "Simple line renderer"
        };
    }
};

class Dimension2D {
public:
    DimensionConfig configure() const {
        return DimensionConfig{
            .camera = "Orthographic 2D camera",
            .physics = "2D rigidbody + collision",
            .rendering = "Sprite/quad renderer"
        };
    }
};

class Dimension3D {
public:
    DimensionConfig configure() const {
        return DimensionConfig{
            .camera = "Perspective 3D camera",
            .physics = "3D rigidbody + collision",
            .rendering = "Forward lit mesh renderer"
        };
    }
};

}  // namespace kylie::dimensions
