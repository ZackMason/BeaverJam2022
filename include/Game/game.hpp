// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include "Game/map.hpp"
#include "Game/player.hpp"
#include "Game/trigger.hpp"

#include "Engine/asset_loader.hpp"
#include "Engine/window.hpp"

struct game_t {
    window_t& window;
    asset_loader_t asset_loader;

    map_t<40,30> game_map;
    player_t player;
    batch2d_t gfx;

    f32 camera_zoom{1.0f};

    void update(const f32 dt);
    void draw();

    game_t(window_t& w);
};
