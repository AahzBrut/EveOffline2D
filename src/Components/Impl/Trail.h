#pragma once
#include <raylib.h>
#include "TypeDefs.h"

struct Trail {
    List<Vector2> points; // front = newest (near ship), back = oldest (tail)
};
