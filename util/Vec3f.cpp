#include <math.h>

#include "Vec3f.h"

#define PI 3.14159

Vec3f::Vec3f(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Vec3f::set(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

// normal
Vec3f Vec3f::operator+(Vec3f b) { 
	return Vec3f(x + b.x, y + b.y, z + b.z);
}

Vec3f Vec3f::operator-(Vec3f b) { 
	return Vec3f(x - b.x, y - b.y, z - b.z);
}

Vec3f Vec3f::operator*(Vec3f b) { 
	return Vec3f(x * b.x, y * b.y, z * b.z);
}

Vec3f Vec3f::operator/(Vec3f b) { 
	return Vec3f(x / b.x, y / b.y, z / b.z);
}


Vec3f Vec3f::operator+=(Vec3f b) {
	x += b.x;
	y += b.y; 
	z += b.z;
	return Vec3f(x,y,z);
}

Vec3f Vec3f::operator-=(Vec3f b) {
	x -= b.x;
	y -= b.y; 
	z -= b.z;
	return Vec3f(x,y,z);
}

Vec3f Vec3f::operator*=(Vec3f b) {
	x *= b.x;
	y *= b.y; 
	z *= b.z;
	return Vec3f(x,y,z);
}

Vec3f Vec3f::operator/=(Vec3f b) {
	x /= b.x;
	y /= b.y; 
	z /= b.z;
	return Vec3f(x,y,z);
}

// scalard
Vec3f Vec3f::operator+(float s) { 
	return Vec3f(x + s, y + s, z + s);
}

Vec3f Vec3f::operator-(float s) { 
	return Vec3f(x - s, y - s, z - s);
}

Vec3f Vec3f::operator*(float s) { 
	return Vec3f(x * s, y * s, z * s);
}

Vec3f Vec3f::operator/(float s) { 
	return Vec3f(x / s, y / s, z / s);
}

bool Vec3f::operator==(Vec3f b) { 
	return x == b.x && y == b.y && z == b.z;
}

float Vec3f::dot(Vec3f b) {
	return x*b.x + y * b.y + z * b.z;
}

Vec3f Vec3f::cross(Vec3f b) {
	return Vec3f(y * b.z - z * b.y, 
				 z * b.x - x * b.z, 
				 x * b.y - y * b.x); 
}

float Vec3f::length() {
	return float(sqrt(x*x + y*y + z*z));
}

Vec3f Vec3f::normalize() {
	float length = this->length();
	return Vec3f(x/length, y/length, z/length);
}