
#define WIN32_MEAN_AND_LEAN
#define NOMINMAX

#include "core.hpp"

#include <glad/glad.h>

#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Engine/window.hpp"

#include "Game/game.hpp"

#include "Util/timer.hpp"
#include "Util/color.hpp"

int main(int argc, char** argv) {
    window_t window;
    window.width = 640;
    window.height = 480;

    window.open_window();

    window.set_title("Nuclear Meltdown");

    try {
        game_t game{window};

        timer32_t frame_timer;
        v3f color{color::v3::gray};
        
        while(!window.should_close()) {
            glClearColor(color.r, color.g, color.b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            /////////////////////////////
            game.update(frame_timer.get_dt(window.get_ticks()));

            game.draw();

            /////////////////////////////
            window.poll_events();
            window.swap_buffers();
        }
    } catch (std::exception& e) {
        logger_t::warn(e.what());
    }

    return 0;
}