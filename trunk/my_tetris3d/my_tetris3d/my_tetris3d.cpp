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

#define LEFT_BOUND -1.0
#define RIGHT_BOUND 1.0
#define DOWN_BOUND -1.5


using namespace std;

//current figure
Figure* current = NULL;
float x_curr=0;
float y_curr=0.5;
float angle_curr = 0.0;

// list of all figures
list<Figure> list_figures;

float bottom = -1.5;

void check_collision(){

	if (y_curr+0.5 <= DOWN_BOUND){
		
		(*current).place(DOWN_BOUND,current);
		x_curr=0.5;
		y_curr=0.5;
		angle_curr = 0.0;
	}
}

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
			
			if(x_curr>LEFT_BOUND){
				x_curr-=0.2;
				glutPostRedisplay();
			}
			break;

		case 100:  // 'D'
			
			if(x_curr<RIGHT_BOUND){
				x_curr+=0.2;
				glutPostRedisplay();
			}
			break;

		case 115:  // 'W'
			y_curr-=0.2;
			glutPostRedisplay();
			break;

		case 119:  // 'S'
			
			check_collision();
			if(y_curr<RIGHT_BOUND){
				y_curr+=0.2;
				glutPostRedisplay();
			}
			break;
		case 122: // 'Z'	
			//angle_curr+=90.0f;
			//if(angle_curr>=360.0) angle_curr=0;
			(*current).set_rotate_angle((*current).rotate_angle()+90.0);
			if((*current).rotate_angle()>=360.0) angle_curr=0;
	
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
	//current = &Figure(0,0,0,'T');

	glClearColor((float)100/256, (float)85/256, (float)67/256,0.0f);
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

	//Figure figure1 = Figure(0,0,0,'Z');

	//Draw current figure
	glPushMatrix();
	
	// Moving figure
	(*current).set_x_coord(x_curr);
	(*current).set_y_coord(y_curr);
	//glTranslatef((*current).x_coord(),(*current).y_coord(),(*current).z_coord());
	// End Moving

	//glRotatef((*current).rotate_angle(),0,0,1); // Rotating figure
	
	(*current).Draw();
	glPopMatrix();


	//Draw the rest figures
	//for(int i=0; i<figure_count-1;i++)
	//{
		//glTranslatef((*current).x_coord(),(*current).y_coord(),(*current).z_coord()); // Moving figure
		//glRotatef(angle_curr,0,0,1); // Rotating figure
		
	//}
	
	// End draw

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
	
	check_collision();
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int _tmain(int argc, char** argv)
{	
	current = &Figure(0,0,0,generate_type(),current);
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

