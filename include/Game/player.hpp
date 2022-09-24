// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include "types.hpp"

#include "Engine/asset_loader.hpp"
#include "Util/sprite.hpp"

struct player_t {
    v2f position{0.0f};
    sprite_t sprite;

    void draw(batch2d_t& gfx, v2f camera_position, f32 zoom) const {
        sprite.draw(gfx, position, camera_position, zoom);
    }

    player_t(asset_loader_t& loader) {
        sprite.texture = loader.get_texture2d("textures/player.png");
    }
};
