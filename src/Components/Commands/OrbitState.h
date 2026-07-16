#pragma once
#include <flecs.h>

struct OrbitState {
    flecs::entity entity;
    float distance = 0.0f;
};
