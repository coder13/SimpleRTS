#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "world/Chunk.h"

#define ESCAPE 27

using namespace std;

// window stuff
int window, scale = 16,
	Width, Height, 
	mWidth, mHeight;

// game stuff
float posX = 0, posY = 0;

bool keys[256], buttons[3];
float mouseX, mouseY;

Chunk* chunks[16];

// GL stuff
GLuint list;

void Resize(int width, int height) {
	if (width == 0 || height == 0)
		return;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Width = width;
	Height = height;
	mWidth = Width/scale;
	mHeight = Height/scale;
	
	glOrtho(-mWidth/2, mWidth/2, mHeight/2, -mHeight/2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
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

	for (int i = 0; i < 16; i++) {
		int x = i / 4 - 2;
		int y = i % 4 - 2;
		chunks[i] = new Chunk(x, y);
		chunks[i]->gen();
	}
}


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
		posY -= 1;
	} else if (keys['s']) {
		posY += 1;
	}
	if (keys['a']) {
		posX -= 1;
	} else if (keys['d']) {
		posX += 1;
	}

	if (buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN) {
		posY += lMouseY - mouseY;
		posX += lMouseX - mouseX;		
	}

	lMouseX = mouseX;
	lMouseY = mouseY;

}

void Tick() {

}

/* The main drawing function. */
void Draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslated(-posX/scale, posY/scale, 0);
	
	for (int i = 0; i < 16; i++) {
		chunks[i]->draw();
	}

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

