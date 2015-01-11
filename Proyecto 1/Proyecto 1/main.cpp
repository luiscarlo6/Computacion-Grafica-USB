#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "objetos.h"

using namespace std;

#define DEF_maxSteps 10.0f
#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	DEF_maxSteps
#define DEF_floorGridZSteps	DEF_maxSteps

objetos l = objetos(20.0, -80.0, -100.0,-1.0, -8.0, 0.0);
//objetos l = objetos();

void changeViewport(int w, int h) {
	float aspectratio;
	if (h==0)
		h=1;	
	glViewport(0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	
	aspectratio = (float) w / (float) h;

	if (w<=h) {
		
		glOrtho(-DEF_maxSteps,DEF_maxSteps,-DEF_maxSteps/aspectratio,DEF_maxSteps/aspectratio,1.0,50.0);

	}else {

		glOrtho(-DEF_maxSteps*aspectratio,DEF_maxSteps*aspectratio,-DEF_maxSteps,DEF_maxSteps,1.0,50.0);

	}


	glMatrixMode (GL_MODELVIEW);
}

void renderGrid(){
	int loopX, loopZ;
	GLfloat zExtent, xExtent, xLocal, zLocal;

	glPushMatrix(); 
    glColor3f( 0.8f, 0.8f, 0.8f);
    glBegin( GL_LINES );
    zExtent = DEF_floorGridScale * DEF_floorGridZSteps;
    for(loopX = -DEF_floorGridXSteps; loopX <= DEF_floorGridXSteps; loopX++ )
	{
	xLocal = DEF_floorGridScale * loopX;
	glVertex3f( xLocal, -zExtent, 0.0f );
	glVertex3f( xLocal, zExtent,  0.0f );
	}
    xExtent = DEF_floorGridScale * DEF_floorGridXSteps;
    for(loopZ = -DEF_floorGridZSteps; loopZ <= DEF_floorGridZSteps; loopZ++ )
	{
	zLocal = DEF_floorGridScale * loopZ;
	glVertex3f( -xExtent, zLocal, 0.0f );
	glVertex3f(  xExtent, zLocal, 0.0f );
	}
    glEnd();
    glPopMatrix();
}

void ejesCoordenada(float limite) {

	glLineWidth(2.5);

	glBegin(GL_LINES);

		glColor3f(1.0,0.0,0.0);

		glVertex2f(0,limite);

		glVertex2f(0,-limite);

		glColor3f(0.0,0.0,1.0);

		glVertex2f(limite,0);

		glVertex2f(-limite,0);

	glEnd();

	glLineWidth(1.5);

	int i;

	glColor3f(0.0,1.0,0.0);

	glBegin(GL_LINES);

		for(i = -limite; i <=limite; i++){

			if (i!=0) {		

				if ((i%2)==0){	

					glVertex2f(i,0.4);

					glVertex2f(i,-0.4);

					glVertex2f(0.4,i);

					glVertex2f(-0.4,i);

				}else{

					glVertex2f(i,0.2);

					glVertex2f(i,-0.2);

					glVertex2f(0.2,i);

					glVertex2f(-0.2,i);

				}

			}

		}

 

	glEnd();

	glLineWidth(1.0);

}

void render(){
	//glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	gluLookAt (0.0, 0.0, DEF_maxSteps, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	/* Render Grid */
	//renderGrid();
	//ejesCoordenada(DEF_maxSteps);

	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );
	glEnable( GL_POINT_SMOOTH );
	l.dibujar();	
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
	switch(key){
		case 'z':
			l.setAnguloCInferior(l.getAnguloCInferior() - 10.0);
			render();
			break;
		case 'x':
			l.setAnguloCInferior(l.getAnguloCInferior() + 10.0);
			render();
			break;
		case 'a':
			l.setAnguloCCentral(l.getAnguloCCentral() - 10);
			render();
			break;
		case 's':
			l.setAnguloCCentral(l.getAnguloCCentral() + 10);
			render();
			break;
		case 'q':
			l.setAnguloCSuperior(l.getAnguloCSuperior() - 10);
			render();
			break;
		case 'w':
			l.setAnguloCSuperior(l.getAnguloCSuperior() + 10);
			render();
			break;
		case 'c':
			l.setXPatineta(l.getXPatineta() + 0.1);
			l.setAnguloRuedas(l.getAnguloRuedas() + 0.1*360/2*3.14159265358979323846*0.5);//Formula de longitud de Arco
			render();
			break;
		case 'v':
			l.setXPatineta(l.getXPatineta() - 0.1);
			l.setAnguloRuedas(l.getAnguloRuedas() - 0.1*360/2*3.14159265358979323846*0.5);
			render();
			break;
	}
}


int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Graficas I - Luiscarlo Rivera");

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc(teclado); 

	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();
	return 0;

}
