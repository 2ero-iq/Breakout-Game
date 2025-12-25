#pragma once
#include <glad/glad.h>

class myVAO
{
public:
    void init();
    void destory();

    void setData(unsigned int index, unsigned int size, unsigned int stride, unsigned int start);

    void bind();
    void unbind();

private:
    unsigned int m_ID;
};
