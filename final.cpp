//Sabeel Kazi | Computer Graphics | Project 2-2
#include <iostream>
#include <string> 
#include <array>
#include <GLUT/glut.h>
#include <math.h>

//variables for lighting
GLfloat pos[] = { -2, 4, 5, 1 };
GLfloat amb[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat front[] = { 0.7, 0.5, 0.1, 1.0 };
GLfloat back[] = { 0.4, 0.7, 0.1, 1.0 };
GLfloat spe[] = { 0.25, 0.25, 0.25, 1.0 };

int rotate = 1;										//storesnrotation angle
int rotateSpeed=1;									//increments the rotation angle
double fire[4] = {.10, .07, .25, -2.3};				//starts off in slow setting
int status = 1;										//stores the states based on the button keys
bool growing = true;								//variable for growing and slowing the propulsion
bool pauseFlag = false;								//flag fpr the pause state
bool fastFlag = false;								//flag for the fast state
bool slowFlag = true;								//f;ag for the slow state			

//provided durface color for all objects
void color(float r, float g, float b){
	GLfloat color[] = { r, g, b, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
}

//used ot generate random float for stars
float randomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//used to create cylinderas ofor the rocket parts
void cylinder(float bottomWidth, float topWidth, float height, float translate){
		glRotatef(270, 1, 0, 0);
		glTranslatef(0, 0, translate);
		GLUquadricObj *o = gluNewQuadric();
		gluCylinder(o, bottomWidth, topWidth, height, 70, 40);
}

//second cylinder class for the propulsors
void cylinder(float bottomWidth, float topWidth, float height, float translate1, float translate2, float translate3){
		glRotatef(90, -1, 0, 0);
		glTranslatef(translate1, translate2, translate3);
		GLUquadricObj *o = gluNewQuadric();
		gluCylinder(o, bottomWidth, topWidth, height, 70, 40);
}

//giant blu cylinder for the earth at lower left
void earth(){
		//render the blue planet earth at the corner of the image
	glPushMatrix();
		color(0, 47.0/255, 75.0/255);
		glRotatef(90, -1, 0, 0);
		glTranslatef(-2.0, 3.0, -4.5);
		GLUquadricObj *r = gluNewQuadric();
		gluSphere(r, 3.0, 70, 40);
	glPopMatrix();
}

//render a small star
void stars(float x, float y){
	//render the blue planet earth at the corner of the image
	glPushMatrix();
		color(1, 1, 1);
		glRotatef(90, -1, 0, 0);
		glTranslatef(x, 3.1, y);
		GLUquadricObj *r = gluNewQuadric();
		gluSphere(r, .01, 5, 5);
	glPopMatrix();
}

//code for the propulsion fire. made of a spehre and a cylinder
void propulsionFire(){
	glPushMatrix();
		color(1, 140.0/255, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0, -2.0);
		GLUquadricObj *x = gluNewQuadric();
		gluSphere(x, fire[0], 70, 40);
	glPopMatrix();

	glPushMatrix();
		color(1, 140.0/255, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0, fire[3]);
		GLUquadricObj *o = gluNewQuadric();
		gluCylinder(o, .01, fire[1], fire[2], 70, 40);
	glPopMatrix();
}

//code for the small thruster propulsors on end of rocket. to be used 4 gtimes
void propulsors(float translate1, float translate2){
		//Cylinder body 1 of propulsor
		glPushMatrix();
			color(0.50, 0.50, 0.50);
			cylinder(.12, .12, .75, translate1, translate2, -1.7);
		glPopMatrix();
		//cylinder body 2 of propulsors
		glPushMatrix();
			color(1, 69/255.0, 0);
			cylinder(.1201, .1201, .25, translate1, translate2, -1.5);
		glPopMatrix();
		//spherical top
		glPushMatrix();
			color(0, 0, 0);
			glRotatef(90, -1, 0, 0);
			glTranslatef(translate1, translate2, -0.95);
			GLUquadricObj *q = gluNewQuadric();
			gluSphere(q, .12, 70, 40);
		glPopMatrix();
		//flat aerodyanmic wings on the propulsor
}

//rocket is built in this function call, parts are from top to bottom
void rocket() {
	glPushMatrix();
		//cone head
		color(.90, .90, .90);
		cylinder(.05, .01, .50, 1.25);
	glPopMatrix();

	glPushMatrix();
		//cone head
		color(.90, .90, .90);
		cylinder(.25 , .10, .25, 1.0);
	glPopMatrix();
	
	//ship head peak sphere
	glPushMatrix();
		color(0, 0, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0, 1.25);
		GLUquadricObj *q = gluNewQuadric();
		gluSphere(q, .10, 70, 40);
	glPopMatrix();

	//produces the the rocket ship window
	glPushMatrix();
		color(135.0/255, 206.0/255, 250.0/255);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, -0.15, 0.75);
		GLUquadricObj *r = gluNewQuadric();
		gluSphere(r, .20, 70, 40);
	glPopMatrix();

	glPushMatrix();
		//Cylinder body 1 of ship orange
		color(1, 69/255.0, 0);
		cylinder(.255 , .255, 0.5, 0.5);
		
	glPopMatrix();

	glPushMatrix();
		//Cylinder body 2 of ship white
		color(1, 1, 1);
		cylinder(.25 , .25, 0.2, 0.30);
	glPopMatrix();

	glPushMatrix();
		//Cylinder body 3 of ship orange
		color(1, 69/255.0, 0);
		cylinder(.255 , .255, 0.3, 0.0);
	glPopMatrix();

	glPushMatrix();
		//Cylinder body 4 of ship grey
		color(0.50, 0.50, 0.50);
		cylinder(.25 , .25, 0.5, -0.5);
	glPopMatrix();

	glPushMatrix();
		//Cylinder body 4 of ship dark grey
		color(0.25, 0.25, 0.25);
		cylinder(.25 , .25, 1.0, -1.5);
	glPopMatrix();

	//cube1 on the side of the ship
	glPushMatrix();
		color(1, 69/255.0, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0.15, 0.75);
		GLdouble size= .25;
		glutSolidCube( size);
	glPopMatrix();

	//cube2 on the side of the ship
	glPushMatrix();
		color(1, 69/255.0, 0);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0.15, 0.15);
		GLdouble size2= .25;
		glutSolidCube(size2);
	glPopMatrix();

	//cube3 on the side of the ship
	glPushMatrix();
		color(0.50, 0.50, 0.50);
		glRotatef(90, -1, 0, 0);
		glTranslatef(0, 0.15, -0.3);
		GLdouble size3= .25;
		glutSolidCube(size3);
	glPopMatrix();

	//propulsor1 on on right
	glPushMatrix();
		propulsors(.25, 0);
	glPopMatrix();

	//propulsor2 on on left
	glPushMatrix();
		propulsors(-0.25, 0);
	glPopMatrix();

	//propulsor3 on the back
	glPushMatrix();
		propulsors(0, 0.25);
	glPopMatrix();

	//propulsor4 on the front
	glPushMatrix();
		propulsors(0, -0.25);
	glPopMatrix();
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render the star in a grid randomly, only if the animation is not paused
	if(pauseFlag == false){
		for(int i=-4.0; i < 4.0; i+= 1.0){
			for(int j=-3.0; j < 4.0; j+=1.0){
				glPushMatrix();
					stars(randomFloat(-4.0, 4.0), randomFloat(-3.0, 4.0));
				glPopMatrix();
			}
		}
	}

	//render the earth
	glPushMatrix();	
		earth();
	glPopMatrix();

	//if the animation is not paused, then show the propulsion animation
	if(pauseFlag == false){
		//render the fire propulsion stuff
		glPushMatrix();
			glRotatef(30, 0, 0, -1);
			propulsionFire();
		glPopMatrix();
	}

	//render the rocket and its rotation, tilited 30 degrees to the right and rotated on its x-axis
	glPushMatrix();
		glRotatef(30, 0, 0, -1);
		glTranslatef(0, 0, 0); // move back to focus of gluLookAt
		glRotatef(rotate, 0, 1 , 0); //  rotate around center
		glTranslatef(0, 0, 0); //move object to center
		rocket();	
	glPopMatrix();

	glutSwapBuffers();
}

