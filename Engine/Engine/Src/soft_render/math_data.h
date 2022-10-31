#pragma once

struct mat4x4
{
	float m[4][4] = { 0 };
};

struct vec3
{
	float x, y, z;

	void operator += (const vec3& other);
	void operator -= (const vec3& other);
	void operator *= (const vec3& other);
	void operator /= (const vec3& other);
	void operator *= (const mat4x4& mat);

	float distance2D(const vec3& other) const;
	void normalize();
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
