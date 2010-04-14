/*
*
* Authors: Miracle and Ajantis
* mailto: MirraMax@yandex.ru id.ajantis@gmail.com 
*
* 06.04.2010
*
*/

// my_tetris3d.cpp : 
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#include <GL/glut.h>

#include "text3d.h"
#include "figures.h"
#include "game_logic.h"
#include "imageloader.h"
#include "simple_cube.h"

using namespace std;

float angl_mine = 0.0; // Angle for observing
float angl_mine2 = 0.0; // Angle for observing

//For Text3d
float _scale=1.0f; // Scaling Text

//The four strings that are drawn
char* STRS[4] = {"The", "Revolution", "Begins", "now!"};
char str[20] = "NULL";

char* WELCOME1 = "We are kindly proud to present...";
char* WELCOME2 = "THE MEGA TETRIS in 3-D!";

char* bmp_names[7]={".\\textures\\L.bmp",".\\textures\\S.bmp",".\\textures\\Z.bmp",".\\textures\\T.bmp",".\\textures\\O.bmp",".\\textures\\I.bmp",".\\textures\\J.bmp"};

int points = 0;
int time_update = 200; // Time between scene updates in milliseconds

void cleanup() {
	t3dCleanup();
}


//current figure
Figure* current = NULL;

// This figure for display next
Figure* next_figure_type = NULL;

//GLuint _textureId; //The id of the texture
//GLuint _textureId[7]; //The id of the texture

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}


void add_to_map()
{
	int x = 0;
	int y = 0;
	char tmp_color='D';

	for(int i=0;i<4;i++)
	{
		
		x = convert_x_to_index((*current).x_blocks[i]);
		y = convert_y_to_index((*current).y_blocks[i]); 
		 
		
		map[x][y] = true;	
		map_color[x][y] = (*current).get_type();
		
		
	}
	
}
void check_collision(){

		
		add_to_map();
		//check_map();
		(*current).place();

		(*next_figure_type).set_type((*current).get_next_type());
		(*next_figure_type).init_figure();

		(*current).set_x_coord(1);
		(*current).set_y_coord(1.9);
		(*current).set_rotate_angle(0.0);
}

bool x_left_collision()
{

	int x=0; int y=0;

	for(int i=0;i<4;i++)
	{
		x = convert_x_to_index((*current).x_blocks[i]);
		y = convert_y_to_index((*current).y_blocks[i]); 
						
		if(x>1)
		{
			if(map[x-1][y]==true)
			{
				return true;
			}
			
		}
		else
		{ 
			return true;
		}
		
	}

	return false;

}
bool x_right_collision(){
	int x=0; int y=0;
	
	for(int i=0;i<4;i++)
	{
		x = convert_x_to_index((*current).x_blocks[i]);
		y = convert_y_to_index((*current).y_blocks[i]); 
		 
				
		if(x<20)
		{
			if(map[x+1][y]==true)
			{
				return true;
			}
		}
		else 
		{
			return true;
		}
	}

	return false;

}

bool collision(){

	int x=0; int y=0;
	
	for(int i=0;i<4;i++)
	{
		x = convert_x_to_index((*current).x_blocks[i]);
		y = convert_y_to_index((*current).y_blocks[i]); 
		
				
		if(y<19)
		{
			if(map[x][y+1]==true)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
		
	

	}
	return false;
}

void handleMouse(int button, int state, int x, int y)
{
	// TO-DO  Make this work properly
   switch (button) {
	  case GLUT_LEFT_BUTTON:
       if (state == GLUT_DOWN) {
		   angl_mine+=5.0f;
	        glutPostRedisplay();
         }
         break;

      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN) {
			 angl_mine2+=5.0f;
            glutPostRedisplay();
         }
         break;

      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN) {
			 angl_mine-=5.0f;
            glutPostRedisplay();
         }
         break;

      default:
         break;
   }
}

void move_down()
{			
		float tmp_y = 0.0;

		if (!collision())
		{

			tmp_y = (*current).y_coord() - BOX_SIZE;
			(*current).set_y_coord(tmp_y);
			if (collision())  check_collision();
		}
		else check_collision();
		glutPostRedisplay();			
}

