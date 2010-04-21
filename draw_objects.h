
const float FLOOR_SIZE = 3.8f; //The length of each side of the floor

GLuint _floor_textureId; //The id of the floor texture
GLuint _panel_textureId; //The id of the panel texture
GLuint _wall_textureId; //The id of the floor texture

GLuint _frontwall_textureId; //The id of the front wall texture

GLfloat lightPos0[] = {-2.0f, 2.0f, 3.0f, 0.0f};
GLfloat lightPos1[] = {2.0f, 2.0f, 3.0f, 1.0f};

float alpha_wall = 1.0f;

//float points_angle;
char* WELCOME1 = "The TETRIS";
char* WELCOME2 = "";
char str[20] = "";

void drawText(Game game, float points_angle)
{
	float _scale = 0.1;
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
	sprintf(str,"%d", game.seconds);
	glPushMatrix();
	if(points_angle>90.0 && points_angle<=270.0)
	{
		glRotatef(points_angle+180.0,0,1,0);
	}
	else glRotatef(points_angle,0,1,0);
	t3dDraw3D(str, 0, 0, BOX_SIZE);
	glPopMatrix();
	glTranslatef(0, -1.0, 0);
	glScalef(_scale, _scale, _scale);
	t3dDraw3D("sec", 0, 0, BOX_SIZE);
	glPopMatrix();

	glPopMatrix();

	//WELCOME TEXT
	glPushMatrix();
	glTranslatef(1.0f,2.5f,0.0f);
	_scale=0.1f;
	glScalef(_scale, _scale, _scale);
	_scale=0.1f;
	glColor3f(0.0f, 0.6f, 1.0f);
	//t3dDraw3D(WELCOME2, 0, 0, BOX_SIZE);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0f,2.5f,0.0f);
	_scale=0.15f;
	glScalef(_scale, _scale, _scale);
	_scale=0.1f;
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
	sprintf(str,"%d", game.points);
	glPushMatrix();
	if(points_angle>90.0 && points_angle<=270.0)
	{
		glRotatef(-points_angle-180.0,0,1,0);
	}
	else glRotatef(-points_angle,0,1,0);
	t3dDraw3D(str, 0, 0, BOX_SIZE);
	glPopMatrix();
	glTranslatef(0, -1.0, 0);
	glScalef(_scale, _scale, _scale);
	t3dDraw3D("Points", 0, 0, BOX_SIZE);

	glPopMatrix();
	//END POINTS

}

void drawPredictedFigure(Figure* next_figure_type, GLuint _panel_textureId,float next_figure_angle)
{
	float _scale = 0.1f;

	glPushMatrix();  
	glTranslatef(2.3,1.7,0);

	glPushMatrix();
	glTranslatef(0,5*BOX_SIZE,0.0f);
	_scale = 0.1;
	glScalef(_scale, _scale, _scale);
	glColor3f(0.0f, 1.0f, 0.0f);
	t3dDraw3D("Next", 0, 0, BOX_SIZE);
	glPopMatrix();

	glColor3f(1,1,1);
	for(int num=17;num>-4;num--)
	{
		glPushMatrix();
		glTranslatef(3*BOX_SIZE,-num*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_panel_textureId);
		glPopMatrix();	
	}
	for(int num=2;num>-3;num--)
	{
		glPushMatrix();
		glTranslatef(num*BOX_SIZE,3*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_panel_textureId);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(num*BOX_SIZE,-3*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_panel_textureId);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(num*BOX_SIZE,-17*BOX_SIZE,0);
		glutSolidCube_own(BOX_SIZE,_panel_textureId);
		glPopMatrix();

	}
	(*next_figure_type).init_figure();
	glPushMatrix();
	glRotatef(next_figure_angle,1,1,0);
	(*next_figure_type).Draw();
	glPopMatrix();
	glPopMatrix();



}


