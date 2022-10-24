#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "SDL.h"
#include "GL/glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

char* ModuleRenderExercise::LoadShaderSource(const char* shader_file_name)
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

unsigned ModuleRenderExercise::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
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
			LOG("Program Log Info: %s", info);
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return program_id;
}

bool ModuleRenderExercise::Init()
{

	LOG("Creating render exercise");
	float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	char* vertexShaderSource = LoadShaderSource("./Shaders/VertexShader.glsl");
	char* fragmentShaderSource = LoadShaderSource("./Shaders/FragmentShader.glsl");
	App->program->vertexShader = App->program->CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	App->program->fragmentShader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	program = CreateProgram(App->program->vertexShader, App->program->fragmentShader);

	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	LOG("Destroying render exercise");
	glDeleteBuffers(1, &vbo);

	return true;
}

