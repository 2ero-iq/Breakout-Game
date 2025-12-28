#include "myShader.hpp"


#include <glad/glad.h>

#include <SDL3/SDL_init.h>
#include <fstream>
#include <ios>
#include <spdlog/spdlog.h>

#include <cstddef>

void myShader::init(std::string p_vertPath, std::string p_fragPath)
{
    std::string l_vertCode = readFile(p_vertPath);
    std::string l_fragCode = readFile(p_fragPath);

    const char* l_vertSource = l_vertCode.c_str();
    const char* l_fragSource = l_fragCode.c_str();


    unsigned int l_vertShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int l_fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(l_vertShader, 1, &l_vertSource, NULL);
    glShaderSource(l_fragShader, 1, &l_fragSource, NULL);

    glCompileShader(l_vertShader);
    glCompileShader(l_fragShader);

    int  success;
    char infoLog[2048];

    glGetShaderiv(l_vertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(l_vertShader, 2048, NULL, infoLog);
        SPDLOG_ERROR("{}", infoLog);
    }

    glGetShaderiv(l_fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(l_fragShader, 2048, NULL, infoLog);
        SPDLOG_ERROR("{}", infoLog);
    }

    m_ProgramID = glCreateProgram();

    glAttachShader(m_ProgramID, l_vertShader);
    glAttachShader(m_ProgramID, l_fragShader);

    glLinkProgram(m_ProgramID);

    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ProgramID, 2048, NULL, infoLog);
        SPDLOG_ERROR("{}", infoLog);
    }

    glDetachShader(m_ProgramID, l_vertShader);
    glDetachShader(m_ProgramID, l_fragShader);

    glDeleteShader(l_vertShader);
    glDeleteShader(l_fragShader);
}

void myShader::destory()
{
    unUseProgram();
    if (m_ProgramID)
        glDeleteProgram(m_ProgramID);
}

unsigned int myShader::getProgramID()
{
    return m_ProgramID;
}

void myShader::doUseProgram()
{
    glUseProgram(m_ProgramID);
}

void myShader::unUseProgram()
{
    glUseProgram(0);
}

std::string myShader::readFile(std::string p_filepath)
{
    std::ifstream shaderFile(p_filepath);

    if (!shaderFile.is_open())
    {
        SPDLOG_ERROR("COULD NOT OPEN THE SHADER FILE");
        SDL_Quit();
        std::exit(-1);
    }

    shaderFile.seekg(0, std::iostream::end);
    std::streamsize len = shaderFile.tellg();
    shaderFile.seekg(0, std::iostream::beg);

    std::string res(len, ' ');


    shaderFile.read(res.data(), len);

    shaderFile.close();

    return res;
}