void handleKeypress(unsigned char key, int x, int y) {

	float tmp_x = 0.0;
	float tmp_y = 0.0;

	float tmp_angle = 90.0f;

	switch (key) {
		case 27: //Escape key
				exit(0);
				break;
		
		case 97:  // 'A'
			
			if(!x_left_collision())
			{
					tmp_x = (*current).x_coord() - 0.1;
					(*current).set_x_coord(tmp_x);
			}
			glutPostRedisplay();
			break;

		case 100:  // 'D'
		
			
			if(!x_right_collision())
			{
				tmp_x = (*current).x_coord() + 0.1;
				(*current).set_x_coord(tmp_x);
			}
			glutPostRedisplay();
			break;

		case 115:  // 'S'
			
			move_down();
			check_map();
			
			break;

		case 119:  // 'W'

			tmp_y = (*current).y_coord()+0.1;
			(*current).set_y_coord(tmp_y);
			glutPostRedisplay();

			break;
		
		case 122: // 'Z'	
			//angle_curr+=90.0f;
			//float tmp_angle = (*current).rotate_angle() + 90.0;
			
			(*current).rotate(tmp_angle);
				
			//if((*current).rotate_angle()>=360.0) (*current).set_rotate_angle(0.0);
			
			//angl_mine+=5.0;
			glutPostRedisplay();
			break;

		case 120: // 'X'	
					
			//angl_mine+=5.0;
			//clear_from_map(19);
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
	
	t3dInit(); // Text3d initialization

	//Fo'king Fog
	GLfloat FogColor[4]={0.5,0.5,0.5,1};
	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,17.0);
	glFogf(GL_FOG_END,19.0);
	glFogfv(GL_FOG_COLOR,FogColor);
	

	//glClearColor((float)100/256, (float)85/256, (float)67/256,0.0f);


	for(int i=0;i<7;i++)
	{
		Image* image = loadBMP(bmp_names[i]);
		_textureId[i] = loadTexture(image);
		delete image;
	}

	glClearColor(0.5,0.5,0.5,0.0f);
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
	
	glTranslatef(0.0f, 0.0f, -6.0f);
	//glTranslatef(0.0f, 0.0f, -zoom); // Mouse zooming

	glRotatef(angl_mine,0,1,0); // Mouse rotate left-right
	glRotatef(angl_mine2+10.0,1,0,0); // Mouse rotate down

	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glTranslatef(-1.0,-1.5,0.0);



	////////////////////////////// TESTING //////////////////////
	//glColor3f(1.0,1.0,1.0); // For TESTING	
	//glutSolidCube_own(0.1,_textureId[0]);
	//glColor3f(0.5,0.5,0.5);
	////////////////////////////// TESTING //////////////////////


	glPushMatrix();
	//Draw the whole MAP
	draw_map();
	glPopMatrix();
	
	glPushMatrix();  // Draw current Figure
	(*current).Draw();
	glPopMatrix();


	////////// Draw predicted Figure //////////
	glPushMatrix();  
	glTranslatef(2.3,1.7,0);

	glPushMatrix();
	glTranslatef(0,4*BOX_SIZE,0.0f);
	_scale = 0.1;
	glScalef(_scale, _scale, _scale);
	glColor3f(0.0f, 1.0f, 0.0f);
	t3dDraw3D("Next", 0, 0, BOX_SIZE);
	glPopMatrix();

	glColor3f(0.5,0.5,0.5);
	for(int num=17;num>-4;num--)
	{
		glPushMatrix();
		glTranslatef(3*BOX_SIZE,-num*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_textureId[2]);
		glPopMatrix();	
	}
	for(int num=2;num>-3;num--)
	{
		glPushMatrix();
		glTranslatef(num*BOX_SIZE,3*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_textureId[2]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(num*BOX_SIZE,-3*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_textureId[2]);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(num*BOX_SIZE,-17*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_textureId[2]);
		glPopMatrix();

	}
	(*next_figure_type).init_figure();
	glPushMatrix();
	(*next_figure_type).Draw();
	glPopMatrix();
	glPopMatrix();
	////////// END Draw predicted Figure //////////




	/* ////////
		TEXT
	*/ ////////
	
	glPushMatrix();
	
	glTranslatef(-0.5f,1.0f,0.0f);
	_scale=0.2f;
	glScalef(_scale, _scale, _scale);
	_scale=0.5f;
	glColor3f(0.0f, 1.0f, 0.0f);

	glPushMatrix();
	sprintf(str,"%d", points);
	t3dDraw3D(str, 0, 0, BOX_SIZE);
	glTranslatef(0, -1.0, 0);
	glScalef(_scale, _scale, _scale);
	t3dDraw3D("sec", 0, 0, BOX_SIZE);
	glPopMatrix();

	glPopMatrix();

	//WELCOME TEXT
	glPushMatrix();
	glTranslatef(1.0f,3.0f,-10.0f);
	_scale=0.4f;
	glScalef(_scale, _scale, _scale);
	_scale=0.4f;
	glColor3f(0.0f, 0.6f, 1.0f);
	t3dDraw3D(WELCOME2, 0, 0, BOX_SIZE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f,3.5f,-10.0f);
	_scale=0.4f;
	glScalef(_scale, _scale, _scale);
	_scale=0.4f;
	glColor3f(0.0f, 0.6f, 1.0f);
	t3dDraw3D(WELCOME1, 0, 0, BOX_SIZE);
	glPopMatrix();
	// END WELCOME TEXT


	//POINTS
	glPushMatrix();
	glTranslatef(2.3f,1.0f,0.0f);
	_scale=0.2f;
	glScalef(_scale, _scale, _scale);
	_scale=0.5f;
	glColor3f(0.0f, 1.0f, 0.0f);
	sprintf(str,"%d", points2);
	t3dDraw3D(str, 0, 0, BOX_SIZE);
	glTranslatef(0, -1.0, 0);
	glScalef(_scale, _scale, _scale);
	t3dDraw3D("Points", 0, 0, BOX_SIZE);

	glPopMatrix();
	//END POINTS


	glutSwapBuffers();	
}

void update(int value) {
	
	move_down(); // Moving down :) 
	check_map(); 
	points+= 1;
	glutPostRedisplay();
	glutTimerFunc(time_update, update, 0);
	
}

//Computes a scaling value so that the strings
float computeScale(char* strs[4]) {
	float maxWidth = 0;
	for(int i = 0; i < 4; i++) {
		float width = t3dDrawWidth(strs[i]);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}
	
	return 2.6f / maxWidth;
}


int main(int argc, char** argv)
{	
	current = new Figure(1,2,0,generate_type());
	

	next_figure_type = new Figure(0,0,0,(*current).get_next_type());
	(*next_figure_type).set_type((*current).get_next_type());
	(*next_figure_type).init_figure();


	init_map(); // Initializes out Game Map

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("Crazy Tetris 3d");
	initRendering();

	_scale = computeScale(STRS); // Text

	glutDisplayFunc(drawScene);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeypress);
	
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);
	
	glutMainLoop();

	return 0;
}

