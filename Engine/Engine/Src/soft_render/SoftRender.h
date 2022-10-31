#pragma once

#include "math_data.h"

class SoftRender
{
public:
	static vec3 meshPosition;
	static vec3 meshScale;

	static bool mirrorX;
	static bool mirrorY;
	static bool mirrorZ;

	static void Init();
	static void Render();
	static void DrawLine(const vec3& start, const vec3& end);
};
