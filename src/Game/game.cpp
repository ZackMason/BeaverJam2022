// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#include "Game/game.hpp"

#include "glfw/glfw3.h"

void set_textures_to_pixel_art(game_t *game) {
    assert(game);

    for (const auto &texture : game->asset_loader.texture2d_cache) {
        texture.second.resource->set_filter(false);
    }
}

game_t::game_t(window_t& w) 
    : window(w), asset_loader{"./assets/"}, player{asset_loader}
{
    window.set_event_callback([&](auto &event) {
        event_handler_t dispatcher;

        dispatcher.dispatch<const mouse_scroll_event_t>(event, [&](const mouse_scroll_event_t& scroll) {
            camera_zoom = glm::clamp(camera_zoom + scroll.y / 10.f, 1.0f, 12.0f);
            return true;
        });

        dispatcher.dispatch<const key_event_t>(event, [&](const key_event_t& key){
            switch(key.key) {
                case GLFW_KEY_ESCAPE:
                    std::terminate();
                    break;
                case GLFW_KEY_R:
                    asset_loader.reload<shader_t>();
                    break;
                default:
                    break;
            }

            return true;
        });
    });

    player.position = {160};

    game_map.set_tile_texture(1, asset_loader.get_texture2d("textures/wall_02.png"));
    game_map.set_tile_texture(2, asset_loader.get_texture2d("textures/table_n.png"));

    set_textures_to_pixel_art(this);
}

void game_t::update(const f32 dt) {
    f32 x_input = f32(window.is_key_pressed(GLFW_KEY_D)) - f32(window.is_key_pressed(GLFW_KEY_A));
    f32 y_input = f32(window.is_key_pressed(GLFW_KEY_S)) - f32(window.is_key_pressed(GLFW_KEY_W));

    if (x_input || y_input) {
        const auto t = player.position + glm::normalize(v2f{x_input, y_input}) * dt * 64.0f;
        const auto p = player.position;
        const auto player_size = player.sprite.size();

        aabb_t<v2f> x_box;
        aabb_t<v2f> y_box;
        x_box.expand(v2f{t.x, p.y});
        x_box.expand(v2f{t.x, p.y} + player_size);
        y_box.expand(v2f{p.x, t.y});
        y_box.expand(v2f{p.x, t.y} + player_size);

        if (!game_map.collide(x_box)) {
            player.position.x = t.x;
        }
        if (!game_map.collide(y_box)) {
            player.position.y = t.y;
        }
    }
}

void game_t::draw() {
    gfx.clear();
    gfx.screen_size = {window.width, window.height};

    const auto camera_position = player.position + 
        player.sprite.size()*0.5f - gfx.screen_size*0.5f;

    game_map.draw(gfx, camera_position, 1.0f);

    player.draw(gfx, camera_position, 1.0f);

    auto batch_shader = asset_loader.get_shader_nameless("shaders/batch.vs", "shaders/batch.fs");
    batch_shader.get().bind();
    batch_shader.get().set_float("uZoom", camera_zoom);
    gfx.present(
        batch_shader
    );
}


