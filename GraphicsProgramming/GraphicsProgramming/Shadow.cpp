#include "Shadow.h"

// For planar shadows. Provide a float shadowmatrix[16] to fill, the light position and the coordinates the describe the floor/geometry to cast the shadow on.
void Shadow::generateShadowMatrix(float* shadowMatrix, float light_pos[4], GLfloat floor[12]) {

	//Defining vertices of plane are PQR with edges PQ and PR
	Vector3 P(floor[0], floor[1], floor[2]);	//top left
	Vector3 Q(floor[3], floor[4], floor[5]);	// bottom left
	Vector3 R(floor[9], floor[10], floor[11]);	// top right

	Vector3 PQ = (Q - P).normalised();
	Vector3 PR = (R - P).normalised();
	Vector3 normal = PR.cross(PQ);

	//Equation of plane is ax + by + cz = d
	//a, b and c are the coefficients of the normal to the plane (i.e. normal = ai + bj + ck)
	//If (x0, y0, z0) is any point on the plane, d = a*x0 + b*y0 + c*z0
	//i.e. d is the dot product of any point on the plane (using P here) and the normal to the plane
	float a, b, c, d;
	a = normal.getX();
	b = normal.getY();
	c = normal.getZ();
	d = normal.dot(P);

	//Origin of projection is at x, y, z. Projection here originating from the light source's position
	float x, y, z;
	x = light_pos[0];
	y = light_pos[1];
	z = light_pos[2];

	//This is the general perspective transformation matrix from a point (x, y, z) onto the plane ax + by + cz = d
	shadowMatrix[0] = d - (b * y + c * z);
	shadowMatrix[1] = a * y;
	shadowMatrix[2] = a * z;
	shadowMatrix[3] = a;

	shadowMatrix[4] = b * x;
	shadowMatrix[5] = d - (a * x + c * z);
	shadowMatrix[6] = b * z;
	shadowMatrix[7] = b;

	shadowMatrix[8] = c * x;
	shadowMatrix[9] = c * y;
	shadowMatrix[10] = d - (a * x + b * y);
	shadowMatrix[11] = c;

	shadowMatrix[12] = -d * x;
	shadowMatrix[13] = -d * y;
	shadowMatrix[14] = -d * z;
	shadowMatrix[15] = -(a * x + b * y + c * z);
}



// Builds and returns the shadow volume. Provide the light position and a float vector of the vertices of the shape casting the shadow.
// Will extend caster vertices to create shadow volume. Shadow volume is returned as a vertex array/vector for easy rendering.
std::vector<float> Shadow::buildShadowVolume(float lightPosit[4], std::vector<float> verts) {
	std::vector<float> shadowVolume;
	float extrusion = 5.f;

	// Clear previous shadow volume
	shadowVolume.clear();

	//Build new shadow volume

	// Temporary variable for storing newly calculated vertcies
	float vExtended[3];


	// For each vertex of the shadow casting object, find the edge 
	// that it helps define and extrude a quad out from that edge.
	for (int i = 0; i < verts.size(); i += 3) {
		// Define the edge we're currently working on extruding...
		int e0 = i;
		int e1 = i + 3;

		// If the edge's second vertex is out of array range, 
		// place it back at 0
		if (e1 >= verts.size()) {
			e1 = 0;
		}
		// v0 of our extruded quad will simply use the edge's first 
		// vertex or e0.
		shadowVolume.push_back(verts[e0]);
		shadowVolume.push_back(verts[e0 + 1]);
		shadowVolume.push_back(verts[e0 + 2]);

		// v1 of our quad is created by taking the edge's first 
		// vertex and extending it out by some amount.
		extendVertex(vExtended, lightPosit, verts[e0], verts[e0 + 1], verts[e0 + 2], extrusion);
		shadowVolume.push_back(vExtended[0]);
		shadowVolume.push_back(vExtended[1]);
		shadowVolume.push_back(vExtended[2]);

		// v2 of our quad is created by taking the edge's second 
		// vertex and extending it out by some amount.
		extendVertex(vExtended, lightPosit, verts[e1], verts[e1 + 1], verts[e1 + 2], extrusion);
		shadowVolume.push_back(vExtended[0]);
		shadowVolume.push_back(vExtended[1]);
		shadowVolume.push_back(vExtended[2]);

		// v3 of our extruded quad will simply use the edge's second 
		//// vertex or e1.
		shadowVolume.push_back(verts[e1]);
		shadowVolume.push_back(verts[e1 + 1]);
		shadowVolume.push_back(verts[e1 + 2]);
	}
	return shadowVolume;
}

// Part of the shadow volume calculation. Calculates an extended vertex value based on light position, original vertex and extrusion/extend value.
void Shadow::extendVertex(float newVert[3], float lightPosit[4], float x, float y, float z, float ext) {
	float lightDir[3];

	// Create a vector that points from the light's position to the original vertex.
	lightDir[0] = x - lightPosit[0];
	lightDir[1] = y - lightPosit[1];
	lightDir[2] = z - lightPosit[2];

	// Then use that vector to extend the original vertex out to a new position.
	// The distance to extend or extrude the new vector is specified by t.
	newVert[0] = lightPosit[0] + lightDir[0] * ext;
	newVert[1] = lightPosit[1] + lightDir[1] * ext;
	newVert[2] = lightPosit[2] + lightDir[2] * ext;
}

