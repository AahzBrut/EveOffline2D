#include "RenderTrailSystem.h"

#include <raylib.h>
#include <raymath.h>

#include "defs.h"
#include "Logger.h"
#include "Components/Impl/Trail.h"


void RenderTrailSystem(const flecs::world& world) {
    world
        .system<const Trail>(__func__)
        .kind(flecs::OnStore)
        .each([](const Trail& trail) {
            const int pointCount = toInt(trail.points.size());
            if (pointCount < 2) return;

            auto trailColor = [](const float t) -> Color {
                if (t < 0.5f) {
                    const float k = t / 0.5f;
                    return ColorAlpha(Color {
                        .r = 255,
                        .g = static_cast<unsigned char>(255 * k),
                        .b = 0,
                        .a = 255
                    }, 0.9f * (1.0f - t));
                }
                const float k = (t - 0.5f) / 0.5f;
                return ColorAlpha(Color {
                    .r = 255,
                    .g = 255,
                    .b = static_cast<unsigned char>(255 * k),
                    .a = 255
                }, 0.9f * (1.0f - t));
            };

            for (int i = 0; i < pointCount - 1; ++i) {
                constexpr float tailWidth = 2.0f;
                constexpr float headWidth = 16.0f;
                const Vector2& p0 = trail.points[i];
                const Vector2& p1 = trail.points[i + 1];

                const Vector2 dir = Vector2Normalize(p1 - p0);
                const Vector2 perp = {.x = -dir.y, .y = dir.x};

                const float t0 = static_cast<float>(i) / static_cast<float>(pointCount - 1);
                const float t1 = static_cast<float>(i + 1) / static_cast<float>(pointCount - 1);
                const float w0 = headWidth * (1.0f - t0) + tailWidth * t0;
                const float w1 = headWidth * (1.0f - t1) + tailWidth * t1;

                const Vector2 l0 = {.x = p0.x + perp.x * w0 * 0.5f, .y = p0.y + perp.y * w0 * 0.5f};
                const Vector2 r0 = {.x = p0.x - perp.x * w0 * 0.5f, .y = p0.y - perp.y * w0 * 0.5f};
                const Vector2 l1 = {.x = p1.x + perp.x * w1 * 0.5f, .y = p1.y + perp.y * w1 * 0.5f};
                const Vector2 r1 = {.x = p1.x - perp.x * w1 * 0.5f, .y = p1.y - perp.y * w1 * 0.5f};

                const Color c0 = trailColor(t0);
                const Color c1 = trailColor(t1);

                const Color avg0 = {
                    .r = static_cast<unsigned char>((c0.r + c1.r) / 2),
                    .g = static_cast<unsigned char>((c0.g + c1.g) / 2),
                    .b = static_cast<unsigned char>((c0.b + c1.b) / 2),
                    .a = static_cast<unsigned char>((c0.a + c1.a) / 2)
                };

                DrawTriangle(l1, r0, l0, avg0);
                DrawTriangle(l1, r1, r0, avg0);
            }
        });
}
