#pragma once

#include <cmath>
#include <raylib.h>


struct Rotation {
    float value;

    Vector2 ForwardVector() const { return Vector2{cosf(value), sinf(value)}; }
};
