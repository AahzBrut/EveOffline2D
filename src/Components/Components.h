#pragma once
#include "AssetManager/AssetManager.h"
#include "AudioManager/AudioManager.h"
#include "Impl/MaxSpeed.h"
#include "Impl/ModuleSlot.h"
#include "Impl/Position.h"
#include "Impl/Rotation.h"
#include "Impl/Sprite.h"
#include "Impl/TargetPosition.h"
#include "Impl/Velocity.h"


// ReSharper disable file CppExpressionWithoutSideEffects
inline void RegisterComponents(const flecs::world &world) {
    world.component<AssetManager>();
    world.component<AudioManager>();
    world.component<Sprite>();
    world.component<Position>();
    world.component<VelocityVector>();
    world.component<MaxSpeed>();
    world.component<TargetPosition>();
    world.component<Rotation>();
    world.component<Camera2D>();
    world.component<ModuleSlotType>();
}
