#pragma once
#include "myEBO.hpp"
#include "myShader.hpp"
#include "myVAO.hpp"
#include "myVBO.hpp"

#include <box2d/box2d.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <box2d/id.h>

class myBox
{
public:
    void init(const b2WorldId& p_worldId);
    void input();
    void update();
    void render();
    void destory();

    b2BodyId getID();

private:
    b2BodyId m_ID;
    myShader m_Shader;
    myVAO    m_VAO;
    myVBO    m_VBO;
    myEBO    m_EBO;
};
