#pragma once

#include <box2d/id.h>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include <box2d/box2d.h>
#include "myBall.hpp"
#include "myPlayer.hpp"
#include "myWindow.hpp"

const Uint64 FPS = 60;
const Uint64 MILLIESEC_PER_FRAME = 1000/FPS;

class Application
{
public:
    void run();

private:
    void init();
    void Input();
    void Update();
    void Render();
    void destory();

    b2WorldId m_worldId;
    myPlayer m_player;
    myBall m_ball;

    bool  is_running    = false;
    float m_DT          = 1.0f / 60.0f;


    // myWindow m_window;

    Uint64 millisecsLastFrame = 0;
};
