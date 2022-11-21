#include "SoftRender.h"

#include "ScreenBuffer.h"
#include "SoftCamera.h"
#include "math_data.h"
#include "Time.h"

const uint32_t line_color = (150 << 24) | (150 << 16) | (150 << 8) | 255;
const vec3 SoftRender::startPosition = { -2.5, -1.5, 6 };
const vec3 SoftRender::startScale = { 1, 1, 1 };

mesh SoftRender::model;

vec3 SoftRender::meshPosition = startPosition;
vec3 SoftRender::meshScale = startScale;

bool SoftRender::moveInSpace;
bool SoftRender::mirrorX, SoftRender::mirrorY, SoftRender::mirrorZ;
bool SoftRender::rotateX, SoftRender::rotateY, SoftRender::rotateZ;
bool SoftRender::setRotationX, SoftRender::setRotationY, SoftRender::setRotationZ;
float SoftRender::angleX, SoftRender::angleY, SoftRender::angleZ;
mat4x4 SoftRender::mat_rotX, SoftRender::mat_rotY, SoftRender::mat_rotZ;

void SoftRender::Init()
{
	SoftCamera::Init(0.1f, 100.0f, 60.0f);
	LoadMesh();
}

void SoftRender::UpdateRotMat()
{
	float time = Time::GetTime();

	float x_angle = setRotationX ? angleX : rotateX ? time : 0;

	mat_rotX.m[0][0] = 1;
	mat_rotX.m[1][1] = cosf(x_angle);
	mat_rotX.m[1][2] = sinf(x_angle);
	mat_rotX.m[2][1] = -sinf(x_angle);
	mat_rotX.m[2][2] = cosf(x_angle);
	mat_rotX.m[3][3] = 1;

	float y_angle = setRotationY ? angleY : rotateY ? time : 0;

	mat_rotY.m[0][0] = cosf(y_angle);
	mat_rotY.m[1][1] = 1;
	mat_rotY.m[0][2] = sinf(y_angle);
	mat_rotY.m[2][0] = -sinf(y_angle);
	mat_rotY.m[2][2] = cosf(y_angle);
	mat_rotY.m[3][3] = 1;

	float z_angle = setRotationZ ? angleZ : rotateZ ? time : 0;

	mat_rotZ.m[0][0] = cosf(z_angle);
	mat_rotZ.m[0][1] = sinf(z_angle);
	mat_rotZ.m[1][0] = -sinf(z_angle);
	mat_rotZ.m[1][1] = cosf(z_angle);
	mat_rotZ.m[2][2] = 1;
	mat_rotZ.m[3][3] = 1;
}

void SoftRender::Render()
{
	ScreenBuffer::Clear();

	UpdateRotMat();

	vec3 mirror = {mirrorX ? -1 : 1, mirrorY ? -1 : 1, mirrorZ ? -1 : 1};
	const vec3 _res = { 0.5f * (float)RES_X, 0.5f * (float)RES_Y, 1.0f };
	const vec3 _110 = { 1.0f, 1.0f, 0.0f };

	for (int i = 0; i < model.triangles.size(); i++)
	{
		triangle triProjected = model.triangles[i];

		for (int i = 0; i < 3; i++)
		{
			triProjected.p[i] *= meshScale;
			triProjected.p[i] *= mat_rotX;
			triProjected.p[i] *= mat_rotY;
			triProjected.p[i] *= mat_rotZ;
			triProjected.p[i] += meshPosition;

			triProjected.p[i] = SoftCamera::Project(triProjected.p[i]);

			if (moveInSpace)
			{
				float time = Time::GetTime();
				triProjected.p[i].x += 2 * sin(time) / 4;
				triProjected.p[i].y += cos(time) / 4;
			}

			triProjected.p[i] *= mirror;
			triProjected.p[i] += _110;
			triProjected.p[i] *= _res;
		}

		DrawLineSimple(triProjected.p[0], triProjected.p[1]);
		DrawLineSimple(triProjected.p[1], triProjected.p[2]);
		DrawLineSimple(triProjected.p[2], triProjected.p[0]);
	}

	ScreenBuffer::Update_ScreenTexture();
}

void SoftRender::DrawLineSimple(const vec3& start, const vec3& end)
{
	const int maxIter = RES_X * 10;
	int iter = 0;

	float maxDistance = start.distance2D(end);
	float distance = 0.0f;

	vec3 rayDir = end;
	rayDir -= start;
	rayDir.normalize();

	vec3 position = start;

	while (iter < maxIter && distance < maxDistance)
	{
		uint32_t coordX = uint32_t(position.x);
		uint32_t coordY = uint32_t(position.y);

		if (coordX >= 0 && coordX < RES_X && coordY >= 0 && coordY < RES_Y)
		{
			ScreenBuffer::SetPixel(coordX, coordY, line_color);
		}

		position += rayDir;
		distance++;
	}	
}

bool SoftRender::AnyTrisOutOfBounds()
{
	for (int i = 0; i < model.triangles.size(); i++)
	{
		triangle triProjected = model.triangles[i];

		for (int i = 0; i < 3; i++)
		{
			triProjected.p[i] *= meshScale;
			triProjected.p[i] *= mat_rotX;
			triProjected.p[i] *= mat_rotY;
			triProjected.p[i] *= mat_rotZ;
			triProjected.p[i] += meshPosition;
			triProjected.p[i] *= SoftCamera::proj;

			if (triProjected.p[i].x < -1.0f || triProjected.p[i].x > 1.0f 
			 || triProjected.p[i].y < -1.0f || triProjected.p[i].y > 1.0f)
			{
				return true;
			}
		}
	}

	return false;
}

void SoftRender::ResetScene()
{
	meshPosition = startPosition;
	meshScale = startScale;

	rotateX = false;
	rotateY = false;
	rotateZ = false;
	setRotationX = false;
	setRotationY = false;
	setRotationZ = false;
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}

#include <iostream>
#include <fstream>

void SoftRender::LoadMesh()
{
	float data[900] = { 0 };

	int n = 0;
	std::ifstream inFile;
	inFile.open("Resources/Mesh/model.txt");

	if (inFile.fail())
	{
		std::cout << "No such file" << std::endl;
		return;
	}

	inFile >> data[n];

	while (!inFile.eof() && n < 1000)
	{
		n++;
		inFile >> data[n];
	}
	inFile.close();

	int tri_count = n / 9;

	for (int i = 0; i < tri_count; i++)
	{
		int offset = i * 9;

		triangle tri = { 0 };
		tri.p[0] = { data[offset + 0],data[offset + 1], data[offset + 2] };
		tri.p[1] = { data[offset + 3],data[offset + 4], data[offset + 5] };
		tri.p[2] = { data[offset + 6],data[offset + 7], data[offset + 8] };

		model.triangles.push_back(tri);
	}
}