void drawControlPanel(GLuint _texturePanelId)
{
	float _scale = 0.1f;

	for(int i = 1; i<12;i++)
	{
		glPushMatrix();
		glTranslatef(BOX_SIZE*i,0,0);
		glutSolidCube_own(BOX_SIZE,_texturePanelId);
		glTranslatef(0,BOX_SIZE*7,0);
		glutSolidCube_own(BOX_SIZE,_texturePanelId);
		glTranslatef(0,BOX_SIZE*5,0);
		glutSolidCube_own(BOX_SIZE,_texturePanelId);
		glPopMatrix();
	}
	for(int i = 0; i<21;i++)
	{
		glPushMatrix();
		glTranslatef(0,BOX_SIZE*i,0);
		glutSolidCube_own(BOX_SIZE,_texturePanelId);
		glPopMatrix();
	}

	// "Well Done" text
	if(welldone_appearance_time <= 5)
	{
		glPushMatrix();
		glTranslatef(0.6f,0.4f,0.0f);
		_scale=0.15f;
		glScalef(_scale, _scale, _scale);
		glColor3f(1.0f, 0.0f, 0.0f);
		t3dDraw3D("Well done!", 0, 0, 0.3);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(0.6f,2.0f,0.0f);
	_scale=0.1f;
	glScalef(_scale, _scale, _scale);
	glColor3f(0.0f, 1.0f, 0.0f);
	t3dDraw3D("Game controls", 0, 0, 0.3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.0f,1.5f,0.0f);
		glPushMatrix();
			glRotatef(90,0,1,0);
			glColor3f(0.0f, 0.6f, 1.0f);
			glutSolidCone(0.05,0.13,10,10);
		glPopMatrix();
		glTranslatef(-0.1f,0.0f,0.0f);
		glScalef(_scale, _scale, _scale);
		glColor3f(0.0f, 1.0f, 0.0f);
		t3dDraw3D("D", 0, 0, 0.3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.2f,1.5f,0.0f);
		glPushMatrix();
			glRotatef(-90,0,1,0);
			glColor3f(0.0f, 0.6f, 1.0f);
			glutSolidCone(0.05,0.13,10,10);
		glPopMatrix();
		glTranslatef(0.1f,0.0f,0.0f);
		glScalef(_scale, _scale, _scale);
		glColor3f(0.0f, 1.0f, 0.0f);
		t3dDraw3D("A", 0, 0, 0.3);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.6f,1.4f,0.0f);
		glPushMatrix();
			glRotatef(90,1,0,0);
			glColor3f(0.0f, 0.6f, 1.0f);
			glutSolidCone(0.05,0.13,10,10);
		glPopMatrix();
		glTranslatef(0.0f,0.1f,0.0f);
		glScalef(_scale, _scale, _scale);
		glColor3f(0.0f, 1.0f, 0.0f);
		t3dDraw3D("S", 0, 0, 0.3);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.4f,1.7f,0.0f);
		glPushMatrix();
			glScalef(_scale, _scale, _scale);
			glColor3f(0.0f, 1.0f, 0.0f);
			t3dDraw3D("Z", 0, 0, 0.3);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.3f,0.0f,0.0f);
			glScalef(_scale, _scale, _scale);
			glColor3f(0.0f, 0.6f, 1.0f);
			t3dDraw3D("rotate", 0, 0, 0.3);
		glPopMatrix();
	glPopMatrix();
}


//Draws the floor
void drawFloor(int textureId) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-FLOOR_SIZE / 2, 0, FLOOR_SIZE / 2);
	glTexCoord2f(0, 1);
	glVertex3f(-FLOOR_SIZE / 2, 0, -FLOOR_SIZE / 2);
	glTexCoord2f(1, 1);
	glVertex3f(FLOOR_SIZE / 2, 0, -FLOOR_SIZE / 2);
	glTexCoord2f(1, 0);
	glVertex3f(FLOOR_SIZE / 2, 0, FLOOR_SIZE / 2);
	
	glEnd();
}

