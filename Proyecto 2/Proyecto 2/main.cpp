#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "objeto.h"
#include "bloque.h"
#include "bala.h"

using namespace std;

#define DEF_maxSteps 50.0f
#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	DEF_maxSteps
#define DEF_floorGridZSteps	DEF_maxSteps

// creacion de los objetos
objeto o = objeto(2.0,2.0);
bloque b = bloque(-2.0,-2.0,1.0,3.0);
bala  d = bala(0.0,5.0,2.0);

void changeViewport(int w, int h) {
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectratio;
	aspectratio = (float) w / (float) h;
	if (w<=h){
		glOrtho(-1.0,1.0,-1.0/aspectratio,1.0/aspectratio,1.0,10.0);
	} else {
		// si cambias el xsteps debe concordar con el valor del aspectratio
		// si cambias el zsteps debe concordar con los valores bottom y top
		glOrtho(-51.0*aspectratio,51.0*aspectratio,-51.0,51.0,1.0,10.0);
	}
	glMatrixMode(GL_MODELVIEW);
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

// para dibujar el borde marron
void dibujarBorde(){
	glBegin(GL_LINE_LOOP);
		glVertex3f(-50.0f,50.0f,0.0f);
		glVertex3f(50.0f,50.0f,0.0f);
		glVertex3f(50.0f,-50.0f,0.0f);
		glVertex3f(-50.0f,-50.0f,0.0f);
	glEnd();
}

void render(){
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// esta funcion te localiza la camara en la consola
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

	//renderGrid();
	//ejesCoordenada(30);
	glColor3f(1.0f,1.0f,0.0f);	
	o.dibujar();
	b.dibujar();
	d.dibujar();
	
	glutSwapBuffers();
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Space Invaders");

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	//glutKeyboardFunc(teclado); 
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();
	return 0;

}