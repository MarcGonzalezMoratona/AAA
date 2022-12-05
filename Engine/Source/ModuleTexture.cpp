#include "ModuleTexture.h"

ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

void ModuleTexture::LoadMetadata(TexMetadata metadata, GLint& internalFormat, GLint& format, GLint& type) {
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}
}

unsigned ModuleTexture::Load(const wchar_t* path) {
	return 0;
}

ScratchImage ModuleTexture::LoadTexture(const wchar_t* path, TexMetadata* metadata, ScratchImage& srcImg) {
	HRESULT result = LoadFromDDSFile(path, DDS_FLAGS_NONE, metadata, srcImg);
	if (FAILED(result)) result = LoadFromTGAFile(path, TGA_FLAGS_NONE, metadata, srcImg);
	if (FAILED(result)) LoadFromWICFile(path, WIC_FLAGS_NONE, metadata, srcImg);
	ScratchImage img;
	FlipRotate(srcImg.GetImages(), srcImg.GetImageCount(), srcImg.GetMetadata(), TEX_FR_FLIP_VERTICAL, img);
	return img;
}

// Called before render is available
bool ModuleTexture::Init()
{
	return true;
}

// Called every draw update
update_status ModuleTexture::Update()
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleTexture::CleanUp()
{
	DEBUGLOG("Destroying ModuleTexture");
	return true;
}

