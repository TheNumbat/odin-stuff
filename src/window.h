
#pragma once

#include <SDL2/SDL.h>
#include "lib/lib.h"
#include "render/vulkan.h"

struct Window {

    void init();
    void destroy();

    void begin_frame();
    void end_frame();
    
    bool get_event(SDL_Event& e);

    static constexpr char gui_name[] = "ImGui";
    using gui_alloc = Mallocator<gui_name>;

private:
    SDL_Window* window = null;
    Vulkan vk;
};

