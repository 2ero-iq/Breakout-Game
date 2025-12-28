#include "myEBO.hpp"
#include <glad/glad.h>

void myEBO::init(unsigned int* p_idicate, size_t p_size)
{
    glGenBuffers(1,&m_ID);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_size, p_idicate, GL_STATIC_DRAW);
}
void myEBO::destory()
{
    unbind();
    glDeleteBuffers(1,&m_ID);
}

void myEBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ID);
}
void myEBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
