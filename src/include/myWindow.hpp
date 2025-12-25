#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#define WIDTH  640.f
#define HEIGHT 480.f

class myWindow
{
public:
    myWindow() = default;
    ~myWindow() = default;
    static void init();
    static void Input(SDL_Event* p_event);
    static void Render();
    static void destory();

private:

    static SDL_Window*   m_window;
    static SDL_GLContext m_context;
};
