#include "myPlayer.hpp"
#include "myWindow.hpp"
#include <glm/gtc/type_ptr.hpp>



void myPlayer::init(const b2WorldId& p_worldId)
{
    b2BodyDef l_bodyDef = b2DefaultBodyDef();
    l_bodyDef.type = b2_kinematicBody;
    // l_bodyDef.position = (b2Vec2){WIDTH/2.f,HEIGHT/2.f};
    l_bodyDef.position = (b2Vec2){WIDTH/2.f,20.f};

    m_ID = b2CreateBody(p_worldId, &l_bodyDef);

    b2Polygon boxShape = b2MakeBox(30.f, 5.f);
    b2ShapeDef l_shapeDef = b2DefaultShapeDef();

    b2CreatePolygonShape(m_ID, &l_shapeDef, &boxShape);

    float l_vertices[] =
    {

        boxShape.vertices[0].x, boxShape.vertices[0].y,
        boxShape.vertices[1].x, boxShape.vertices[1].y,
        boxShape.vertices[2].x, boxShape.vertices[2].y,
        boxShape.vertices[3].x, boxShape.vertices[3].y,
    };

    unsigned int l_ind[] =
    {
        0,1,2,
        0,2,3
    };

    m_Shader.init("../src/shader/shader.vert", "../src/shader/shader.frag");

    m_Shader.doUseProgram();
    m_VAO.init();
    m_VAO.bind();

    m_VBO.init(l_vertices,sizeof(l_vertices));
    m_EBO.init(l_ind, sizeof(l_ind));

    m_VAO.setData(0, 2, 2, 0);

    m_VAO.unbind();

}
void myPlayer::input()
{
    const bool* key = SDL_GetKeyboardState(nullptr);

    b2Vec2 vel = { 0.0f, 0.0f };
    float speed = 300.0f; // units per second (pixels in your case)

    b2Vec2 l_pos = b2Body_GetPosition(m_ID);


    if (key[SDL_SCANCODE_RIGHT])
    {
        vel.x = speed;
    }

    else if (key[SDL_SCANCODE_LEFT])
    {
        vel.x = -speed;
    }

    l_pos.x = b2ClampFloat(l_pos.x, 30, WIDTH-30);
    b2Body_SetTransform(m_ID, l_pos, b2Body_GetRotation(m_ID));

    b2Body_SetLinearVelocity(m_ID, vel);
}

void myPlayer::update()
{
    m_Shader.doUseProgram();

    b2Vec2 l_pos = b2Body_GetPosition(m_ID);
    glm::mat4 model = glm::translate(glm::mat4(1), glm::vec3(l_pos.x,l_pos.y,0.0f));
    glm::mat4 projection = glm::ortho(
        0.f,WIDTH,
        0.f,HEIGHT,
        -1.f,1.f
    );

    unsigned int modLoc = glGetUniformLocation(m_Shader.getProgramID(),"Model");
    unsigned int projLoc = glGetUniformLocation(m_Shader.getProgramID(),"Projection");

    glUniformMatrix4fv(modLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    m_Shader.unUseProgram();

}
void myPlayer::render()
{
    m_Shader.doUseProgram();
    m_VAO.bind();
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

    m_Shader.unUseProgram();
    m_VAO.unbind();
}
void myPlayer::destory()
{

    b2DestroyBody(m_ID);


    m_Shader.destory();  // glDeleteProgram
    m_VAO.destory();     // glDeleteVertexArrays
    m_VBO.destory();     // glDeleteBuffers
    m_EBO.destory();     // glDeleteBuffers
}
