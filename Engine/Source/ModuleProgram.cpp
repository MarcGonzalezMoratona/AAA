#include "Globals.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleEditor.h"
#include "SDL/include/SDL.h"
#include "GL/glew.h"
#include "PanelConsole.h"

ModuleProgram::ModuleProgram()
{
    program = 0;
}

ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
    App->editor->AddLog("Init shader loader program");
    return true;
}

bool ModuleProgram::Start()
{
    CreateProgram();
    return true;
}

update_status ModuleProgram::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
    App->editor->AddLog("Destroying program");
    return true;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
    char* data = nullptr;
    FILE* file = nullptr;
    fopen_s(&file, shader_file_name, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        data = (char*)malloc(size + 1);
        fseek(file, 0, SEEK_SET);
        fread(data, 1, size, file);
        data[size] = 0;
        fclose(file);
    }
    return data;
}

void ModuleProgram::CreateProgram()
{
    char* vertexShaderSource = LoadShaderSource("./Shaders/VertexShader.glsl");
    char* fragmentShaderSource = LoadShaderSource("./Shaders/FragmentShader.glsl");
    vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned program_id = glCreateProgram();
    glAttachShader(program_id, vertexShader);
    glAttachShader(program_id, fragmentShader);
    glLinkProgram(program_id);
    int res;
    glGetProgramiv(program_id, GL_LINK_STATUS, &res);
    if (res == GL_FALSE)
    {
        int len = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
        if (len > 0)
        {
            int written = 0;
            char* info = (char*)malloc(len);
            glGetProgramInfoLog(program_id, len, &written, info);
            DEBUGLOG("Program Log Info: %s", info);
            free(info);
        }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    program = program_id;
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
            DEBUGLOG("Log Info: %s", info);
            free(info);
        }
    }
    return shader_id;
}
