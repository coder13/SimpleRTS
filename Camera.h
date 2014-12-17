#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Camera {
private: 
	GLfloat matrix[16];
public: 
	float posX, posY;
	Camera();
	Camera(float posx, float posy);
	void adjust(float width, float height);
	void use();
	void apply();

};