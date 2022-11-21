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

	float aspectRatio = (float)RES_Y / (float)RES_X;
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	proj.m[0][0] = aspectRatio * fovRad;
	proj.m[1][1] = fovRad;
	proj.m[2][2] = zFar / (zFar - zNear);
	proj.m[3][2] = (-zFar * zNear) / (zFar - zNear);
	proj.m[2][3] = 1.0f;
	proj.m[3][3] = 0.0f;
}

vec3 SoftCamera::Project(const vec3& point)
{	
	vec3 result = {0, 0, 0};

	//соотношение сторон екрана (например 1920 / 1080)
	float aspectRatio = (float)RES_Y / (float)RES_X;
	// 1 / tan(Q/2)   Q - угол обзора   Перевод в радианы: / 180.0f * 3.14159f  
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	result.x = point.x * aspectRatio * fovRad;
	result.y = point.y * fovRad;
	result.z = point.z / (zFar - zNear);

	if (point.z != 0)
	{
		result.x /= point.z;
		result.y /= point.z;
	}

	return result;
}
