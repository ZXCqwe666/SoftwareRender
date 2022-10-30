#pragma once

#include "math_data.h"

class SoftRender
{
public:
	static void Init();
	static void Render();
	static void DrawLine(const vec3& start, const vec3& end);
};
