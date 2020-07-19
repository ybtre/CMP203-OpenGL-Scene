#pragma once

#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include "Vector3.h"

class Shadow {
public:
	static void generateShadowMatrix(float* shadowMatrix, float light_pos[4], GLfloat floor[12]);
	static void extendVertex(float newVert[3], float lightPosit[4], float x, float y, float z, float ext);
	static std::vector<float> buildShadowVolume(float lightPosit[4], std::vector<float> verts);
};