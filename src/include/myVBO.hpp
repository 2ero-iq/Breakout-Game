#pragma once
#include <glad/glad.h>

#include <cstddef>

class myVBO
{
public:
    void init(float* p_vertices, size_t p_size);
    void destory();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
};
