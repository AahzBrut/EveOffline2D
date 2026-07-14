#pragma once
#include <flecs.h>

#include "Impl/BeginCameraSystem.h"
#include "Impl/CameraControlSystem.h"
#include "Impl/DebugUISystem.h"
#include "Impl/EndCameraSystem.h"
#include "Impl/InputSystem.h"
#include "Impl/MovementSystem.h"
#include "Impl/RenderBackgroundSystem.h"
#include "Impl/RenderSpriteSystem.h"
#include "Impl/RotationSytem.h"
#include "Impl/ThrustSystem.h"


inline void RegisterSystems(const flecs::world &world) {
    CameraControlSystem(world);
    InputSystem(world);
    RotationSystem(world);
    ThrustSystem(world);
    MovementSystem(world);
    RenderBackgroundSystem(world);
    BeginCameraSystem(world);
    RenderSpriteSystem(world);
    EndCameraSystem(world);
    DebugUISystem(world);
}
