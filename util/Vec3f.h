#pragma once

class Vec3f {
public:
	float x, y, z;
	Vec3f() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3f(float _x, float _y, float _z);

	void set(float _x, float _y, float _z);

	Vec3f operator+(Vec3f b);
	Vec3f operator-(Vec3f b);
	Vec3f operator*(Vec3f b);
	Vec3f operator/(Vec3f b);
	Vec3f operator+=(Vec3f b);
	Vec3f operator-=(Vec3f b);
	Vec3f operator*=(Vec3f b);
	Vec3f operator/=(Vec3f b);
	Vec3f operator+(float s);
	Vec3f operator-(float s);
	Vec3f operator*(float s);
	Vec3f operator/(float s);
	bool operator==(Vec3f b);
	bool operator!=(Vec3f b) {
		return !(Vec3f(x,y,z) == b);
	}

	float dot(Vec3f b);
	Vec3f cross(Vec3f b);
	float length();
	Vec3f normalize();
};