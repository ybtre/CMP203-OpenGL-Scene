
#define CAMERASPEED	0.03f		// The Camera Speed

struct vvector3	// 3D Vector Struct
{
	vvector3() {} // Struct Constructor
	vvector3(float new_x, float new_y, float new_z) { // Init Constructor	 
		x = new_x;
		y = new_y;
		z = new_z;
	}

	// overload + operator
	vvector3 operator+(vvector3 vVector) {
		return vvector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}
	// overload - operator
	vvector3 operator-(vvector3 vVector) {
		return vvector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	// overload * operator
	vvector3 operator*(float number) {
		return vvector3(x * number, y * number, z * number);
	}
	// overload / operator
	vvector3 operator/(float number) {
		return vvector3(x / number, y / number, z / number);
	}

	float x, y, z;	// 3D vector coordinates
};


class CCamera {
public:

	vvector3 mPos;
	vvector3 mLookAt;
	vvector3 mUp;

	void strafeCamera(float speed);

	void mouseMove(int wndWidth, int wndHeight);
	void moveCamera(float speed);
	void rotateView(float speed);
	void positionCamera(float pos_x, float pos_y, float pos_z,
		float view_x, float view_y, float view_z,
		float up_x, float up_y, float up_z);
};