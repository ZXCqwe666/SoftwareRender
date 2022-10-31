#include "SoftRender.h"

#include "ScreenBuffer.h"
#include "SoftCamera.h"
#include "math_data.h"

vec3 SoftRender::meshPosition = { 0, 0, 2};

void SoftRender::Init()
{
	SoftCamera::Init(0.1f, 1000.0f, 90.0f);
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
		
		//translate
		triProjected.p[0] += meshPosition;
		triProjected.p[1] += meshPosition;
		triProjected.p[2] += meshPosition;

		//project
		triProjected.p[0] = SoftCamera::proj * triProjected.p[0];
		triProjected.p[1] = SoftCamera::proj * triProjected.p[1];
		triProjected.p[2] = SoftCamera::proj * triProjected.p[2];

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

	//for (int x = 0; x < RES_X; x++)
	//{
	//	for (int y = 0; y < RES_Y; y++)
	//	{	
	//		if ((x + y) % 2 == 0)
	//		{
	//			int32_t color = (255 << 24) | (32 << 16) | (54 << 8) | 255;
	//			ScreenBuffer::SetPixel(x, y, color);
	//		}
	//		else 
	//		{
	//			int32_t color = (4 << 24) | (74 << 16) | (12 << 8) | 255;
	//			ScreenBuffer::SetPixel(x, y, color);
	//		}
	//	}
	//}

	ScreenBuffer::Update_ScreenTexture();
}

void SoftRender::DrawLine(const vec3& start, const vec3& end)
{
	const uint32_t line_color = (128 << 24) | (128 << 16) | (128 << 8) | 255;
	const uint32_t point_color = (200 << 24) | (200 << 16) | (200 << 8) | 255;

	float dx = abs(end.x - start.x);
	float dy = abs(end.y - start.y);
	float step = 0;

	if (dx >= dy) step = dx;
	else step = dy;

	dx /= step;
	dy /= step;

	float x = start.x;
	float y = start.y;

	int i = 0;

	while (i < step)
	{
		if ((uint32_t)x >= 0 && (uint32_t)x < RES_X && (uint32_t)y >= 0 && (uint32_t)y < RES_Y)
		{
			ScreenBuffer::SetPixel((uint32_t)x, (uint32_t)y, line_color);
		}

		x += dx;
		y += dy;
		i++;
	}

	uint32_t start_x = (uint32_t)start.x;
	uint32_t start_y = (uint32_t)start.y;
	uint32_t end_x = (uint32_t)end.x;
	uint32_t end_y = (uint32_t)end.y;

	if (start_x >= 0 && start_x < RES_X && start_y >= 0 && start_y < RES_Y)
	{
		ScreenBuffer::SetPixel(start_x, start_y, point_color);
	}
}
