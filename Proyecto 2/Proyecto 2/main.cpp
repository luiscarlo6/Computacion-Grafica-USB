#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "objeto.h"
#include "bloque.h"

using namespace std;

#define DEF_maxSteps 51.0f
#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	DEF_maxSteps
#define DEF_floorGridZSteps	DEF_maxSteps

// creacion de los objetos
bloque total[30]; // Posicion de los morados: 1, 3, 11, 15, 19, 28

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
		glOrtho(-DEF_maxSteps*aspectratio,DEF_maxSteps*aspectratio,-DEF_maxSteps,DEF_maxSteps,1.0,10.0);
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
	ejesCoordenada(50);

	//variables para llevar la suma
	float x=-35.0;
	float y=35.0;

	glPushMatrix();
		// Push del borde marron
		glPushMatrix();
			glColor3f(0.45f,0.26f,0.10f);
			glLineWidth(5.0f);
			glPushMatrix();
				dibujarBorde();
			glPopMatrix();
		glPopMatrix();

		// Push para dibujar los cuadrados
		glPushMatrix();
			for (int i = 0; i < 30; i++)
			{
				if ((i==1)||(i==3)||(i==11)||(i==15)||(i==19)||(i==28)){
					glColor3f(1.0f,0.0f,1.0f);
					total[i].setXY(x,y);
					total[i].dibujar(x,y);
				}
				else{
					glColor3f(1.0f,0.5f,0.0f);
					total[i].setXY(x,y);
					total[i].dibujar(x,y);
				}
				x = x + 10.0;
				if ((i==5)||(i==11)||(i==17)||(i==23)){
					y = y - 5.0;
					if ((i==11)||(i==23)){
						x = -35.0;
					}
					else{
						x = -40.0;
					}
				}
			}
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

int main (int argc, char** argv) {

	for (int i = 0; i < 30; i++)
	{
		bloque b = bloque(2.0,7.0);
		total[i] = b;
	}

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Space Invaders");

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();
	return 0;

}