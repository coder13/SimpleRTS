#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../util/Vec3f.h"
#include "Chunk.h"
// #include "../util/simplexnoise.h"

const Vec3f TILES[6] = {
Vec3f(0.0f, 0.0f, 0.0f), Vec3f(1.0f, 1.0f, 1.0f), Vec3f(0.5f, 0.5f, 0.5f), 
Vec3f(1.0f, 0.0f, 0.0f), Vec3f(0.0f, 1.0f, 0.0f), Vec3f(0.0f, 0.0f, 1.0f)};

//comment 
Chunk::Chunk(int x, int y) {
	X = x;
	Y = y;
}

void Chunk::gen() {

	for (int i = 0; i < CHUNK_SIZE * CHUNK_SIZE; i++) {
		int x = i % CHUNK_SIZE, 
			y = i / CHUNK_SIZE;
		int rx = x + X*CHUNK_SIZE,
			ry = y + Y*CHUNK_SIZE;

		// if (raw_noise_2d((float)rx, (float)ry) < .5) {
		if (rx*rx + ry*ry < 64) {
			map[i] = 1;
		} else {
			map[i] = 2;
		}

		if (x + X*CHUNK_SIZE == 0 && y + Y * CHUNK_SIZE == 0) {
			map[i] = 3;
		}
	}
}

int Chunk::getId(int x, int y) {
	return map[y * CHUNK_SIZE + x];
}

bool Chunk::setId(int x, int y, int id) {
	if (x < 0 || y < 0 || x >= CHUNK_SIZE || y >= CHUNK_SIZE)
		return false;
	map[y * CHUNK_SIZE + x] = id;
	return true;
}


void Chunk::draw() {
	if (!list) {
		// Generate 1 display list
		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		    // Enter your vertices here
		    glBegin(GL_QUADS);
		    	for (int i = 0; i < CHUNK_SIZE*CHUNK_SIZE; i++) {
			        int x = i % CHUNK_SIZE, y = i / CHUNK_SIZE;

			        // Vec3f color = TILES[map[i]];
			        // glColor3f(color.x, color.y, color.z);
			        
			        glColor3f(.0f,1.0f,1.0f);
			        glVertex3f(x     , y     , 0.0f);
			        glVertex3f(x     , y+1.0f, 0.0f);
			        glVertex3f(x+1.0f, y+1.0f, 0.0f);
			        glVertex3f(x+1.0f, y     , 0.0f);
		    	}
			glEnd();
		glEndList();
		// Then later, elsewhere in your code,
		// Call the display list to render it
	}

	glPushMatrix();

	glTranslated(X * CHUNK_SIZE, Y * CHUNK_SIZE, 0);

	glCallList(list);

	glPopMatrix();
}