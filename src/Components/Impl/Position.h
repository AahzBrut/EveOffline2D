#pragma once

#include "defs.h"

struct Position {
    double x, y;

    Vector2 Vector2() const { return {toFloat(x), toFloat(y)}; }
};
