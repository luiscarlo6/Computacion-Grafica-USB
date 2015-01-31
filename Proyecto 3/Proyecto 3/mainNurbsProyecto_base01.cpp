// Cubica

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <math.h> 

using namespace std;

#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0
#define PI 3.14159265358979323846

GLUnurbsObj *theNurb;
float time = 1.0;
GLfloat theCtrlPoints[21][21][3];
GLfloat A;
GLfloat centro[3] = {0.001f,0.0f,0.001f};
GLfloat L;
GLfloat S;
GLfloat D;
bool pausa;
bool ola;
float theKnots[25];  

void inicializarKnots(){
	// Para hacer una curva clamped los primeros 4 elementos del vector knot son 0.0 y los ultimos 4 1.0
	int i;
	float p = 1.0/18.0;//factor de crecimiento del vector, pues los elementos deben ser crecientes de 0 a 1.
	for(i = 0; i < 25; i++) {
		if (i < 4) {
			theKnots[i] = 0.0;
		} else if (i > 20) {
			theKnots[i] = 1.0;
		} else {
			theKnots[i] = p;
			p = p + 1.0/18.0;
		}
	}
}

void changeViewport(int w, int h) {
	
	if (h==0)
		h=1;

	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode (GL_MODELVIEW);

}

void init_surface() {
	
	int f,c;
	int z = 10;
	for (f = 0; f < 21 ; f++) {
		int x = 10;
		for (c = 0; c < 21; c++) {
			theCtrlPoints[f][c][0] = x;
			theCtrlPoints[f][c][1] = 0.0;
			theCtrlPoints[f][c][2] = z;
			x--;
		}
		z--;
	}
	
}

void init(){



   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_AUTO_NORMAL);
   glEnable(GL_NORMALIZE);

   init_surface();

   theNurb = gluNewNurbsRenderer();
   gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 15.0);
   gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);

	A = 0.2f;
	L = 3.0f;
	S = -0.1f;
	D = 0.0f;
	
	pausa = false;
	ola = true;

}

void circularWaves(float t){
	GLfloat Gx, Gz; //componentes del vector Di de la Equation 1
	GLfloat dotProduct;
	GLfloat distCentro;
	GLfloat w;
	GLfloat phase_const;
	for (int i = 0; i<21;i++)
	{
		for (int j = 0; j<21;j++){
			distCentro = sqrt(pow(theCtrlPoints[i][j][0]-centro[0],2) + pow(theCtrlPoints[i][j][2]-centro[2],2));
			Gx = ((theCtrlPoints[i][j][0]-centro[0])/distCentro);
			Gz = ((theCtrlPoints[i][j][2]-centro[2])/distCentro);

			//Producto Punto de Di con el punto (x,z)
			dotProduct = Gx * theCtrlPoints[i][j][0] + Gz * theCtrlPoints[i][j][2];
			w = (2*PI)/L;

			phase_const = S * (2*PI)/L;

			if (ola)
				theCtrlPoints[i][j][1] = A * sin(dotProduct*w + t*phase_const);	
			else
				theCtrlPoints[i][j][1] = 0;
		}
	}
	A = A - D;
}

void animacion(int value) {
	
	glutTimerFunc(10,animacion,1);
	glutPostRedisplay();
	if (pausa)
		return;		
	circularWaves(time);
	time += 0.5;

}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a':
			A+=0.1;
			break;
		case 'z':
			A-=0.1;
			break;
		case 's':
			L+=0.1;
			break;
		case 'x':
			L-=0.1;
			break;
		case 'd':
			S+=0.1;
			break;
		case 'c':
			S-=0.1;
			break;
		case 'f':
			D+=0.01;
			break;
		case 'v':
			D-=0.01;
			break;
		case 'q':
			centro[0]+=0.1;
			break;
		case 'w':
			centro[0]-=0.1;
			break;
		case 'e':
			centro[2]+=0.1;
			break;
		case 'r':
			centro[2]-=0.1;
			break;
		case '1':
			pausa = !pausa;
			break;
		case '3':
			ola = !ola;
			break;
		case 27:             
			exit (0);
			break;
	}
  cout<<"Valores de las variables"<<endl
	  <<"-----------------------------------------"<<endl<<endl
	  <<"Amplitud de la ola <A> = "<<A<<endl
	  <<"Longitud de la ola <L> = "<<L<<endl
	  <<"Velocidad = "<<S<<endl
	  <<"Centro = ("<<centro[0]<<", "<<centro[2]<<")"<<endl
	  <<"Decaimiento = "<<D<<endl
	  <<"-----------------------------------------"<<endl;
}

void controlPoints()
{
	int i,j;
	glPointSize(5.0);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (i = 0; i <21; i++) {
		for (j = 0; j < 21; j++) {
			if (i-10==floor(centro[2]+0.5) && j-10==floor(centro[0]+0.5))
				//glVertex3f(theCtrlPoints[i][j][0], 	theCtrlPoints[i][j][1], theCtrlPoints[i][j][2]);
				glColor3f(1.0f,0.0f,0.0f);
			else
				glColor3f(1.0f,1.0f,0.0f);
			glVertex3f(-theCtrlPoints[i][j][0], 	theCtrlPoints[i][j][1], -theCtrlPoints[i][j][2]);
		}
	}
	glEnd();
	glEnable(GL_LIGHTING);


}

void LuzMaterial()
{
	// Luz y material

	GLfloat mat_diffuse[] = { 0.6, 0.6, 0.9, 1.0 };
	GLfloat mat_specular[] = { 0.8, 0.8, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 60.0 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


	GLfloat light_ambient[] = { 0.0, 0.0, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
	GLfloat light_position[] = { -10.0, 5.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); 
}

void render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();                       
	gluLookAt (25.0, 12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	LuzMaterial();
	//renderGrid();
	
	//Suaviza las lineas
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );	

	
	glPushMatrix();

	gluBeginSurface(theNurb);
    
	gluNurbsSurface(theNurb, 
                   25, theKnots, 25, theKnots,
                   21 * 3, 3, &theCtrlPoints[0][0][0], 
                   4, 4, GL_MAP2_VERTEX_3);
	/*

		No cambien los numeros de la funcion, solo deben de poner los nombres de las variables correspondiente.
		
	*/


	gluEndSurface(theNurb);
	
	glPopMatrix();
	
	
	/* Muestra los puntos de control */
	
	controlPoints();


	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glutSwapBuffers();
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(960,540);

	glutCreateWindow("Proyecto 3");

	init ();
	inicializarKnots();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc (Keyboard);
	glutTimerFunc(10,animacion,1);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	

	glutMainLoop();
	return 0;

}
