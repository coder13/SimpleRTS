#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>


#include "Camera.h"
#include "util/Vec3f.h"
#include "world/Chunk.h"
#include "Entity.h"

#define ESCAPE 27

using namespace std;

// window stuff
int window, scale = 16,
	Width, Height;

GLfloat gui[16];
Camera cam;
Vec3f selected;

// game stuff

bool keys[256], buttons[3];
float mouseX, mouseY;

Chunk* chunks[16];
Entity entity;

// GL stuff
GLuint selectedList;

void Resize(int width, int height) {
	if (width == 0 || height == 0)
		return;

	glViewport(0, 0, width, height);

	Width = width;
	Height = height;


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, Width, height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glGetFloatv(GL_PROJECTION_MATRIX, gui);

	cam.adjust(width/scale, height/scale);
	
}

void InitGL(int width, int height) {       
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);			
	glShadeModel(GL_SMOOTH);

	Resize(width, height);
}

void start() {
	buttons[0] = GLUT_UP;
	buttons[1] = GLUT_UP;
	buttons[2] = GLUT_UP;

	entity = Entity(Vec3f(0.5f, 0.5f, 0.0f));

	entity.setTarget(Vec3f(15.0f, 16.5f, 0.0f));

	selectedList = glGenLists(1);
	glNewList(selectedList, GL_COMPILE);
	glBegin(GL_LINE_STRIP);
		glVertex3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();

	glEndList();

	for (int i = 0; i < 16; i++) {
		int x = i / 4 - 2;
		int y = i % 4 - 2;
		chunks[i] = new Chunk(x, y);
		chunks[i]->gen();
	}
}

// Input
void keyPressed(unsigned char key, int x, int y)  {
	keys[key] = true;
}

void keyUp(unsigned char key, int x, int y)  {
	keys[key] = false;
}

void mouseInput(int button, int state, int x, int y) {
	buttons[button] = state;
	mouseX = x;
	mouseY = Height - y;
}

int lMouseX = 0, lMouseY = 0;

void motion(int x, int y) {
	mouseX = x;
	mouseY = Height - y;
}

void handleInput() {
	if (keys[ESCAPE]) {
		glutDestroyWindow(window); 
		exit(0);
	}

	if (keys['w']) {
		cam.posY += 2.0f / scale;
	} else if (keys['s']) {
		cam.posY -= 2.0f / scale;
	}
	if (keys['a']) {
		cam.posX -= 2.0f / scale;
	} else if (keys['d']) {
		cam.posX += 2.0f / scale;
	}

	if (buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN) {
		cam.posX += (float)(lMouseX - mouseX) / scale;		
		cam.posY += (float)(lMouseY - mouseY) / scale;
	} else if (buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN) {
		//drag select
	}
	

	selected.set(floor(cam.posX -((Width/2-mouseX) / scale)), 
				 floor(cam.posY - ((Height/2-mouseY) / scale)) + 1, 0.0f);

	lMouseX = mouseX;
	lMouseY = mouseY;
}

void Tick() {
	entity.tick();
}

void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cam.use();
	
	cam.apply();

	for (int i = 0; i < 16; i++) {
		// cout << i << endl;
		chunks[i]->draw();
	}

	entity.draw();

	glTranslated(selected.x, -selected.y, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glCallList(selectedList);
	

	// gui     // commented out for when I do work on gui
	glPushMatrix();	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glLoadMatrixf(gui);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(1.0f, 0.0f, 0.0f);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'a');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'b');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'c');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'd');
	glPopMatrix();

	glutSwapBuffers();
}

void Update() {
	handleInput();
	Tick();
	Draw();
}

int main(int argc, char **argv) {  
	/* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
		X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
	glutInit(&argc, argv);  

	/* Select type of Display mode:   
		Double buffer 
		RGBA color
		Alpha components supported 
		Depth buffer */  
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  

	/* get a 640 x 480 window
	 * Open a window */  
	glutInitWindowSize(640, 480);
	window = glutCreateWindow("");  

	/* Register the function to do all our OpenGL drawing. */
	glutDisplayFunc(&Draw);

	/* Even if there are no events, redraw our gl scene. */
	glutIdleFunc(&Update);

	/* Register the function called when our window is resized. */
	glutReshapeFunc(&Resize);

	/* Register the function called when the keyboard is pressed. */
	glutKeyboardFunc(&keyPressed);
	glutKeyboardUpFunc(&keyUp);

	glutMouseFunc(&mouseInput);
	glutMotionFunc(&motion);
	glutPassiveMotionFunc(&motion);

	/* Initialize our window. */
	InitGL(640, 480);

	start();

	/* Start Event Processing Engine */  
	glutMainLoop();  

	return 0;
}

