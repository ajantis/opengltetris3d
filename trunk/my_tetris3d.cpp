/*
*
* Authors: Miracle and Ajantis
* mailto: MirraMax@yandex.ru id.ajantis@gmail.com 
*
* 06.04.2010
*
*/

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <GL/glut.h>
#include "text3d.h"
#include "figures.h"
#include "game_logic.h"
#include "imageloader.h"
#include "simple_cube.h"

#include "particles.h"
#include "draw_objects.h"

#pragma comment( lib, "opengl32.lib" )				
#pragma comment( lib, "glu32.lib" )					
#pragma comment( lib, "winmm.lib" )					
 
#define UPDATE_ANIMATION_TIME 400 //Time between updating animation
#define REAL_TIME 1000 // 1 second is 1 second :)
#define GAME_SPEED 1000 // GAME SPEED in _milliseconds_ :crazy:


using namespace std;

float angl_mine = 0.0; // Angle for observing
float angl_mine2 = 0.0; // Angle for observing
float next_figure_angle = 0.0; // angle for rotating next figure preview
float points_angle = 0.0; // angle for rotating points text

int seconds = 0;
int game_speed = GAME_SPEED;
//int animate_appearance_time = 0; // until UPDATE_ANIMATION_TIME*25;

Game game;  // Instance of current Game process (all game logics are there)

float game_over_z = -8.0; // beginning position of game_over notification text

//For Text3d
float _scale = 1.0f; // Scaling Text

float zoom = 0.0f; // multiplier for zooming of the whole game 3d scene


// Paths to all texture files for cubes
char* bmp_names[7]={".\\textures\\L.bmp",".\\textures\\S.bmp",".\\textures\\Z.bmp",".\\textures\\T.bmp",".\\textures\\O.bmp",".\\textures\\I.bmp",".\\textures\\J.bmp"};
char* bmp_panel = ".\\textures\\panel2.bmp";

//Declaration of current figure
Figure* current = NULL;

// This figure for display next
Figure* next_figure_type = NULL;

ParticleEngine* _particleEngine; //particles

GLuint _particle_textureId;  // texture ID for particle

GLuint _displayList_walls_Id; // ID of the display list for walls



// cleaning objects created for text3D
/*
void cleanup() {
	t3dCleanup();
	delete _particleEngine;
}
*/

// Returns texture id of loaded from bmp(256*256) 24bit texture
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

