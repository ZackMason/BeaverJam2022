// Author: Zackery Mason-Blaug
// Date: 2022-09-24

#include "Game/game.hpp"

#include "glfw/glfw3.h"

game_t::game_t(window_t& w) 
    : window(w), asset_loader{GAME_ASSETS_PATH}, player{asset_loader}
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
}

void game_t::update(const f32 dt) {
    f32 x_input = f32(window.is_key_pressed(GLFW_KEY_D)) - f32(window.is_key_pressed(GLFW_KEY_A));
    f32 y_input = f32(window.is_key_pressed(GLFW_KEY_S)) - f32(window.is_key_pressed(GLFW_KEY_W));

    if (x_input || y_input)
    player.position += glm::normalize(v2f{x_input, y_input}) * dt * 64.0f;
}

void game_t::draw() {
    gfx.clear();
    gfx.screen_size = {window.width, window.height};

    const auto camera_position = player.position + v2f{8.0f} - gfx.screen_size*0.5f;

    game_map.draw(gfx, camera_position, 1.0f);

    player.draw(gfx, camera_position, 1.0f);

    auto batch_shader = asset_loader.get_shader_nameless("shaders/batch.vs", "shaders/batch.fs");
    batch_shader.get().bind();
    batch_shader.get().set_float("uZoom", camera_zoom);
    gfx.present(
        batch_shader
    );
}


