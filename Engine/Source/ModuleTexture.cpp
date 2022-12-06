#include "Application.h"
#include "ModuleEditor.h"
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

unsigned ModuleTexture::Load(const char* textureName){
	ScratchImage srcImage;

	// Cast from const char * to wchar_t *
	const size_t size = strlen(textureName) + 1;
	wchar_t* texture_path = new wchar_t[size];
	mbstowcs(texture_path, textureName, size);

	// Load texture
	ScratchImage image = LoadTexture(texture_path, nullptr, srcImage);

	glGenTextures(1, &tbo);
	glBindTexture(GL_TEXTURE_2D, tbo);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Get texture metadata
	GLint internalFormat, format, type;
	TexMetadata metadata = image.GetMetadata();
	LoadMetadata(metadata, internalFormat, format, type);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, image.GetPixels());
	glGenerateMipmap(GL_TEXTURE_2D);

	return tbo;
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
	App->editor->AddLog("Destroying ModuleTexture");
	return true;
}

