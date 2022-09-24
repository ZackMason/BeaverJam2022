// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include "types.hpp"

#include "Engine/asset_loader.hpp"
#include "Util/sprite.hpp"

#include "Game/entity.hpp"

struct player_t : entity_t {

    player_t(asset_loader_t& loader) {
        sprite.texture = loader.get_texture2d("textures/player.png");
    }
};
