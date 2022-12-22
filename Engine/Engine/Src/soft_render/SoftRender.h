#pragma once

#include "math_data.h"

class SoftRender
{
public:
	static mesh model;

	static const vec3 startPosition;
	static const vec3 startScale;

	static vec3 meshPosition;
	static vec3 meshScale;

	static bool mirrorX;
	static bool mirrorY;
	static bool mirrorZ;

	static bool rotateX, rotateY, rotateZ;
	static bool setRotationX, setRotationY, setRotationZ;
	static bool moveInSpace;
	static float angleX, angleY, angleZ;

private:
	static mat4x4 mat_rotX, mat_rotY, mat_rotZ;

private:
	static void LoadMesh();
	static void UpdateRotMat();
	static void DrawLineSimple(const vec3& start, const vec3& end);

public:
	static void Init();
	static void Render();
	static void ResetScene();
};
