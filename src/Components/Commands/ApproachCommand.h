#pragma once
#include <flecs.h>

struct ApproachCommand {
    flecs::entity entity;
    float distance;
};