// Function for handling mouse calls
void handleMouse(int button, int state, int x, int y)
{
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

// Function for handling keyboard calls
void handleKeypress(unsigned char key, int x, int y) {

	float tmp_x = 0.0;
	float tmp_y = 0.0;

	float tmp_angle = 90.0f;

	switch (key) {
		case 27: //Escape key
				exit(0);
				break;
		
		if(!game.game_over) {
		case 97:  // 'A'
			
			game.move_left(current);
			glutPostRedisplay();
			break;

		case 100:  // 'D'
		
			game.move_right(current);
			glutPostRedisplay();
			break;

		case 115:  // 'S'
			
			game.move_down(current,next_figure_type, game.game_over);
			game.check_map();
			
			break;
		
		case 122: // 'Z'	
			
			if(((*current).x_coord()>=0.3) && ((*current).x_coord()<=1.8))(*current).rotate();

			glutPostRedisplay();
			break;
		}
		case 120: // 'X'	
					
			zoom-=0.2;
			glutPostRedisplay();
			break;

		case 119:  // 'W'

			zoom+=0.2;
			glutPostRedisplay();

		break;
	}
}

// OpenGL initialization
void initRendering() 
{

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable Alpha Blending (disable alpha testing)


	t3dInit(); // Text3d initialization

	// Enabling Fog
	
	glEnable(GL_FOG);
		
	// Loading textures for cubes
	for(int i=0;i<7;i++)
	{
		Image* image = loadBMP(bmp_names[i]);
		_textureId[i] = loadTexture(image);
		delete image;
	}
	// Loading texture for floor
	Image* image = loadBMP(".\\textures\\chess.bmp");
	_floor_textureId = loadTexture(image);
	delete image;

	// Loading texture for floor and walls
	image = loadBMP(".\\textures\\floor.bmp");
	_wall_textureId = loadTexture(image);
	delete image;

	// Loading texture for floor and walls
	image = loadBMP(".\\textures\\mirror.bmp");
	_frontwall_textureId = loadTexture(image);
	delete image;


	// Loading texture for panel
	image = loadBMP(bmp_panel);
	_panel_textureId = loadTexture(image);
	delete image;

	//for particles
	image = loadBMP(".\\textures\\particle.bmp");
	Image* alphaChannel = loadBMP(".\\textures\\particle_alpha.bmp");
	_particle_textureId = loadAlphaTexture(image, alphaChannel);
	delete image;
	delete alphaChannel;

	// LISTS
	_displayList_walls_Id = glGenLists(1); //Make room for the display list
    glNewList(_displayList_walls_Id, GL_COMPILE); //Begin the display list
    drawWalls(game,current, next_figure_type, next_figure_angle,points_angle);
    glEndList(); //End the display list


	// Background color
	glClearColor(0.5,0.5,0.5,1.0f);  // Grey Background!
}

// Function for handling of resizing game window
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

// Basic function for Drawing of the whole scene
void drawScene() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Fog
	GLfloat FogColor[4]={0.5,0.5,0.5,1.0}; 
	glFogfv(GL_FOG_COLOR,FogColor);
	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,10.0);
	glFogf(GL_FOG_END,15.0);
	//glFogf(GL_FOG_DENSITY,0.20); // For GL_EXP

	GLfloat ambientColor[] = {0.1f, 0.1f, 0.1f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);	
	

	// Lightning number 0
	GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
	// Lightning number 1
	GLfloat lightColor1[] = {0.3f,0.3f, 0.3f, 0.0f};
	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	

	glTranslatef(-1.0,-1.5,0.0);
	glTranslatef(0.0f, 0.0f, -5.0f);
	glTranslatef(0.0f, 0.0f, -zoom); // Mouse zooming

	glRotatef(angl_mine,0,1,0); // Mouse rotate left-right
	glRotatef(angl_mine2+10.0,1,0,0); // Mouse rotate down

	glPushMatrix(); // GLOBAL

	/*
	if(animate_appearance_time <= 5){

		glPushMatrix(); //partcles 
			glTranslatef(0.0f, 1.5f, -1.0f);
			glScalef(0.5f, 0.5f, 0.5f);
			_particleEngine->draw();
		glPopMatrix();

	}
	*/

	glCullFace(GL_BACK);  // Skipping backward faces to improve performance
	glEnable(GL_CULL_FACE);  // Enable alpha CULLING - to not to draw backward polygons
	glPushMatrix();
		//Draw the whole MAP
		game.draw_map(_panel_textureId);
	glPopMatrix();

	glPushMatrix();  // Draw current Figure
		(*current).Draw();
	glPopMatrix();

	glPushMatrix(); // draws left panel
		glColor3f(1,1,1);
		glTranslatef(-11*BOX_SIZE,0,0);
		drawControlPanel(_panel_textureId);
	glPopMatrix();

	drawPredictedFigure(next_figure_type,_panel_textureId,next_figure_angle); //draws next figure and frame

	drawText(game, points_angle);

	if(game.game_over)
	{
		// GAME OVER TEXT
		glPushMatrix();
		glTranslatef(1.0f,0.0f,game_over_z);
		_scale=0.5f;
		glScalef(_scale, _scale, _scale);
		glColor3f(1.0f, 0.0f, 0.0f);
		t3dDraw3D("Game over!", 0, 0, 2*BOX_SIZE);
		glPopMatrix();
		//END GAME OVER TEXT
	}
	glDisable(GL_CULL_FACE);  // Disable alpha CULLING - to not to draw backward polygons

	drawMirrorFloor(game, current, next_figure_type, next_figure_angle, points_angle,_particleEngine);
	
	drawWall(game, current, next_figure_type, next_figure_angle,points_angle,_particleEngine);

	//drawWalls(game,current, next_figure_type, next_figure_angle,points_angle);
	glCallList(_displayList_walls_Id); // Draw left and right walls


	glPopMatrix();// GLOBAL

	glutSwapBuffers();	
}

