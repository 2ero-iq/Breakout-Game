#include "myVBO.hpp"
#include <glad/glad.h>

void myVBO::init(float* p_vertices, size_t p_size)
{
    glGenBuffers(1,&m_ID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, p_size, p_vertices, GL_STATIC_DRAW);
}
void myVBO::destory()
{
    glDeleteBuffers(1,&m_ID);
}

void myVBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER,m_ID);
}
void myVBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}
