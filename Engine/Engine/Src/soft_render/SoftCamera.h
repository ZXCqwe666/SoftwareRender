#pragma once

#include "math_data.h"

class SoftCamera
{
public:
	static float zNear;
	static float zFar;
	static float fov;
	static mat4x4 proj;

public:
	static void Init(float _zNear, float _zFar, float _fov);
};
