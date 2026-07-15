#pragma once

#include "AudioManager/AudioManager.h"
#include "Commands/ApproachCommand.h"
#include "Impl/Acceleration.h"
#include "Impl/MaxRotationSpeed.h"
#include "Impl/MaxSpeed.h"
#include "Impl/ModuleSlot.h"
#include "Impl/MouseCollider.h"
#include "Impl/Position.h"
#include "Impl/Rotation.h"
#include "Impl/Selected.h"
#include "Impl/Speed.h"
#include "Impl/Sprite.h"
#include "Impl/TargetPosition.h"
#include "Impl/TargetRotation.h"
#include "Impl/ThrustLevel.h"
#include "Impl/Velocity.h"


// ReSharper disable CppExpressionWithoutSideEffects
inline void RegisterComponents(const flecs::world &world) {
    world.component<AssetManager>();
    world.component<AudioManager>();
    world.component<Acceleration>();
    world.component<Sprite>();
    world.component<Position>();
    world.component<VelocityVector>();
    world.component<MaxSpeed>();
    world.component<TargetPosition>();
    world.component<TargetRotation>();
    world.component<Rotation>();
    world.component<Camera2D>();
    world.component<ModuleSlotType>();
    world.component<ModuleSlotSize>();
    world.component<MaxRotationSpeed>();
    world.component<ThrustLevel>();
    world.component<Speed>();
    world.component<MouseCollider>();
    world.component<ApproachCommand>();
    world.component<Selected>().add(flecs::Singleton);
    world.set<Selected>({});
}