void drawMirrorFloor(Game game, 
					 Figure* current, 
					 Figure* next_figure_type, 
					 float next_figure_angle, 
					 float points_angle,
					 ParticleEngine* _particleEngine)
{
	glPushMatrix();

		glTranslatef(0.75,-0.05,0);

		glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
		glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
		glDisable(GL_DEPTH_TEST); //Disable depth testing
		glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
		//Make pixels in the stencil buffer be set to 1 when the stencil test passes
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//Set all of the pixels covered by the floor to be 1 in the stencil buffer
		drawFloor(_floor_textureId);
		
		glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
		glEnable(GL_DEPTH_TEST); //Enable depth testing
		//Make the stencil test pass only when the pixel is 1 in the stencil buffer
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
		
		//Draw the scene, reflected vertically, at all pixels where the stencil
		//buffer is 1
		glPushMatrix();
		
			glTranslatef(-0.75, 0, 0);
			glScalef(1, -1, 1);

			/// MIRRORING
			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); 
			glLightfv(GL_LIGHT1, GL_POSITION, lightPos1); 
		     // particles
			/*
			if(animate_appearance_time <= 5)
			{
				glPushMatrix();
					glTranslatef(0.0f,1.5f, -1.0f);
					glScalef(0.5f, 0.5f, 0.5f);
					_particleEngine->draw();
				glPopMatrix();
			}// end particles
			*/
			

			game.draw_map(_panel_textureId);

			drawPredictedFigure(next_figure_type,_panel_textureId,next_figure_angle);
			(*current).Draw();
			drawText(game, points_angle);
			glPushMatrix();
				glColor3f(1,1,1);
				glTranslatef(-11*BOX_SIZE,0,0);
				drawControlPanel(_panel_textureId);
			glPopMatrix();
			/// END MIRRORING

		glPopMatrix();
		
		glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
		
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); // returning lights
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1); // returning lights
		
		//Blend the floor onto the screen
		glEnable(GL_BLEND);
		glColor4f(1, 1, 1, 0.5f);
		drawFloor(_floor_textureId);
		glDisable(GL_BLEND);
		

		

	glPopMatrix();

}

void drawWall(Game game, 
					 Figure* current, 
					 Figure* next_figure_type, 
					 float next_figure_angle, 
					 float points_angle,
					 ParticleEngine* _particleEngine)
{
	glPushMatrix();
		glTranslatef(0.75,-0.05+FLOOR_SIZE/2,-FLOOR_SIZE/2);
		
		glRotatef(90.0,1,0,0);

		glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
		glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
		glDisable(GL_DEPTH_TEST); //Disable depth testing
		glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
		//Make pixels in the stencil buffer be set to 1 when the stencil test passes
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//Set all of the pixels covered by the wall to be 1 in the stencil buffer
		drawFloor(_frontwall_textureId);
		
		glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
		glEnable(GL_DEPTH_TEST); //Enable depth testing
		//Make the stencil test pass only when the pixel is 1 in the stencil buffer
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
		
		//Draw the scene, reflected horizontally, at all pixels where the stencil
		//buffer is 1
		glPushMatrix();
			glRotatef(-90.0,1,0,0);
			glTranslatef(-0.75,+0.05-FLOOR_SIZE/2,-FLOOR_SIZE/2);
			glScalef(1, 1, -1);

			
			glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); // returning lights
			glLightfv(GL_LIGHT1, GL_POSITION, lightPos1); // returning lights
		

			glPushMatrix();
				/// MIRRORING

				/*
				if(animate_appearance_time <= 5)
				{
					glPushMatrix();
						glTranslatef(0.0f, 1.5f, -1.0f);
						glScalef(0.5f, 0.5f, 0.5f);
						_particleEngine->draw();
					glPopMatrix();
				}
				*/
				

				game.draw_map(_panel_textureId);
				drawPredictedFigure(next_figure_type,_panel_textureId,next_figure_angle);
				(*current).Draw();
				drawText(game, points_angle);
				glPushMatrix();
					glColor3f(1,1,1);
					glTranslatef(-11*BOX_SIZE,0,0);
					drawControlPanel(_panel_textureId);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.75,-0.05,0);
				glEnable(GL_BLEND);
				glColor4f(1, 1, 1, 0.5f);
				drawFloor(_floor_textureId);
				glDisable(GL_BLEND);
				glPopMatrix();



				/// Mirroring Left and right WALLS
				glPushMatrix();
				glTranslatef(0.75-FLOOR_SIZE/2,-0.05+FLOOR_SIZE/2,0);
				glRotatef(90.0,0,0,1);
				glEnable(GL_BLEND);
				glColor4f(1, 1, 1, alpha_wall);
				drawFloor(_wall_textureId);
				glDisable(GL_BLEND);
				glPopMatrix();

				glPushMatrix();
				glTranslatef(0.75+FLOOR_SIZE/2,-0.05+FLOOR_SIZE/2,0);
				glRotatef(90.0,0,0,1);
				glEnable(GL_BLEND);
				glColor4f(1, 1, 1, alpha_wall);
				drawFloor(_wall_textureId);
				glDisable(GL_BLEND);
				glPopMatrix();
				/// End Mirroring Left and right WALLS


				/// END MIRRORING
			glPopMatrix();
		glPopMatrix();
		
		glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
		
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0); // returning lights
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1); // returning lights

		glPushMatrix();
		//Blend the wall onto the screen
		glEnable(GL_BLEND);
		glColor4f(1, 1, 1, 0.5f);
		drawFloor(_frontwall_textureId);
		glDisable(GL_BLEND);
		glPopMatrix();

		/*
		
		*/

	glPopMatrix();
}

