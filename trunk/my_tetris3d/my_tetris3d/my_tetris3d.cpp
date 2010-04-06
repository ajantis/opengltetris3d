/*
*
* Created by ajantis
* id.ajantis@gmail.com
* 06.04.2010
*
*/

// my_tetris3d.cpp : 
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <list>

#include <GL/glut.h>
#include "figures.h"



using namespace std;

//current figure
Figure* current;
float x_curr=0;
float y_curr=0;
float angle_curr = 0.0;

// list of all figures
list<Figure> list_figures;

float bottom = 0;

void mouse(int button, int state, int x, int y)
{
	// TO-DO  Make this work properly
   switch (button) {
	  case GLUT_LEFT_BUTTON:
       if (state == GLUT_DOWN) {
	        glutPostRedisplay();
         }
         break;

      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN) {
            glutPostRedisplay();
         }
         break;

      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {
            glutPostRedisplay();
         }
         break;

      default:
         break;
   }
}

void handleKeypress(unsigned char key, int x, int y) {

	switch (key) {
		case 27: //Escape key
				exit(0);
				break;
		
		case 97:  // 'A'
			x_curr-=0.2;
			glutPostRedisplay();
			break;

		case 100:  // 'D'
			x_curr+=0.2;
			glutPostRedisplay();
			break;
		case 115:  // 'W'
			y_curr-=0.2;
			glutPostRedisplay();
			break;
		case 119:  // 'S'
			y_curr+=0.2;
			glutPostRedisplay();
			break;
		case 122: // 'Z'	
			angle_curr+=90.0f;
			if(angle_curr>=360.0) angle_curr=0;
			glutPostRedisplay();
			break;
	}
}

void initRendering() {
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	
	//Fo'king Fog
	/*GLfloat FogColor[4]={0.3,0.3,0.3,1};
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,0.0);
	glFogf(GL_FOG_END,10.0);
	glFogfv(GL_FOG_COLOR,FogColor);
	*/
	

	glClearColor((float)100/256, (float)85/256, (float)67/256,0.0f);
}

void check_collision(){

	if (y_curr == bottom){
		&current.place();
	}
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -8.0f);
	//glTranslatef(0.0f, 0.0f, -zoom); // Mouse zooming
	
	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	Figure figure1 = Figure(0,0,0,'Z');

	//Draw current figure
	glPushMatrix();
	
	// Moving figure
	figure1.set_x_coord(x_curr);
	figure1.set_y_coord(y_curr);
	glTranslatef(figure1.x_coord(),figure1.y_coord(),figure1.z_coord());
	// End Moving

	glRotatef(angle_curr,0,0,1); // Rotating figure
	
	figure1.Draw();
	glPopMatrix();

	// Start Board
	glPushMatrix();

	glBegin(GL_QUADS);
	glVertex3f(-1,0.5,2+0.05);
	glVertex3f(-1,0.5,2-0.05);
	glVertex3f(-1,-1.5,2-0.05);
	glVertex3f(-1,-1.5,2+0.05);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(1,+0.5,2+0.05);
	glVertex3f(1,+0.5,2-0.05);
	glVertex3f(1,-1.5,2-0.05);
	glVertex3f(1,-1.5,2+0.05);
	glEnd();
	glBegin(GL_QUADS);
	glVertex3f(-1,-1.5,2-0.05);
	glVertex3f(-1,-1.5,2+0.05);
	glVertex3f(+1,-1.5,2+0.05);
	glVertex3f(+1,-1.5,2-0.05);
	glEnd();

	glPopMatrix();
    // End Board

	glutSwapBuffers();
	
}

void update(int value) {
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int _tmain(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	
	glutCreateWindow("Crazy Tetris 3d");
	initRendering();

	glutDisplayFunc(drawScene);
	glutMouseFunc(mouse);
	glutKeyboardFunc(handleKeypress);
	
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();

	return 0;
}

