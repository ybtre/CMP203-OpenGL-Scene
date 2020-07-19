#include "Camera.h"

#include "glut.h"
#include <corecrt_math.h>

// CCamera positionCamera
void CCamera::positionCamera(float pos_x, float pos_y, float pos_z,
	float view_x, float view_y, float view_z,
	float up_x, float up_y, float up_z) {
	mPos = vvector3(pos_x, pos_y, pos_z); // set position
	mLookAt = vvector3(view_x, view_y, view_z); // set LookAt
	mUp = vvector3(up_x, up_y, up_z); // set the up vector	
}

//Ccamera Move Camera
void CCamera::moveCamera(float speed) {
	vvector3 vVector = mLookAt - mPos;	// Get the LookAt vector

	// forward positive cameraspeed and backward negative -cameraspeed.
	mPos.x = mPos.x + vVector.x * speed;
	mPos.z = mPos.z + vVector.z * speed;
	mLookAt.x = mLookAt.x + vVector.x * speed;
	mLookAt.z = mLookAt.z + vVector.z * speed;
}

//	CCamera Rotate View
void CCamera::rotateView(float speed) {
	vvector3 vector3 = mLookAt - mPos;	// Get the LookAt vector

	mLookAt.z = float(mPos.z + sin(speed) * vector3.x + cos(speed) * vector3.z);
	mLookAt.x = float(mPos.x + cos(speed) * vector3.x - sin(speed) * vector3.z);
}

// CCamera Strafe
void CCamera::strafeCamera(float speed) {
	vvector3 lookAtVector = mLookAt - mPos;	// Get the LookAt vector
	vvector3 orthoVector;					  // Orthogonal vector for the view vector

	orthoVector.x = -lookAtVector.z;
	orthoVector.z = lookAtVector.x;

	// left positive cameraspeed and right negative -cameraspeed.
	mPos.x = mPos.x + orthoVector.x * speed;
	mPos.z = mPos.z + orthoVector.z * speed;
	mLookAt.x = mLookAt.x + orthoVector.x * speed;
	mLookAt.z = mLookAt.z + orthoVector.z * speed;
}

// CCamera Mouse Move
void CCamera::mouseMove(int wndWidth, int wndHeight) {
	POINT mousePos;
	int mid_x = wndWidth >> 1;
	int mid_y = wndHeight >> 1;
	float angle_y = 0.0f;
	float angle_z = 0.0f;

	GetCursorPos(&mousePos);	// Get the 2D mouse cursor (x,y) position					

	if ((mousePos.x == mid_x) && (mousePos.y == mid_y)) return;

	SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the center of the window						

	// Get the direction from the mouse cursor, set a reasonable speed
	angle_y = float((mid_x - mousePos.x)) / 1000;
	angle_z = float((mid_y - mousePos.y)) / 1000;

	// The higher the value is the faster the camera looks around.
	mLookAt.y += angle_z * 3;

	// limit the rotation around the x-axis
	if ((mLookAt.y - mPos.y) > 8)  mLookAt.y = mPos.y + 8;
	if ((mLookAt.y - mPos.y) < -8)  mLookAt.y = mPos.y - 8;

	rotateView(-angle_y); // Rotate
}
