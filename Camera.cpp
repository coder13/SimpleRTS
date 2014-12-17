#include "Camera.h"

Camera::Camera() {
	posX = 0;
	posY = 0;
}

Camera::Camera(float posx, float posy) {
	posX = posx;
	posY = posy;
}

void Camera::adjust(float width, float height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-width/2, width/2, height/2, -height/2, -2, 2);
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::use() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(matrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Camera::apply() {
	glTranslated(-posX, posY, 0);
}
