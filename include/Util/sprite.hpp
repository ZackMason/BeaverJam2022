
// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include "Graphics/texture2d.hpp"
#include "Graphics/batch2d.hpp"
#include "Engine/resource_handle.hpp"

struct sprite_t {
    resource_handle_t<texture2d_t> texture;

    v2f size() const {
        return v2f{
            texture.get().width,
            texture.get().height
        };
    }

    void draw(batch2d_t& gfx, v2f position, v2f camera_position, f32 zoom) const {
        gfx.draw_scaled(texture, position - camera_position, v2f{zoom});
    }
};
