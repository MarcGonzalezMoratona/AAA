#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "SDL/include/SDL.h"
#include "GL/glew.h"

ModuleProgram::ModuleProgram()
{}

ModuleProgram::~ModuleProgram()
{}

bool ModuleProgram::Init()
{
    LOG("Init shader loader program");
    return true;
}

update_status ModuleProgram::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
    LOG("Destroying program");
    return true;
}


unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
    unsigned shader_id = glCreateShader(type);
    glShaderSource(shader_id, 1, &source, 0);
    glCompileShader(shader_id);
    int res = GL_FALSE;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetShaderInfoLog(shader_id, len, &written, info);
            LOG("Log Info: %s", info);
            free(info);
        }
    }
    return shader_id;
}