void idle() {
	//rotate the ship on display
	rotate = (rotate + rotateSpeed) % 360 ;

	//if the animation is not paused, then show the propulsion animation
	if(pauseFlag == false){
		//case for the natural slow state
		if(slowFlag == true) {
			//flame gets bigger and smaller when it reaches min and max
			if( fire[0] > .15) growing = false;
			if( fire[0] < .10) growing = true;

			if(growing == true) {fire[0] += .002;} else if (growing == false) { fire[0] -= .002;}
			if(growing == true) {fire[1] += .002;} else if (growing == false) { fire[1] -= .002;}
		}
		//case for the speed state
		else if(fastFlag == true){
			//flame gets bigger and smaller when it reaches min and max
			if( fire[0] > .20) growing = false;
			if( fire[0] < .15) growing = true;

			if(growing == true) {fire[0] += .005;} else if (growing == false) { fire[0] -= .005;}
			if(growing == true) {fire[1] += .005;} else if (growing == false) { fire[1] -= .005;}
		}
	}

	glutPostRedisplay();
}

//function defines the flags for each state
//3 states are paused, slow and fast
void state(){
	//paused state
	if(status==0){
			fastFlag=false;
			slowFlag=false;
			pauseFlag=true;
			rotateSpeed=0;
	}
	//slow state
	else if(status==1){ 
			fastFlag=false;
			slowFlag=true;
			pauseFlag=false ;
			rotateSpeed=1;
			double fire[4] = {.10, .07, .25, -2.3};
	}
	//fast state
	else if(status==2){
			fastFlag=true;
			slowFlag=false;
			pauseFlag=false ;
			rotateSpeed=10;
			double fire[4] = {.15, .12, .50, -3.0};
	}
}

void keyPressed (unsigned char key, int x, int y) { 
    //handle r button press for interpolation
    if(key == 'p'){
		status = 0;
		state();
    }
	//handle minus pressed for slowing down the animation
	else if(key == '-'){
		if(status==0) {/*do nothing*/}
		else {status--;}
		state();
    }
    //handle plus press for speeding up the animation
    else if(key == '+'){
		if(status==2) {/*do nothing*/}
		else {status++;}
		state();
    }
	//handle r press for resetting the animeation from any of the states
	else if(key == 'r'){
		status = 1;
		state();
    }

    glutPostRedisplay();
}  

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(1000, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Shuttle in Space | Project 3");
	glClearColor(.1, .1, .1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1.0, 2, 16);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, front);
	glMaterialfv(GL_BACK, GL_AMBIENT_AND_DIFFUSE, back);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 75);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0, 0, -5);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyPressed);
	glutIdleFunc(idle);
	glutMainLoop();
}