// Function for updating animation of objects: rotating texts, next figure preview, etc
void update_animation(int value)
{
	next_figure_angle +=18.0;
	if(next_figure_angle>=360.0)next_figure_angle=0.0;

	points_angle+=18.0;
	if(points_angle>=360.0)points_angle=0.0;

	if(game.game_over)
	{
		if(game_over_z<=0.0) game_over_z+= 0.5;
	}

	_particleEngine->advance(UPDATE_ANIMATION_TIME / 1000.0f);


	if(animate_appearance_time <= 5) animate_appearance_time++;
	if(welldone_appearance_time <= 5) welldone_appearance_time++;

	glutPostRedisplay();
	glutTimerFunc(UPDATE_ANIMATION_TIME, update_animation, 0); // Every second
}

// Function for updating time info in game
void update_time(int value) {
	
	if(!game.game_over){
		game.seconds+= 1;
	}
	
	glutTimerFunc(REAL_TIME, update_time, 0); // Every second
}

// Function for updating game logic 
void update_logic(int value) {
	
	if(!game.game_over){
		game.move_down(current, next_figure_type, game.game_over); // Moving down :) 
		game.check_map(); 
	}
	
	glutPostRedisplay();
	glutTimerFunc(game_speed, update_logic, 0);
}

// Main func
int main(int argc, char** argv)
{
	//srand((unsigned int)time(0)); //Seed the random number generator
	initrand();

	if ( argc >= 5 ) 
	{
		// We print argv[0] assuming it is the program name
		cout<<"Usage: " << argv[0] << " <game resolution <width><height>> <game speed 1,2,3..>";
		return 1;
	}
	else {

	printf("Welcome to the Tetris 3D\r\n");
	printf("\r\n");
	printf("Press ESC to quit the game...\r\n");
	printf("\r\n");

	game = Game(); // Create new Game

	current = new Figure(1,2,0); // Creating current figure that will be moving to the map
	//next_figure_type = new Figure(0,0,0,(*current).get_next_type()); // Creating figure for displaying next figure
	next_figure_type = new Figure(0,0,0); // Creating figure for displaying next figure

	game.init_map(); // Initializes out Game Map
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);

	char* window_name = "Tetris 3d v.0.50";
	if(argc > 1)
	{
		if(strcmp(argv[1],"full")==0)
		{
			glutGameModeString("1024x768:32@75");
			glutEnterGameMode();	
		}
		else 
		{
			if(argc>=3)
			{
				glutInitWindowSize(atoi(argv[1]),atoi(argv[2]));
			}
			if(argc==2) 
			{
				glutInitWindowSize(atoi(argv[1]),atoi(argv[1])); 
			}
			glutCreateWindow(window_name);
		}
		if(argc==4) 
		{
			game_speed = (int)game_speed/atoi(argv[3]);
		}
	}
	else
	{
		glutInitWindowSize(800,800); // default resotution
		glutCreateWindow(window_name);
	}
	initRendering();
	

	glutDisplayFunc(drawScene);
	glutMouseFunc(handleMouse);
	glutKeyboardFunc(handleKeypress);
	
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update_logic, 0);  // Main timer for game logic
	glutTimerFunc(REAL_TIME, update_time, 0); // Updating Every second
	glutTimerFunc(UPDATE_ANIMATION_TIME, update_animation, 0); // Updating all background animation
	

	_particleEngine = new ParticleEngine(_particle_textureId);

	glutMainLoop();

	return 0;
	}

}

