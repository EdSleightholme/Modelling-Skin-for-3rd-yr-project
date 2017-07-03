#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Cell.h"

/*
29/06/17 Ed.S
Skin Model 1.0  

Each space on grid one 3 states 
Empty 
Dead 
Alive

Dead cells leave grid after set amout of time 
Alive cells split if there is gap next to in to 4 states
(Dead,Dead)
(Alive,Dead)
(Dead,Alive)
(Alive,Alive)

Concusion
Reach point where only alive cells ae left 


31/06/17
Skin Model 1.1

Alive cells become dead after a set amount of time
TODO 
Add recording how long a cell stays empty 
Concusion 

*/

Cell grid[100][100];

int	mouse_x = 0, mouse_y = 0;
bool LeftPressed = false;
int screenWidth = 510, screenHeight = 510;
bool keys[256];
float spin = 0;
float speed = 0;
int wait = 100;


//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height);				//called when the window is resized
void init();				//called in winmain when the program starts.
void keyfunction(unsigned char key, int x, int y);
void special(int key, int x, int y);
void update();				//called in winmain to update variables
void changingCells(int x, int y, int x2, int y2);
							/*************    START OF OPENGL FUNCTIONS   ****************/


void changingCells(int x, int y, int x2, int y2) {

	int temp = grid[x][y].getSplitType();
	switch (temp) {
	case(0):
		grid[x][y].changeToDead();
		grid[x2][y2].changeToDead();
		break;
	case(1):
		grid[x][y].changeToAlive();
		grid[x2][y2].changeToDead();
		break;
	case(2):
		grid[x][y].changeToDead();
		grid[x2][y2].changeToAlive();
		break;
	default:
		grid[x][y].changeToAlive();
		grid[x2][y2].changeToAlive();
		break;
	}

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Sleep(wait);
	glLoadIdentity();

	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {

			if (grid[x][y].getType() == 1) {
				if (x > 0) {
					if (grid[x - 1][y].getType() == 0) {
						changingCells(x, y, x - 1, y);
					}
				}
				if (x < 99) {
					if (grid[x + 1][y].getType() == 0) {
						changingCells(x, y, x + 1, y);
					}
				}

				if (y > 0) {
					if (grid[x ][y-1].getType() == 0) {
						changingCells(x, y, x, y-1);
					}
				}
				if (y < 99) {
					if (grid[x][y+1].getType() == 0) {
						changingCells(x, y, x, y+1);
					}
				}

				if (true == grid[x][y].countDown()) {
					grid[x][y].changeToDead();
				}

			}

			if (grid[x][y].getType() == 2) {
				if (true == grid[x][y].countDown()) {
					grid[x][y].changetoEmpty();
				}
			}

		}
	}






	for (int x = 0; x < 100; x++) {
		for (int y = 0; y< 100; y++) {
			int temp = grid[x][y].getType();
			switch (temp) {
			case (0):
				glColor3f(0, 0, 0);
				break;
			case (1):
				glColor3f(1, 1, 1);
				break;
			case (2):
				glColor3f(0, 0, 1);
				break;
			}
			
			glBegin(GL_POLYGON);
			glVertex2f(x*5, y * 5);
			glVertex2f((x+1) * 5, y * 5);
			glVertex2f((x + 1) * 5, (y + 1) * 5);
			glVertex2f(x * 5, (y + 1) * 5);
			glEnd();

		}

	}
	

	



	glutSwapBuffers();
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width; screenHeight = height;           // to ensure the mouse coordinates match 
														  // we will use these values to set the coordinate system

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);						//sets the clear colour to yellow
															//glClear(GL_COLOR_BUFFER_BIT) in the display function
															//will clear the buffer to this colour.
	int temp = 0;
	for (int x = 0; x < 100; x++) {
		for (int y = 0; y < 100; y++) {

			temp = rand() % 3;
			switch (temp) {
			case(0):
				grid[x][y].changeToAlive();
				break;
			case(1):
				grid[x][y].changeToDead();
				break;
			default:
				grid[x][y].changetoEmpty();
				break;
			}

		}
	}
}

void keyfunction(unsigned char key, int x, int y)
{
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;
	case GLUT_KEY_UP:
		wait += 1;
		break;
	case GLUT_KEY_DOWN:
		
		wait -= 1;
		if (wait == -1) {
			wait = 0;
		}
		break;
	}
}

void mouseMotion(int x, int y)
{
	mouse_y = screenHeight - y;
	mouse_x = x;
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			LeftPressed = true;
		}
		else
			LeftPressed = false;
		break;
	case GLUT_RIGHT_BUTTON:

		break;
	default:
		break;
	}
}

void update()
{
	spin += speed;
	if (spin > 360)
		spin = 0;

	glutPostRedisplay();
}
/**************** END OPENGL FUNCTIONS *************************/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("OpenGL FreeGLUT Template");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMotion);
	glutIdleFunc(update);

	//add keyboard callback.
	glutKeyboardFunc(keyfunction);
	//add callback for the function keys.
	glutSpecialFunc(special);

	glutMainLoop();

	return 0;
}

