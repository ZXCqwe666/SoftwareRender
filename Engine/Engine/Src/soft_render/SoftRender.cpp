#include "SoftRender.h"

#include "ScreenBuffer.h"
#include "SoftCamera.h"
#include "math_data.h"

const uint32_t line_color = (128 << 24) | (128 << 16) | (128 << 8) | 255;
const uint32_t point_color = (200 << 24) | (200 << 16) | (200 << 8) | 255;

vec3 SoftRender::meshPosition = { 0, 0, 2};
vec3 SoftRender::meshScale = { 1, 1, 1 };
bool SoftRender::mirrorX;
bool SoftRender::mirrorY;
bool SoftRender::mirrorZ;

void SoftRender::Init()
{
	SoftCamera::Init(0.1f, 500.0f, 60.0f);
}

void SoftRender::Render()
{
	ScreenBuffer::Clear();

	mesh cubeMesh;
	cubeMesh.triangles = 
	{
		// SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
	};

	for (int i = 0; i < cubeMesh.triangles.size(); i++)
	{
		triangle triProjected = cubeMesh.triangles[i];
		
		//scale 
		triProjected.p[0] *= meshScale;
		triProjected.p[1] *= meshScale;
		triProjected.p[2] *= meshScale;

		//translate
		triProjected.p[0] += meshPosition;
		triProjected.p[1] += meshPosition;
		triProjected.p[2] += meshPosition;

		//project
		triProjected.p[0] *= SoftCamera::proj;
		triProjected.p[1] *= SoftCamera::proj;
		triProjected.p[2] *= SoftCamera::proj;

		//mirror on axis
		vec3 mirror = {mirrorX ? -1 : 1, mirrorY ? -1 : 1, mirrorZ ? -1 : 1};
		triProjected.p[0] *= mirror;
		triProjected.p[1] *= mirror;
		triProjected.p[2] *= mirror;

		//scale into view
		const vec3 _110 = {1.0f, 1.0f, 0.0f};
		const vec3 _res = {0.5f * (float)RES_X, 0.5f * (float)RES_Y, 1.0f};
		triProjected.p[0] += _110;
		triProjected.p[1] += _110;
		triProjected.p[2] += _110;
		triProjected.p[0] *= _res;
		triProjected.p[1] *= _res;
		triProjected.p[2] *= _res;

		//draw
		DrawLine(triProjected.p[0], triProjected.p[1]);
		DrawLine(triProjected.p[1], triProjected.p[2]);
		DrawLine(triProjected.p[2], triProjected.p[0]);
	}

	ScreenBuffer::Update_ScreenTexture();
}

void SoftRender::DrawLine(const vec3& start, const vec3& end)
{
	vec3 startPos = start;
	vec3 rayDir = end;
	rayDir -= start;
	rayDir.normalize();

	vec3 rayUnitStepSize = 
	{ 
		sqrt(1 + (rayDir.y / rayDir.x) * (rayDir.y / rayDir.x)),
		sqrt(1 + (rayDir.x / rayDir.y) * (rayDir.x / rayDir.y))
	};

	vec3 checkPos = startPos;
	vec3 rayLen1D = { 0 };
	vec3 step = { 0 };

	if (rayDir.x < 0)
	{
		step.x = -1;
		rayLen1D.x = (startPos.x - float(checkPos.x)) * rayUnitStepSize.x;
	}
	else
	{
		step.x = 1;
		rayLen1D.x = (float(checkPos.x + 1) - startPos.x) * rayUnitStepSize.x;
	}

	if (rayDir.y < 0)
	{
		step.y = -1;
		rayLen1D.y = (startPos.y - float(checkPos.y)) * rayUnitStepSize.y;
	}
	else
	{
		step.y = 1;
		rayLen1D.y = (float(checkPos.y + 1) - startPos.y) * rayUnitStepSize.y;
	}

	float maxDistance = start.distance2D(end);
	float distance = 0.0f;
	int maxIter = RES_X * 10;
	int iter = 0;

	while (iter < maxIter && distance < maxDistance)
	{
		if (rayLen1D.x < rayLen1D.y)
		{
			checkPos.x += step.x;
			distance = rayLen1D.x;
			rayLen1D.x += rayUnitStepSize.x;
		}
		else
		{
			checkPos.y += step.y;
			distance = rayLen1D.y;
			rayLen1D.y += rayUnitStepSize.y;
		}

		if (checkPos.x >= 0 && checkPos.x < RES_X && checkPos.y >= 0 && checkPos.y < RES_Y)
		{
			ScreenBuffer::SetPixel((uint32_t)checkPos.x, (uint32_t)checkPos.y, line_color);
		}

		iter++;
	}

	if ((uint32_t)start.x >= 0 && (uint32_t)start.x < RES_X && (uint32_t)start.y >= 0 && (uint32_t)start.y < RES_Y)
	{
		ScreenBuffer::SetPixel((uint32_t)start.x, (uint32_t)start.y, point_color);
	}
}
