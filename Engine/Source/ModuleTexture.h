#ifndef __ModuleTexture_H__
#define __ModuleTexture_H__

#include "Module.h"
#include "DirectXTex.h"
#include "SDL/include/SDL.h"
#include <GL/glew.h>

using namespace DirectX;

class ModuleTexture : public Module
{
public:

	ModuleTexture();
	~ModuleTexture();

	bool Init() override;
	update_status Update() override;
	bool CleanUp() override;

	ScratchImage LoadTexture(const wchar_t* path, TexMetadata* metadata, ScratchImage& srcImg);
	void LoadMetadata(TexMetadata metadata, GLint& internalFormat, GLint& format, GLint& type);
	unsigned Load(const char* textureName);

private:
	unsigned tbo = 0;
};

#endif // __ModuleTexture_H__