#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#include "Entity.h"

#define PI 3.1415926

Entity::Entity() {
	list = -1;
	targetReached = false;
}

Entity::Entity(Vec3f pos) {
	_pos = pos;
	list = -1;
	targetReached = false;
}

void Entity::tick() {
	if (_pos != target && !targetReached) {
		Vec3f delta = target - _pos;
		if (delta.length() > .25f)
			_pos += delta.normalize()/10;
		else {
			targetReached = true;
		}
	}	
}

void Entity::setTarget(Vec3f t) {
	target = t;
	
}

bool reachedTarget() {
	return targetReached;
}

void Entity::draw() {
	if (list == -1) {
		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		    glBegin(GL_TRIANGLE_FAN);
			    glColor3f(1.0f, 1.0f, 0.0f);
			    // glVertex3f(0.0f, 0.0f, 0.2f);
			    for (int i = 0; i < 36; i++) {
			    	glVertex3f(cos(i*10*(PI/180))/2, sin(i*10*(PI/180))/2, 0.2f);
			    }
		    glEnd();
		glEndList();
	}
	glPushMatrix();

		glTranslated(_pos.x, _pos.y, _pos.z);
		glCallList(list);

	glPopMatrix();
}