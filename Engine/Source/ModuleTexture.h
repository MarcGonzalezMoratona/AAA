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
	virtual ~ModuleTexture();
	bool Init();
	update_status Update();
	bool CleanUp();

	ScratchImage LoadTexture(const wchar_t* path, TexMetadata* metadata, ScratchImage& srcImg);
	void LoadMetadata(TexMetadata metadata, GLint& internalFormat, GLint& format, GLint& type);
	unsigned Load(const wchar_t* path);

private:

};

#endif // __ModuleTexture_H__