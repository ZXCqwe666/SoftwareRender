#include "SoftRender.h"

#include "ScreenBuffer.h"
#include "SoftCamera.h"
#include "math_data.h"
#include "Time.h"
#include <algorithm>

uint32_t line_color = (150 << 24) | (150 << 16) | (150 << 8) | 255;
const vec3 SoftRender::startPosition = { -2.0, -2.0, 11 };
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

	std::vector<triangle> tris;

	for (int i = 0; i < model.triangles.size(); i++)
	{
		triangle world_space_tri = model.triangles[i];

		for (int i = 0; i < 3; i++)
		{
			world_space_tri.p[i] *= meshScale;
			world_space_tri.p[i] *= mat_rotX;
			world_space_tri.p[i] *= mat_rotY;
			world_space_tri.p[i] *= mat_rotZ;
			world_space_tri.p[i] += meshPosition;
		}

		tris.push_back(world_space_tri);
	}

	std::sort(tris.begin(), tris.end(), [](triangle& t1_w, triangle& t2_w)
	{
		triangle t1{};
		t1.p[0] = SoftCamera::Project(t1_w.p[0]);
		t1.p[1] = SoftCamera::Project(t1_w.p[1]);
		t1.p[2] = SoftCamera::Project(t1_w.p[2]);

		triangle t2{};
		t2.p[0] = SoftCamera::Project(t2_w.p[0]);
		t2.p[1] = SoftCamera::Project(t2_w.p[1]);
		t2.p[2] = SoftCamera::Project(t2_w.p[2]);

		float average_z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
		float average_z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
		return average_z1 > average_z2;
	});

	vec3 mirror = {mirrorX ? -1 : 1, mirrorY ? -1 : 1, 1};
	const vec3 _res = { 0.5f * (float)RES_X, 0.5f * (float)RES_Y, 1.0f };
	const vec3 _110 = { 1.0f, 1.0f, 0.0f };

	for (int i = 0; i < tris.size(); i++)
	{
		triangle triProj = tris[i];
		triangle world_space_tri = tris[i];

		for (int i = 0; i < 3; i++)
		{
			triProj.p[i] = SoftCamera::Project(triProj.p[i]);

			if (moveInSpace)
			{
				float time = Time::GetTime();
				triProj.p[i].x += 2 * sin(time) / 4;
				triProj.p[i].y += cos(time) / 4;
			}

			triProj.p[i] *= mirror;
			triProj.p[i] += _110;
			triProj.p[i] *= _res;
		}

		//calculate normal vector of a triangle
		vec3 A = world_space_tri.p[1];
		A -= world_space_tri.p[0];
		vec3 B = world_space_tri.p[2];
		B -= world_space_tri.p[0];

		//cross product (vector perpendicular to triangle plane)
		vec3 normal
		{
			A.y * B.z - A.z * B.y,
			A.z * B.x - A.x * B.z,
			A.x * B.y - A.y * B.x,
		};

		normal.normalize();

		//dot product
		vec3 light_dir = {0, 0, -1.0};
		float illumination = normal.x * light_dir.x + normal.y * light_dir.y + normal.z * light_dir.z;

		//face color
		if (illumination > 1) illumination = 1;
		if (illumination < 0) illumination = 0;
		int color  = int(illumination * 255);
		line_color = (color << 24) | (color << 16) | (color << 8) | 255;

		//draw pixels
		DrawLineSimple(triProj.p[0], triProj.p[1]);
		DrawLineSimple(triProj.p[1], triProj.p[2]);
		DrawLineSimple(triProj.p[2], triProj.p[0]);
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

	std::ifstream inFile;
	inFile.open("Resources/Mesh/model.txt");

	if (inFile.fail())
	{
		std::cout << "No such file" << std::endl;
		return;
	}

	int n = 0;

	while (!inFile.eof() && n < 1000)
	{
		inFile >> data[n + 0];
		inFile >> data[n + 1];
		inFile >> data[n + 2];

		inFile >> data[n + 3];
		inFile >> data[n + 4];
		inFile >> data[n + 5];

		inFile >> data[n + 6];
		inFile >> data[n + 7];
		inFile >> data[n + 8];

		n += 9;
	}
	inFile.close();

	int tri_count = n / 9;

	for (int i = 0; i < tri_count; i++)
	{
		int offset = i * 9;

		triangle tri = { 0 };
		tri.p[0] = { data[offset + 0], data[offset + 1], data[offset + 2] };
		tri.p[1] = { data[offset + 3], data[offset + 4], data[offset + 5] };
		tri.p[2] = { data[offset + 6], data[offset + 7], data[offset + 8] };

		model.triangles.push_back(tri);
	}
}
