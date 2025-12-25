#pragma once
#include <glad/glad.h>

#include <cstddef>

class myEBO
{
public:
    void init(unsigned int* p_idicate, size_t p_size);
    void destory();

    void bind();
    void unbind();

private:
    unsigned int m_ID;
};
