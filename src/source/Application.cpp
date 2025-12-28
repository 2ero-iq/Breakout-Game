#include "Application.hpp"
#include "myWindow.hpp"
#include <box2d/id.h>
#include <box2d/math_functions.h>
#include <box2d/types.h>


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

    b2WorldDef l_worldDef = b2DefaultWorldDef();
    l_worldDef.gravity = (b2Vec2){0.0,0.0};

    m_worldId = b2CreateWorld(&l_worldDef);

    m_player.init(m_worldId);
    m_ball.init(m_worldId);

    // Making the world walls

    {
        b2BodyDef l_wallDef = b2DefaultBodyDef();
        l_wallDef.type = b2_staticBody;
        b2ShapeDef l_shapeShapeDef = b2DefaultShapeDef();
        l_shapeShapeDef.material.restitution = 1.0f;
        l_shapeShapeDef.material.friction = 0.0f;

        // left wall
        l_wallDef.position = (b2Vec2){0.0-5.f,HEIGHT/2.f};
        b2BodyId LeftWall = b2CreateBody(m_worldId, &l_wallDef);
        b2Polygon LeftWallShape = b2MakeBox(5.f,HEIGHT/2.f);
        b2CreatePolygonShape(LeftWall, &l_shapeShapeDef, &LeftWallShape);

        // Right wall
        l_wallDef.position = (b2Vec2){WIDTH+5.f,HEIGHT/2.f};
        b2BodyId RightWall = b2CreateBody(m_worldId, &l_wallDef);
        b2Polygon RightWallShape = b2MakeBox(5.f, HEIGHT/2.f);
        b2CreatePolygonShape(RightWall, &l_shapeShapeDef, &RightWallShape);


        // Up wall
        l_wallDef.position = (b2Vec2){WIDTH/2.f,HEIGHT+5.f};
        b2BodyId UpWall = b2CreateBody(m_worldId, &l_wallDef);
        b2Polygon UpWallShape = b2MakeBox(WIDTH,5.f);
        b2CreatePolygonShape(UpWall, &l_shapeShapeDef, &UpWallShape);

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

    m_player.input();
    m_player.input();
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

    m_player.update();
    m_ball.update();
    b2World_Step(m_worldId, 1/60.f, 4);


}

void Application::Render()
{
    glClearColor(29 / 255.f, 32 / 255.f, 33 / 255.f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_player.render();
    m_ball.render();
    myWindow::Render();
}

void Application::destory()
{
    m_player.destory();
    m_ball.destory();
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
