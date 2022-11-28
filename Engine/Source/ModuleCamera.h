#ifndef __ModuleCamera_H__
#define __ModuleCamera_H__

#include "Module.h"
#include "SDL/include/SDL.h"
#include "../Source/MathGeoLib/Geometry/Frustum.h"

class Application;

class ModuleCamera : public Module
{
public:

	ModuleCamera();
	virtual ~ModuleCamera();
	bool Init();
	update_status Update();
	bool CleanUp();
	//void drawAxis();

	void SetAspectRatio(float h, float w);
	void SetDistance(float nearPlane, float farPlane);
	void SetKind(FrustumProjectiveSpace projectiveSpace, FrustumHandedness handedness);
	void SetPerspective(float height, float width);
	void SetPos(math::vec pos);
	void SetFront(math::vec front);
	void SetUp(math::vec up);
	float4x4 ViewMatrix();
	float4x4 ProjectionMatrix();

	float posX = 0.0f, posY = 1.0f, posZ = 8.0f;
	float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;
	float speed = 3.0f;

private:
	Frustum frustum;
};

#endif // __ModuleCamera_H__