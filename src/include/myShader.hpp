#pragma once
#include <spdlog/spdlog.h>


class myShader
{
    public:
    void init(std::string p_vertPath, std::string p_fragPath);
    void destory();

    unsigned int getProgramID();

    void doUseProgram();
    void unUseProgram();


    private:
    unsigned int m_ProgramID;
    std::string readFile(std::string p_filepath);
};