void drawWalls(Game game, 
					 Figure* current, 
					 Figure* next_figure_type, 
					 float next_figure_angle, 
					 float points_angle)
{
//// FLOOR/////
	glPushMatrix();
	//glTranslatef(-1.5,2.4,0);
	glTranslatef(0.75-FLOOR_SIZE/2,-0.05+FLOOR_SIZE/2,0);
	glRotatef(90.0,0,0,1);

	glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
	glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
	glDisable(GL_DEPTH_TEST); //Disable depth testing
	glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
	//Make pixels in the stencil buffer be set to 1 when the stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//Set all of the pixels covered by the floor to be 1 in the stencil buffer
	drawFloor(_wall_textureId);
	
	glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	//Make the stencil test pass only when the pixel is 1 in the stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
	
	//Draw the cube, reflected vertically, at all pixels where the stencil
	//buffer is 1
	glPushMatrix();
	//glScalef(1, -1, 1);
	//glTranslatef(0, BOX_HEIGHT, 0);
	//drawCube(_textureId, _angle);
	glPopMatrix();
	
	glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
	
	//Blend the floor onto the screen
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1,alpha_wall);
	drawFloor(_wall_textureId);
	glDisable(GL_BLEND);

	glPopMatrix();



//// FLOOR/////
	glPushMatrix();
	glTranslatef(0.75+FLOOR_SIZE/2,-0.05+FLOOR_SIZE/2,0);

	glRotatef(90.0,0,0,1);

	glEnable(GL_STENCIL_TEST); //Enable using the stencil buffer
	glColorMask(0, 0, 0, 0); //Disable drawing colors to the screen
	glDisable(GL_DEPTH_TEST); //Disable depth testing
	glStencilFunc(GL_ALWAYS, 1, 1); //Make the stencil test always pass
	//Make pixels in the stencil buffer be set to 1 when the stencil test passes
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//Set all of the pixels covered by the floor to be 1 in the stencil buffer
	drawFloor(_wall_textureId);
	
	glColorMask(1, 1, 1, 1); //Enable drawing colors to the screen
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	//Make the stencil test pass only when the pixel is 1 in the stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Make the stencil buffer not change
	
	//Draw the cube, reflected vertically, at all pixels where the stencil
	//buffer is 1
	glPushMatrix();
	//glScalef(1, -1, 1);
	//glTranslatef(0, BOX_HEIGHT, 0);
	//drawCube(_textureId, _angle);
	glPopMatrix();
	
	glDisable(GL_STENCIL_TEST); //Disable using the stencil buffer
	
	//Blend the floor onto the screen
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, alpha_wall);
	drawFloor(_wall_textureId);
	glDisable(GL_BLEND);

	glPopMatrix();

}