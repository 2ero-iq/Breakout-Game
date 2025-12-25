#include "Application.hpp"
#include "myWindow.hpp"

#include <glad/glad.h>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <spdlog/spdlog.h>


void Application::init()
{
    is_running = true;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SPDLOG_ERROR("COULD NOT INIT SDL");
        is_running = false;
    }
    myWindow::init();


    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SPDLOG_ERROR("COULD NOT INIT GLAD");
        is_running = false;
    }


}

void Application::Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
            is_running = false;

        if (e.type == SDL_EVENT_KEY_DOWN)
            if (e.key.scancode == SDL_SCANCODE_ESCAPE)
                is_running = false;

        myWindow::Input(&e);
    }

}

void Application::Update()
{

    int time2wait = MILLIESEC_PER_FRAME - (SDL_GetTicks() - millisecsLastFrame);
    if(time2wait > 0 &&  time2wait <= (int)MILLIESEC_PER_FRAME)
        SDL_Delay(time2wait);

    m_DT = (SDL_GetTicks() - millisecsLastFrame)/1000.f;

    // while (!(SDL_GetTicks() >= MILLIESEC_PER_FRAME + millisecsLastFrame))
    //     ;
    millisecsLastFrame = SDL_GetTicks();


}

void Application::Render()
{
    glClearColor(29 / 255.f, 32 / 255.f, 33 / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    myWindow::Render();
}

void Application::destory()
{
    myWindow::destory();
    SDL_Quit();
}


void Application::run()
{
    init();
    while (is_running)
    {
        Input();
        Update();
        Render();
    }
    destory();
}
