#include "SoftCamera.h"
#include "Config.h"

#include <corecrt_math.h>

float SoftCamera::zNear;
float SoftCamera::zFar;
float SoftCamera::fov;
mat4x4 SoftCamera::proj;

void SoftCamera::Init(float _zNear, float _zFar, float _fov)
{
	zNear = _zNear;
	zFar = _zFar;
	fov = _fov;

	float aspectRatio = (float)RES_X / (float)RES_Y;
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	proj.m[0][0] = aspectRatio * fovRad;
	proj.m[1][1] = fovRad;
	proj.m[2][2] = zFar / (zFar - zNear);
	proj.m[3][2] = (-zFar * zNear) / (zFar - zNear);
	proj.m[2][3] = 1.0f;
	proj.m[3][3] = 0.0f;
}
