#include <ctime>   // For srand() and time() functions!
#include <cstdlib> // For srand() and time() functions! 

using namespace std;

int figure_count = 0;
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
		float rot_angle;
		
		

	public:
		
		Figure* prev;
		Figure* next;


		Figure(float x1, float y1, float z1, char type1, Figure* current){
			x = x1;
			y = y1;
			z = z1;
			type = type1;
			next = NULL;

			if(figure_count!=0) {
				prev = current;
			}
			else
			{
				prev = NULL;
			}

			rot_angle = 0.0;

			figure_count++;
		}
		
		float x_coord();
		
		float y_coord();

		float z_coord();

		float rotate_angle();

		void set_x_coord(float new_x);
		
		void set_y_coord(float new_y);

		void set_z_coord(float new_z);

		void set_rotate_angle(float new_angle);

		char figure_type();

		void Draw();

		void Draw_static();
		
		void Draw_L();
		
		void Draw_I();
		
		void Draw_S();
		
		void Draw_Z();
		
		void Draw_T();
		
		void Draw_J();
		
		void Draw_O();

		void init_figure();

		void move();

		void place(float bottom, Figure* &current);

};


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

void Figure::set_x_coord(float new_x){
	x =  new_x;	
}
		
void Figure::set_y_coord(float new_y){
	y =  new_y;
}

void Figure::set_z_coord(float new_z){
	z =  new_z;
}

void Figure::set_rotate_angle(float new_angle){
	rot_angle = new_angle;
}

char Figure::figure_type(){
	return type;
}

void Figure::Draw(){

	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(rot_angle,0,0,1);
	switch (type) {
		case 'L':
			Draw_L();
			break;
		case 'J':
			Draw_J();
			break;
		case 'T':
			Draw_T();
			break;
		case 'O':
			Draw_O();
			break;
		case 'Z':
			Draw_Z();
			break;
		case 'S':
			Draw_S();
			break;
		case 'I':
			Draw_I();
			break;
	}
	glPopMatrix();

	if(prev!=NULL) (*prev).Draw();
	
}

void Figure::Draw_static(){
	Draw();

	if(next!=NULL) (*prev).Draw();
}

void Figure::Draw_L(){

	
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0,0.1,0);
	glutSolidCube(0.1);
}
void Figure::Draw_I(){
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
}

void Figure::Draw_S(){
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0,0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
}

void Figure::Draw_Z(){
	glTranslatef(0,0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0,-0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
}

void Figure::Draw_T(){
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0,0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,-0.1,0);
	glutSolidCube(0.1);
}

void Figure::Draw_J(){
	glTranslatef(0,0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0,-0.1,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,0,0);
	glutSolidCube(0.1);
}

void Figure::Draw_O(){
	
	glutSolidCube(0.1);
	glTranslatef(0.1,0.1,0);
	glutSolidCube(0.1);
	glTranslatef(-0.1,0,0);
	glutSolidCube(0.1);
	glTranslatef(0.1,-0.1,0);
	glutSolidCube(0.1);

}

void Figure::init_figure(){
	
}

void Figure::move(){

}

void Figure::place(float bottom, Figure* &current){
	
	//Figure* tmp = current;
	//delete tmp;  // Problem with DELETING. TODO!
	
	current = new Figure(0,0,0,generate_type(),current);
}


