
// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include "Util/sprite.hpp"

#include "types.hpp"

struct entity_t {
    v2f position{};
    sprite_t sprite{};

    void draw(batch2d_t &gfx, v2f camera_position, f32 zoom) const
    {
        sprite.draw(gfx, position, camera_position, zoom);
    }

    virtual ~entity_t() = default;
};
