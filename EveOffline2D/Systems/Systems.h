#pragma once
#include <flecs.h>

#include "Impl/RenderBackgroundSystem.h"
#include "Impl/RenderFPSSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    RenderBackgroundSystem(world);
    RenderFPSSystem(world);
}
