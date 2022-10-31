#include "math_data.h"

void vec3::operator+=(const vec3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

void vec3::operator-=(const vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

void vec3::operator*=(const vec3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
}

void vec3::operator/=(const vec3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
}

void vec3::operator*=(const mat4x4& mat)
{
	vec3 result = { 0 };

	result.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + mat.m[3][0];
	result.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + mat.m[3][1];
	result.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + mat.m[3][2];
	float  w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + mat.m[3][3];

	if (w != 0.0f)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	x = result.x;
	y = result.y;
	z = result.z;
}

void vec3::normalize()
{
	float length = sqrt((x * x) + (y * y) + (z * z));
	float mag = length >= 0 ? length : -length;

	x /= mag;
	y /= mag;
	z /= mag;
}

float vec3::distance2D(const vec3& other) const
{
	return sqrt(powf(x - other.x, 2.0f) + powf(y - other.y, 2.0f));
}
