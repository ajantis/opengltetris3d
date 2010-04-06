class Figure {
	private:
		float x; 
		float y; 
		float z; 
		char type;

	public:
		
		Figure(float x1, float y1, float z1, char type1){
			x = x1;
			y = y1;
			z = z1;
			type = type1;	
		}
		
		float x_coord();
		
		float y_coord();

		float z_coord();

		void set_x_coord(float new_x);
		
		void set_y_coord(float new_y);

		void set_z_coord(float new_z);

		char figure_type();

		void Draw();
		
		void Draw_L();
		
		void Draw_I();
		
		void Draw_S();
		
		void Draw_Z();
		
		void Draw_T();
		
		void Draw_J();
		
		void Draw_O();

		void init_figure();

		void move();

		void place(float bottom);

};

//Figure(float x1, float y1, float z1, char type1) 

float Figure::x_coord() {
	return x;
}
		
float Figure::y_coord() {
	return y;
}

float Figure::z_coord() {
	return z;
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

char Figure::figure_type(){
	return type;
}

void Figure::Draw(){
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
void Figure::place(float bottom){
	
		/*Figure figure2 = Figure (0,5.5,0,'T'); /// MAKE RANDOM!!!!
		figures_list.push_back(figure2);
		current = &figure2;*/
		current = &Figure(0,0,0,'T');
}

