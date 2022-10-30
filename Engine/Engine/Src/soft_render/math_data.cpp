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

vec3 mat4x4::operator*(const vec3& input)
{
	vec3 result = { 0 };

	result.x = input.x * m[0][0] + input.y * m[1][0] + input.z * m[2][0] + m[3][0];
	result.y = input.x * m[0][1] + input.y * m[1][1] + input.z * m[2][1] + m[3][1];
	result.z = input.x * m[0][2] + input.y * m[1][2] + input.z * m[2][2] + m[3][2];
	float  w = input.x * m[0][3] + input.y * m[1][3] + input.z * m[2][3] + m[3][3];

	if (w != 0.0f)
	{
		result.x /= w; 
		result.y /= w; 
		result.z /= w;
	}

	return result;
}
