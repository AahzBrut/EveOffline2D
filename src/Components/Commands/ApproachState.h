#pragma once
#include <flecs.h>

struct ApproachState {
    flecs::entity entity;
    float distance = 0.0f;
};
