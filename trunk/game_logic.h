int animate_appearance_time = 0;
int welldone_appearance_time = 6;

class Game {
	public:
		bool map[22][22];
		char map_color[22][22];
		int points; // Game points
		int seconds; // Game time
		int game_speed; // Game speed
		bool game_over; // angle for rotating points text

		bool check_fail(Figure* figure);

		float convert_x_from_index(int index);
		float convert_y_from_index(int index);

		int convert_x_to_index(float y);
		int convert_y_to_index(float y);

		void clear_from_map(int row);
		bool check_map();
		void draw_map(GLuint _panel_textureId);
		void init_map();
		void add_to_map(Figure* current);
		void handle_collision(Figure* current, Figure* next_figure_type);
		bool collision(Figure* current);
		bool x_left_collision(Figure* current);
		bool x_right_collision(Figure* current);
		void move_down(Figure* current,Figure* next_figure_type, bool game_over);
		void move_left(Figure* current);
		void move_right(Figure* current);

		Game()
		{
			points = 0; 
			seconds = 0;
			game_speed = 0; 
			game_over = false;
		}


};

bool Game::check_fail(Figure* figure)
{
	for(int i=0;i<4;i++)
	{
		if((*figure).y_blocks[i]>1.8) 
		{
			return true;
		}
	}
	return false;

}

void Game::clear_from_map(int row){
	
	for(int i=row;i>0;i--)
	{
		for(int j=1; j<20; j++)
		{
			map[j][i]=map[j][i-1];
			map_color[j][i]=map_color[j][i-1];
		}
	}
	for(int j=1; j<20; j++)
	{
		map[j][0]=false;
		map_color[j][0]='D';
		map[j][20]=true;
		map_color[j][20]='D';
	}
	points+=100;
}

bool Game::check_map()
{
	int count=0;
	int i = 0;
	int j = 0;
	for(i=1;i<20;i++)
	{
		for(j=1; j<20; j++)
		{
			if(map[j][i]==true) count++;
		}
		if(count>=18)
		{
			clear_from_map(i);
			welldone_appearance_time = 0;  // For WELLDONE text appearance
			
		}
		count = 0;
	}

	return 0;
}

void Game::draw_map(GLuint _panel_textureId){

	int curr_texture_map = 0;
	glColor3f(1.0,1.0,1.0); // Grey
	glPushMatrix();

	float x_curr=0.0; 
	float y_curr=0.0;

	for(int i=0;i<21;i++){

		for(int j=0;j<21;j++){
						
			glPushMatrix();
			if(map[i][j]==true){
	
				x_curr = convert_x_from_index(i); 
				y_curr = convert_y_from_index(j);
				if(i==0) x_curr+=0.1; // This is PATCH. Sorry.
				glTranslatef(x_curr,y_curr,0);

				glColor3f(1.0,1.0,1.0);
				switch(map_color[i][j])
				{
						case 'L':
							
							curr_texture_map = 0;
							break;
						case 'J':
							
							curr_texture_map = 6;
							break;
						case 'T':
							
							curr_texture_map = 3;
							break;
						case 'O':
							
							curr_texture_map = 4;
							break;
						case 'Z':
							
							curr_texture_map = 2;
							break;
						case 'S':
							
							curr_texture_map =1;
							break;
						case 'I':
							
							curr_texture_map =5;
							break;

						default:
							glColor3f(1.0,1.0,1.0);
							curr_texture_map = -1;
							break;
							
				}
				
				if(curr_texture_map!=-1)glutSolidCube_own(0.1,_textureId[curr_texture_map]);
				else glutSolidCube_own(0.1,_panel_textureId); // Draw the default cubes
				glColor3f(1,1,1);
				curr_texture_map = 2;
				
			}
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void Game::init_map(){
	for(int i=0;i<21;i++){
		for(int j=0;j<21;j++){
			map[i][j] = false;
			map_color[i][j]='D';
		}
	}
	for(int i=0;i<21;i++){
		map[0][i] = true;
		map[20][i] = true;
		map[i][20] = true;
	}
}

float Game::convert_x_from_index(int index){
	
	float x = 0.0;
	if((index<10) && (index>0)) x = index*0.1 + 0.1;
	else x = index*0.1;
	
	return x;
}

float Game::convert_y_from_index(int index){
	
	float y = -(index*0.1) + 2.0;
	
	return y;

}

int Game::convert_x_to_index(float x){
	
	int index = x*10;
	
	return index;
}

int Game::convert_y_to_index(float y){

	int index = 0;

	index = (2.0-y)*10;


	
	return index;

}


void Game::add_to_map(Figure* current)
{
	int x = 0;
	int y = 0;
	
	for(int i=0;i<4;i++)
	{
		
		x = convert_x_to_index((*current).x_blocks[i]);
		y = convert_y_to_index((*current).y_blocks[i]); 
		 
		map[x][y] = true;	
		map_color[x][y] = (*current).get_type();
		
	}
	
}


void Game::handle_collision(Figure* current, Figure* next_figure_type)
{
		add_to_map(current);
		//check_map();
		
		if(check_fail(current))
		{
			printf("Game OVER!");
			printf("\r\n");
			game_over = true;
			
		}
		else
		{
			(*current).place();
			(*current).set_type((*next_figure_type).get_type());
			(*current).init_figure();
			(*next_figure_type).set_type((*next_figure_type).generate_type());
			(*next_figure_type).init_figure();

			animate_appearance_time = 0;
			
			(*current).set_x_coord(1);
			(*current).set_y_coord(1.9);
			(*current).set_rotate_angle(0.0);
			
		}
}


bool Game::collision(Figure* current){

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


bool Game::x_left_collision(Figure* current)
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
		else return true;
	}
	return false;
}


bool Game::x_right_collision(Figure* current){
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

void Game::move_down(Figure* current,Figure* next_figure_type, bool game_over)
{		
		if (!collision(current))
		{
			(*current).set_y_coord((*current).y_coord() - BOX_SIZE);
			if (collision(current))  handle_collision(current,next_figure_type);
		}
		else handle_collision(current,next_figure_type);
		glutPostRedisplay();			
}

void Game::move_left(Figure* current)
{			
		if(!x_left_collision(current))
		{
			(*current).set_x_coord((*current).x_coord() - 0.1);
		}	
		
}

void Game::move_right(Figure* current)
{			
		if(!x_right_collision(current))
		{
			(*current).set_x_coord((*current).x_coord() + 0.1);
		}		
}

