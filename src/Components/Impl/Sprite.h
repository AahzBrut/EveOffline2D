#pragma once
#include <raylib.h>
#include <raymath.h>
#include "TypeDefs.h"


struct Sprite {
    Vector2 offset;
    Vector2 size;
    Shared<Texture> texture;
    float rotation = 0.0f;
    float scale = 1.0f;

    [[nodiscard]] Rectangle GetSrcRect() const {
        return Rectangle{offset.x, offset.y, size.x, size.y};
    }

    [[nodiscard]] Rectangle GetDstRect(const Vector2 position) const {
        return Rectangle{position.x, position.y, size.x * scale, size.y * scale};
    }

    [[nodiscard]] Vector2 GetCenterOrigin() const { return size * scale * 0.5f; }
};
