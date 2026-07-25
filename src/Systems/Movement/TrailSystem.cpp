#include "TrailSystem.h"

#include <algorithm>
#include <cmath>
#include <raylib.h>
#include <raymath.h>

#include "Logger.h"
#include "Components/Impl/MaxSpeed.h"
#include "Components/Impl/Position.h"
#include "Components/Impl/Rotation.h"
#include "Components/Impl/Speed.h"
#include "Components/Impl/Trail.h"


constexpr int TrailMinSegments = 16;
constexpr int TrailMaxPoints = 250;
constexpr float TrailTailLength = 16.0f;       // base width at the ship end
constexpr float TrailDecayRate = 2.0f;          // how fast points fade when not moving
constexpr float TrailMinSpeed = 1.0f;           // below this speed we start decaying
constexpr float TrailSegmentSpacing = 3.0f;     // min distance to add a new point


void TrailSystem(const flecs::world& world) {
    world
        .system<Trail, const Position, const Speed, const MaxSpeed>(__func__)
        .kind(flecs::OnUpdate)
        .each([](const flecs::iter& it, const size_t,
                 Trail& trail,
                 const Position& position,
                 const Speed& speed,
                 const MaxSpeed& maxSpeed) {
            const float dt = it.delta_time();
            const float currentSpeed = speed.effectiveValue;
            const float maxSpeedVal = maxSpeed.effectiveValue;

            // Determine desired trail length based on speed ratio
            const float speedRatio = maxSpeedVal > 0.0f ? currentSpeed / maxSpeedVal : 0.0f;
            const int desiredPoints = std::max(0, std::min(TrailMaxPoints,
                static_cast<int>(TrailMinSegments + speedRatio * (TrailMaxPoints - TrailMinSegments))));

            // If moving fast enough, add new point at ship position
            if (currentSpeed > TrailMinSpeed) {
                const Vector2 newPos = position.Vector2();
                bool shouldAdd = false;
                if (trail.points.empty()) {
                    shouldAdd = true;
                } else {
                    const Vector2& front = trail.points.front();
                    if (Vector2Distance(newPos, front) >= TrailSegmentSpacing) {
                        shouldAdd = true;
                    }
                }
                if (shouldAdd) {
                    trail.points.insert(trail.points.begin(), newPos);
                }
            }

            // Trim to desired length (remove old tail points)
            while (static_cast<int>(trail.points.size()) > desiredPoints) {
                trail.points.pop_back();
            }

            // When slow/stopped, gradually shrink the trail (decay from tail)
            if (currentSpeed <= TrailMinSpeed) {
                const int removeCount = std::max(1, toInt(trail.points.size() * TrailDecayRate * dt));
                for (int i = 0; i < removeCount && !trail.points.empty(); ++i) {
                    trail.points.pop_back();
                }
            }
        });
}
