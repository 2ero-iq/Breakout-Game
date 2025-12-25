#include "myVAO.hpp"
#include <glad/glad.h>

void myVAO::init()
{
    glGenVertexArrays(1,&m_ID);
}
void myVAO::destory()
{
    if(m_ID)
        glDeleteVertexArrays(1,&m_ID);
}

void myVAO::setData(unsigned int index, unsigned int size, unsigned int stride, unsigned int start)
{

    glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE,stride * sizeof(float),(void*)(start*sizeof(float)));
    glEnableVertexAttribArray(index);
}

void myVAO::bind()
{
    glBindVertexArray(m_ID);
}
void myVAO::unbind()
{
    glBindVertexArray(0);
}
