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
#define B 0x100
#define BM 0xff
#define N 0x1000

GLUnurbsObj *theNurb;
float time = 1.0;
GLfloat theCtrlPoints[21][21][3];
GLfloat A;
GLfloat centro[3] = {0.001f,0.0f,0.001f};
GLfloat L;
GLfloat S;
GLfloat D;
GLfloat Amplitud_Ruido;
GLfloat Offset_ruido;
GLfloat Altura_Ruido;
GLfloat factorTurb;
GLfloat factorCurva;
GLfloat traslaCurva;
bool pausa;
bool ola;
bool ruido;
float theKnots[25];

static int p[B + B + 2];
static float g2[B + B + 2][2];
static int start = 1;

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)\
	t = vec[i] + N;\
	b0 = ((int)t) & BM;\
	b1 = (b0+1) & BM;\
	r0 = t - (int)t;\
	r1 = r0 - 1.;

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

static void normalize2(GLfloat v[2])
{
	float s;

	s = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
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

	A = 0.5f;
	L = 3.0f;
	S = -0.1f;
	D = 0.0f;

	Amplitud_Ruido = 30.0f;
	Offset_ruido = 0.5f;
	Altura_Ruido = 1.0f;
	factorTurb = 16.0f;

	factorCurva = 0.0f;
	traslaCurva = 0.0f;
	
	ruido = false;
	pausa = false;
	ola = true;

	int i, j, k;

	for (i = 0 ; i < B ; i++) {
		p[i] = i;

		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (float)((rand() % (B + B)) - B) / B;
		normalize2(g2[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % B];
		p[j] = k;
	}

	for (i = 0 ; i < B + 2 ; i++) {
		p[B + i] = p[i];
		for (j = 0 ; j < 2 ; j++)
			g2[B + i][j] = g2[i][j];
	}
}

GLfloat noise2(GLfloat vec[2])
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v;
	int i, j;

	if (start) {
		start = 0;
		init();
	}

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	return lerp(sy, a, b);
}

GLfloat turbulence(GLfloat x, GLfloat y, GLfloat size)
{
    GLfloat value = 0.0, initialSize = size;
	GLfloat valor[2];

    while(size >= 1)
    {
		valor[0] = x / size;
		valor[1]= y / size;
		value += noise2(valor) * size;
        size /= 2.0;
    }
    
    return(128.0 * value / initialSize);
}
void circularWaves(float t){
	GLfloat Gx, Gz; //componentes del vector Di de la Equation 1
	GLfloat dotProduct;
	GLfloat distCentro;
	GLfloat w;
	GLfloat phase_const;
	GLfloat n_noise[2];
	GLfloat noise=0.0f;
	GLfloat decaimiento;
	GLfloat parabola;
	for (int i = 0; i<21;i++)
	{
		for (int j = 0; j<21;j++){
			distCentro = sqrt(pow(theCtrlPoints[i][j][0]-centro[0],2) + pow(theCtrlPoints[i][j][2]-centro[2],2));
			Gx = ((theCtrlPoints[i][j][0]-centro[0])/distCentro);
			Gz = ((theCtrlPoints[i][j][2]-centro[2])/distCentro);

			decaimiento= 1/(distCentro*D +1);
			//Producto Punto de Di con el punto (x,z)
			dotProduct = Gx * theCtrlPoints[i][j][0] + Gz * theCtrlPoints[i][j][2];
			w = (2*PI)/L;

			phase_const = S * (2*PI)/L;

			parabola = pow(theCtrlPoints[i][j][2],2)*factorCurva;
			if (ruido)
			{
				n_noise[0] = theCtrlPoints[i][j][0]*Amplitud_Ruido + Offset_ruido;
				n_noise[1] = theCtrlPoints[i][j][2]*Amplitud_Ruido + Offset_ruido;
				noise = Altura_Ruido * 0.005 * turbulence(n_noise[0],n_noise[1],factorTurb);
			}

			if (ola)
				theCtrlPoints[i][j][1] = (A * sin(dotProduct*w + t*phase_const) + noise) * decaimiento + parabola;
			else
				theCtrlPoints[i][j][1] = 0 + noise+parabola;
		}
	}
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
		case 'g':
			Amplitud_Ruido+=0.01;
			break;
		case 'b':
			Amplitud_Ruido-=0.01;
			break;
		case 'h':
			Offset_ruido+=0.01;
			break;
		case 'n':
			Offset_ruido-=0.01;
			break;
		case 'j':
			Altura_Ruido+=0.01;
			break;
		case 'm':
			Altura_Ruido-=0.01;
			break;
		case 't':
			factorTurb+=1.0;
			break;
		case 'y':
			factorTurb-=1.0;
			break;
		case 'u':
			factorCurva+=0.001;
			break;
		case 'i':
			factorCurva-=0.001;
			break;
		case 'o':
			traslaCurva+=0.1;
			break;
		case 'l':
			traslaCurva-=0.1;
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
		case '2':
			ruido = !ruido;
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
	  <<"Amplitud de la ola <A/Z> = "<<A<<endl
	  <<"Longitud de la ola <S/X> = "<<L<<endl
	  <<"Velocidad <D/C> = "<<S<<endl
	  <<"Centro <Q/W/E/R>= ("<<centro[0]<<", "<<centro[2]<<")"<<endl
	  <<"Decaimiento = <F/V>"<<D<<endl
	  <<"Amplitud Ruido <G/B> = "<<Amplitud_Ruido<<endl
	  <<"Offset Ruido <H/N> = "<<Offset_ruido<<endl
	  <<"Altura Ruido <J/M> = "<<Altura_Ruido<<endl
	  <<"Factor Turbulencia <T/Y>= "<<factorTurb<<endl
	  <<"Factor Curvatura = "<<factorCurva<<endl
	  <<"Traslacion Curvatura = "<<traslaCurva<<endl
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
			glVertex3f(-theCtrlPoints[i][j][0], theCtrlPoints[i][j][1], -theCtrlPoints[i][j][2]);
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
	
	//controlPoints();


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
