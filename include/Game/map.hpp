// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#pragma once

#include <array>
#include <vector>

#include "Graphics/batch2d.hpp"
#include "Graphics/texture2d.hpp"

#include "Math/aabb.hpp"

template <size_t W, size_t H>
struct map_t {
    using tile_t = int;

    enum struct tile_e : tile_t {
        EMPTY, WALL, TABLE, FLOOR, SIZE
    };
    using tile_textures_t = std::array<resource_handle_t<texture2d_t>, static_cast<size_t>(tile_e::SIZE)>;

    using tile_array_t = std::array<tile_e, W * H>;

    size_t get_index(int x, int y) const {
        return y*W + x;
    }

    tile_e get_tile(int x, int y) const {
        const auto index = get_index(x,y);
        return index < (W*H) ? tiles[index] : tile_e::SIZE;
    }

    void set_tile_texture(size_t index, resource_handle_t<texture2d_t> texture) {
        assert(index < W*H);
        tile_textures[index] = texture;
    }
    
    void draw(
        batch2d_t& gfx, 
        v2f camera_center, 
        f32 camera_zoom
    ) const {
        constexpr int tile_size = 16;

        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                const auto tile = get_tile(x,y);
                if (tile == tile_e::SIZE || tile == tile_e::EMPTY) continue;

                f32 wx = camera_zoom*((x * tile_size) - camera_center.x);
                f32 wy = camera_zoom*((y * tile_size) - camera_center.y);

                gfx.draw_scaled(tile_textures[static_cast<size_t>(tile)], {wx,wy}, v2f{camera_zoom});
            }
        }
    }

    bool collide(const aabb_t<v2f>& aabb) const {
        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                const tile_e tile = get_tile(x,y);
                if (tile == tile_e::EMPTY || tile == tile_e::SIZE) continue;

                aabb_t<v2f> tile_aabb;
                tile_aabb.expand(v2f{x, y} * 16.0f);
                tile_aabb.expand(v2f{x+1, y+1} * 16.0f);

                // implement overlaps
                if (tile_aabb.contains(aabb.min))
                    return true;
                if (tile_aabb.contains(aabb.max))
                    return true;
            }  
        }
        
        return false;
    }

    map_t() {
        for (int x = 0; x < W; x++) {
            for (int y = 0; y < H; y++) {
                const bool is_edge = x == 0 || y == 0 || x == (W-1) || y == (H-1);

                const auto i = get_index(x,y);

                tiles[i] = y == 1 ? tile_e::TABLE : tile_e::EMPTY;
                tiles[i] = is_edge ? tile_e::WALL : tiles[i];
            }
        }
    }

    ~map_t() = default;
    
    tile_textures_t tile_textures{};
    tile_array_t tiles{};
};
