#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "DirectXTex.h"
#include <GL/glew.h>
#include <string>


ModuleTexture::ModuleTexture()
{
}

// Destructor
ModuleTexture::~ModuleTexture()
{
}

// Called before render is available
bool ModuleTexture::Init()
{

	DirectX::TexMetadata metadata;
	GLenum internalFormat, format, type;

	/*switch (metadata.format)
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
	}*/

	DirectX::ScratchImage img;
	//DirectX::Image srcImage;
	std::string path = "Textures/Baboon.ppm";
	std::wstring texture = std::wstring(path.begin(), path.end());
	HRESULT result = DirectX::LoadFromDDSFile(texture.c_str(), DirectX::DDS_FLAGS_NONE, &metadata, img);
	if(FAILED(result)) result = DirectX::LoadFromTGAFile(texture.c_str(), DirectX::TGA_FLAGS_NONE, &metadata, img);
	if(FAILED(result)) DirectX::LoadFromWICFile(texture.c_str(),DirectX::WIC_FLAGS_NONE,&metadata, img);
	//DirectX::FlipRotate(srcImage, DirectX::TEX_FR_FLIP_VERTICAL, img);
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

