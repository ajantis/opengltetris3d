#include <ctime>   // For srand() and time() functions!
#include <cstdlib> // For srand() and time() functions! 

#include "simple_cube.h"


#define BOX_SIZE 0.1

using namespace std;

GLuint _textureId[7];




// random generator initialization
void initrand()
{
    srand((unsigned)(time(0)));
} 

//generates a psuedo-random integer between min and max 
int randint(int min, int max)
{
	initrand();
    if (min>max)
    {
		return (rand() % min) + max;
    }
    else
    {
		return (rand() % max) + min;
    }
} 

char generate_type(){

	initrand();
	int random_integer = randint(1,7);
	switch(random_integer){
	
		case 1:
			return 'T';
			break;
		case 2:
			return 'Z';
			break;
		case 3:
			return 'S';
			break;			
		case 4:
			return 'I';
			break;
		case 5:
			return 'O';
			break;
		case 6:
			return 'L';
			break;
		case 7:
			return 'J';
			break;
		

		default:
			return 'E'; //Error: Something went wrong!
			break;
	}
}




class Figure {
	private:
		float x; 
		float y; 
		float z; 
		char type;
		int curr_texture;

		char next_type;

	public:
		float rot_angle;

		float x_blocks[4];
		float y_blocks[4];


		Figure(float x1, float y1, float z1, char type1){
			x = x1;
			y = y1;
			z = z1;
			type = type1;			
			rot_angle = 0.0;
			init_figure();
			curr_texture = 0;

			next_type = generate_type();
		}
		
		float x_coord();
		
		float y_coord();

		float z_coord();

		float rotate_angle(); // return only ANGLE

		char get_type();

		char get_next_type();

		float get_right_border();

		float get_left_border();

		float get_down_border(); 

		void set_x_coord(float new_x);
		
		void set_y_coord(float new_y);

		void set_z_coord(float new_z);

		void set_type(char new_type);

		void set_rotate_angle(float new_angle);

		void Draw();
		
		void init_figure();

		void rotate(float angle_flo);

		void place();

};



//Figure next_figure_type = Figure(0,0,0,'O');


float Figure::x_coord() {
	return x;
}
		
float Figure::y_coord() {
	return y;
}

float Figure::z_coord() {
	return z;
}

float Figure::rotate_angle(){
	return rot_angle;
}

char Figure::get_type(){
	return type;
}

char Figure::get_next_type(){
	return next_type;
}


void Figure::set_x_coord(float new_x){
	
	float delta = x - new_x;

	for (int i = 0; i < 4; i++)
	{
		x_blocks[i] -= delta;
	}
	x = new_x;
	//x_blocks[0]=new_x;
}
		
void Figure::set_y_coord(float new_y){
	
	float delta = y - new_y;
	for (int i = 0; i < 4; i++)
	{
		y_blocks[i] -= delta;
	}
	y = new_y;
	//y_blocks[0]=new_y;
}

void Figure::set_z_coord(float new_z){
	z =  new_z;
}

void Figure::set_type(char new_type)
{
	type = new_type;
}

void Figure::set_rotate_angle(float new_angle){
	
	rot_angle = new_angle;

}

void Figure::Draw(){

	glColor3f(1,1,1);
	switch (type) {  // Change the color for the specific FIGURE
		case 'L':
			
			curr_texture = 0;
			break;
		case 'J':
			
			curr_texture = 6;
			break;
		case 'T':
			
			curr_texture = 3;
			break;
		case 'O':
			
			curr_texture = 4;
			break;
		case 'Z':
			
			curr_texture = 2;
			break;
		case 'S':
			
			curr_texture =1;
			break;
		case 'I':
			
			curr_texture =5;
			break;
	}
	for(int i=0;i<4;i++)
	{
		glPushMatrix();
		glTranslatef(x_blocks[i],y_blocks[i],z);  // points from 0 to 3
		glutSolidCube_own(0.1,_textureId[curr_texture]);
		glPopMatrix();
	}
	glColor3f(0.5,0.5,0.5); // return to the default GREY color	
}

void Figure::init_figure(){
	switch(type){
		case 'L':
		
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x+BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x; y_blocks[2]=y+BOX_SIZE;
			x_blocks[3]=x; y_blocks[3]=y+2*BOX_SIZE;

			break;
		
		case 'I':
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x-BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x+BOX_SIZE; y_blocks[2]=y;
			x_blocks[3]=x+2*BOX_SIZE; y_blocks[3]=y;
			break;

		case 'S':
			
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x-BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x; y_blocks[2]=y+BOX_SIZE;
			x_blocks[3]=x+BOX_SIZE; y_blocks[3]=y+BOX_SIZE;
			break;

		case 'Z':
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x+BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x; y_blocks[2]=y+BOX_SIZE;
			x_blocks[3]=x-BOX_SIZE; y_blocks[3]=y+BOX_SIZE;
			break;

		case 'O':
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x-BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x-BOX_SIZE; y_blocks[2]=y+BOX_SIZE;
			x_blocks[3]=x; y_blocks[3]=y+BOX_SIZE;
			break;

		case 'J':
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x-BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x; y_blocks[2]=y+BOX_SIZE;
			x_blocks[3]=x; y_blocks[3]=y+2*BOX_SIZE;
			break;

		case 'T':
			x_blocks[0]=x; y_blocks[0]=y;
			x_blocks[1]=x-BOX_SIZE; y_blocks[1]=y;
			x_blocks[2]=x+BOX_SIZE; y_blocks[2]=y;
			x_blocks[3]=x; y_blocks[3]=y+BOX_SIZE;
			break;
	}

}

// Change angle of figure with amount of "angle_flo" degrees
void Figure::rotate(float angle_flo){
	
	int angle = (int)angle_flo;
	
	float tmp_x = 0.0;
	float tmp_y = 0.0;
	float tmp_x0 = 0.0;
	float tmp_y0 = 0.0;
	
	x_blocks[0] = x;
	y_blocks[0] = y;

	tmp_x0 = x; 
	tmp_y0 = y;

	for (int i=0; i<4;i++)
	{
		tmp_x = x_blocks[i];
		tmp_y = y_blocks[i];
		
		x_blocks[i]= (tmp_y - tmp_y0) + tmp_x0; 
		y_blocks[i]= -(tmp_x - tmp_x0) + tmp_y0;
	}

	rot_angle += angle_flo;
	
	if(rot_angle>=360.0) rot_angle=0.0;

}

void Figure::place(){
		
	x = 1.0; y = 1.9; z = 0.0;

	type = next_type;
	next_type = generate_type();

	init_figure();

}


