#include "SoftRender.h"

#include "ScreenBuffer.h"
#include "SoftCamera.h"
#include "math_data.h"

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
		triangle tri = cubeMesh.triangles[i];
		
		//translate
		vec3 meshPosition = {2, 0, 5};
		tri.p[0] += meshPosition;
		tri.p[1] += meshPosition;
		tri.p[2] += meshPosition;

		//project
		triangle triProjected = { 0 };
		triProjected.p[0] = SoftCamera::proj * tri.p[0];
		triProjected.p[1] = SoftCamera::proj * tri.p[1];
		triProjected.p[2] = SoftCamera::proj * tri.p[2];

		//scale
		//vec3 scale = {100, 100, 100};
		//tri.p[0] += scale;
		//tri.p[1] += scale;
		//tri.p[2] += scale;

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
	uint32_t start_x = (uint32_t)start.x;
	uint32_t start_y = (uint32_t)start.y;
	uint32_t line_color = (128 << 24) | (128 << 16) | (128 << 8) | 255;

	if (start_x >= 0 && start_x < RES_X && start_y >= 0 && start_y < RES_Y)
	{
		ScreenBuffer::SetPixel(start_x, start_y, line_color);
	}
}
