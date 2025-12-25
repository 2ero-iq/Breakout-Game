#include "myWindow.hpp"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <spdlog/spdlog.h>

SDL_Window*   myWindow::m_window  = nullptr;
SDL_GLContext myWindow::m_context = nullptr;


void myWindow::init()
{

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow("test", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!m_window)
    {
        SPDLOG_ERROR("COULD NOT CREATE WINDOW");
        SDL_Quit();
    }
    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context)
    {
        SPDLOG_ERROR("COULD NOT CREATE WINDOW");
        SDL_Quit();
    }

    SDL_GL_MakeCurrent(m_window, m_context);
}

void myWindow::Input(SDL_Event* p_event)
{
}

void myWindow::Render()
{
    SDL_GL_SwapWindow(m_window);
}

void myWindow::destory()
{
    SDL_DestroyWindow(m_window);
}
