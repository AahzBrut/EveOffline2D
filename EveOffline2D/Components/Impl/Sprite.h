#pragma once
#include <raylib.h>
#include <raymath.h>
#include "TypeDefs.h"


struct Sprite {
    Vector2 offset;
    Vector2 size;
    Shared<Texture> texture;

    [[nodiscard]] Rectangle GetSrcRect() const {
        return Rectangle{offset.x, offset.y, size.x, size.y};
    }

    [[nodiscard]] Rectangle GetDstRect(const Vector2 position) const {
        return Rectangle{position.x, position.y, size.x, size.y};
    }

    [[nodiscard]] Vector2 GetCenterOrigin() const { return size * 0.5f; }
};
