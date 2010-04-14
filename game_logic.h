bool map[22][22];
char map_color[22][22];


void init_map();
void draw_map();

float convert_x_from_index(int index);
float convert_y_from_index(int index);

int convert_x_to_index(float y);
int convert_y_to_index(float y);

int points2 = 0; // Game points

void clear_from_map(int row){
	
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
	points2+=100;
}

bool check_map()
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
			
		}
		count = 0;
	}

	return 0;
}

void draw_map(){

	int curr_texture_map = 0;
	glColor3f(0.5,0.5,0.5); // Grey
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

				glColor3f(1,1,1);
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
							glColor3f(0.5,0.5,0.5);
							curr_texture_map = 2;
							break;
							
				}
				
				glutSolidCube_own(0.1,_textureId[curr_texture_map]);
				glColor3f(0.5,0.5,0.5);
				curr_texture_map = 2;
				
			}
			glPopMatrix();
		}
	}

	glPopMatrix();
}

void init_map(){
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

// For multiple games - TO DO!
class Game {
	private:
	public:
};


float convert_x_from_index(int index){
	
	float x = 0.0;
	if((index<10) && (index>0)) x = index*0.1 + 0.1;
	else x = index*0.1;
	
	return x;
}

float convert_y_from_index(int index){
	
	float y = -(index*0.1) + 2.0;
	
	return y;

}

int convert_x_to_index(float x){
	
	int index = x*10;
	
	return index;
}

int convert_y_to_index(float y){

	int index = 0;

	index = (2.0-y)*10;


	
	return index;

}
