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
	bool Start();
	update_status Update();
	bool CleanUp();

	void SetAspectRatio(float h, float w);
	void SetDistance(float nearPlane, float farPlane);
	void SetKind(FrustumProjectiveSpace projectiveSpace, FrustumHandedness handedness);
	void SetPerspective(float height, float width);
	void SetPos(math::vec pos);
	void SetFront(math::vec front);
	void SetUp(math::vec up);
	void Rotate(const float3x3& rotationMatrix);
	void Move(const float3& direction);
	void Zoom(const float3& direction, int wheel);
	float3 GetPos();
	float4x4 ViewMatrix();
	float4x4 ProjectionMatrix();
	void LookAt(const float3& lookAt);

	float movementSpeed = 10.0f;
	float rotationSpeed = 50.0f;
	float zoomSpeed = 14.0f;

private:
	void drawAxis();

	float posX = 0.0f, posY = 1.0f, posZ = 8.0f;
	Frustum frustum;
};

#endif // __ModuleCamera_H__