#pragma once
#include <flecs.h>

#include "Impl/RenderBackgroundSystem.h"
#include "Impl/RenderFPSSystem.h"
#include "Impl/RenderSpriteSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    RenderBackgroundSystem(world);
    RenderSpriteSystem(world);
    RenderFPSSystem(world);
}
