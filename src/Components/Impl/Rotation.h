#pragma once

#include <cmath>

struct Rotation {
    float value;

    Vector2 ForwardVector() const { return Vector2{cosf(value), sinf(value)}; }
};
