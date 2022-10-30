#pragma once

struct vec3
{
	float x, y, z;

	void operator += (const vec3& other);
	void operator -= (const vec3& other);
	void operator *= (const vec3& other);
	void operator /= (const vec3& other);
};

struct mat4x4
{
	float m[4][4] = { 0 };

	vec3 operator * (const vec3& other);
};

struct triangle
{
	vec3 p[3];
};

#include <vector>

struct mesh
{
	std::vector<triangle> triangles;
};
