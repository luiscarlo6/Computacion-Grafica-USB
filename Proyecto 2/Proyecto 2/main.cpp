#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GL\glut.h>
#include <iostream>
#include <list>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "objeto.h"
#include "bloque.h"
#include "bala.h"
#include "nave.h"
using namespace std;

#define DEF_maxSteps 51.0f
#define DEF_floorGridScale	1.0f
#define DEF_floorGridXSteps	DEF_maxSteps
#define DEF_floorGridZSteps	DEF_maxSteps

// creacion de los objetos
bloque total[30]; // Bloques enemigos. Posicion de los morados: 1, 3, 11, 15, 19, 28
bloque defensa[24];
nave jugadores[2]; 
list<bala> balasbuenas,balasmalas;
bala esfera;
float vel = 1.0;
float despl = 0.0;
int tiempo = 25;
int tiempoMovEnemigos = 500;
int tiempoDisparos = 5;
int tiempoDispEnemigos = 1;
int tiempoNaveEnemiga = 1;
int score = 0;
char quote[50], str[20]; // para dibujar el texto
bool fin = false; //saber si es fin de juego
bool gano = false; // saber si gano

bool* estadoTeclas = new bool[256]; // Crea un arreglo de booleanos de longitud 256 (0-255)
bool* keySpecialStates = new bool[246];

void seleccionTecla(unsigned char tecla){
	// la nave del jugador dispara las esferas
	if (tecla==' '){		
		esfera = bala(0.5);
		// se le asigna a la esfera la posicion del jugador
		esfera.setXY(jugadores[1].getX(),jugadores[1].getY());
		balasbuenas.push_back(esfera);
	}
	glutPostRedisplay(); // funcion para actualizar el display al momento de un cambio
 }

void teclaPresionada(unsigned char tecla, int x, int y){
	estadoTeclas[tecla] = true; // Coloca el estado actual de la tecla presionada
	seleccionTecla(tecla);
 }

void teclaLiberada (unsigned char tecla, int x, int y) {
	 estadoTeclas[tecla] = false; // Coloca el estado actual de la tecla no presionada
 }

void keySpecialOperations(void) {
	// If the left arrow key has been pressed  
	if (keySpecialStates[GLUT_KEY_LEFT]) {
		// Perform left arrow key operations
		jugadores[1].setXY(jugadores[1].getX()-1,jugadores[1].getY());
	} 
	if (keySpecialStates[GLUT_KEY_RIGHT]) {
		// Perform right arrow key operations
		jugadores[1].setXY(jugadores[1].getX()+1,jugadores[1].getY());
	} 
	glutPostRedisplay(); // funcion para actualizar el display al momento de un cambio
}  

void keySpecial (int key, int x, int y) {
	keySpecialStates[key] = true;
	keySpecialOperations();
}

void keySpecialUp (int key, int x, int y) {
	keySpecialStates[key] = false;
}

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

// para dibujar el borde marron
void dibujarBorde(){
	glBegin(GL_LINE_LOOP);
		glVertex3f(-50.0f,50.0f,0.0f);
		glVertex3f(50.0f,50.0f,0.0f);
		glVertex3f(50.0f,-50.0f,0.0f);
		glVertex3f(-50.0f,-50.0f,0.0f);
	glEnd();
}

void textoPuntaje(){
	strcpy(quote,"");
	char copia[20];
	strcpy(copia,"Puntaje: ");
	// se actualiza el string
	sprintf(str, "%d", score); //para copiar el puntaje
	strncat(copia,str,(strlen(copia)+strlen(str)));
	strncpy(quote,copia,(strlen(copia)+strlen(str)));
}

void finalizarJuego(){
	fin = true;
	//glutTimerFunc(3000,exit,0);
}

void verifEnemigos(){
	bool seacabo = true;
	for (int i = 0; i < 30; i++)
	{
		seacabo = seacabo && !total[i].getExiste();
	}
	if (seacabo){
		gano = true;
		finalizarJuego();
	}
}

void verifColisiones()
{
	//enemigos con defensas y jugador
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 24; j++)
		{
			if (total[i].colisionConCuadrado(defensa[j])){
				defensa[j].setExiste(false);
				score-=30;
				textoPuntaje();
			}
		}
		if (total[i].colisionConNave(jugadores[1])){
			jugadores[1].setExiste(false);
			finalizarJuego();
		}
	}
	//balas del jugador con bloques, defensas y nave superior
	for (std::list<bala>::iterator it=balasbuenas.begin(); it != balasbuenas.end(); ++it){
		for (int i = 0; i < 24; i++)
		{
			if((*it).colisionConBloque(defensa[i])){
				defensa[i].setExiste(false);
				(*it).setExiste(false);
				score-=30;
				textoPuntaje();
			}
		}
		for (int i = 0; i < 30; i++)
		{
			if((*it).colisionConBloque(total[i])){
				(*it).setExiste(false);
				if(total[i].getMorado()||total[i].getDisparado()){
					if(!total[i].getDisparado()){
						total[i].setDisparado(true);
						total[i].setMorado(false);
					}
					else{
						total[i].setExiste(false);
						score += 200;
						textoPuntaje();
					}
				}
				else{
					total[i].setExiste(false);
					score+=100;
					textoPuntaje();
				}
			}
		}
		for (std::list<bala>::iterator it2=balasmalas.begin(); it2 != balasmalas.end(); ++it2){		
			if((*it).colisionConBala((*it2))){
				(*it2).setExiste(false);
				(*it).setExiste(false);				
			}
		}


		if ((*it).colisionConNave(jugadores[0])){
			jugadores[0].setExiste(false);
			(*it).setExiste(false);
			score+=300;
			textoPuntaje();
		}
	}

	//balas enemigas con defensas y jugador
	for (std::list<bala>::iterator it=balasmalas.begin(); it != balasmalas.end(); ++it){		
		for (int i = 0; i < 24; i++)
		{
			if((*it).colisionConBloque(defensa[i])){
				defensa[i].setExiste(false);
				(*it).setExiste(false);
				score-=30;
				textoPuntaje();
			}
		}
		if ((*it).colisionConNave(jugadores[1])){
			jugadores[1].setExiste(false);
			(*it).setExiste(false);
			finalizarJuego();
		}
	}
}

void render(){
	int lenghOfQuote,i;
	char finJuego[50],perdiste[50],ganaste[50];
	strcpy(finJuego,"Fin del juego.");
	strcpy(perdiste,"Perdiste.");
	strcpy(ganaste,"Ganaste.");
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	// esta funcion te localiza la camara en la consola
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

	//Push inicial
	glPushMatrix();
		// Push del borde marron
		glPushMatrix();
			glColor3f(0.45f,0.26f,0.10f);
			glLineWidth(5.0f);
			glPushMatrix();
				dibujarBorde();
			glPopMatrix();
		glPopMatrix();
		// Push para dibujar las letras del puntaje
		glPushMatrix();
			glTranslatef(-5.0f,45.0f,0.0f);
			glPushMatrix();
				glScalef(0.06f,0.04f,0.0f);
				for (i = 0; i < strlen(quote); i++)
				{
					glColor3f(1.0f,1.0f,0.0f);
					glutStrokeCharacter(GLUT_STROKE_ROMAN, quote[i]);
				}
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	if (fin==false){
		// Push inicial del objetos del juego
		glPushMatrix();
			// Push para dibujar los bloques enemigos
			glPushMatrix();
				for (int i = 0; i < 30; i++)
				{
					if (total[i].getMorado()){
						glColor3f(1.0f,0.0f,1.0f);
						total[i].dibujar();
					}
					else{
						glColor3f(1.0f,0.5f,0.0f);
						total[i].dibujar();
					}
				}
			glPopMatrix();
			// Push para dibujar los bloques defensa
			glPushMatrix();
				for (int i = 0; i < 24; i++)
				{
					glColor3f(0.36f,0.15f,0.10f);
					defensa[i].dibujar();
				}
			glPopMatrix();
			// Push para dibujar las naves
			glPushMatrix();
				for (int i = 0; i < 2; i++)
				{
					if ((i==0)){
						glColor3f(0.5f,0.5f,0.5f);
						jugadores[i].dibujar();
					}
					else{
						glColor3f(0.2f,0.65f,1.0f);
						jugadores[i].dibujar();
					}	
				}
			glPopMatrix();
			// Push para las balas buenas
			glPushMatrix();
					for (std::list<bala>::iterator it=balasbuenas.begin(); it != balasbuenas.end(); ++it){
						glColor3f(1.0,0.0,0.0);
						(*it).dibujar();
					}
			glPopMatrix();
			// Push para las balas malas
			glPushMatrix();
				for (std::list<bala>::iterator it=balasmalas.begin(); it != balasmalas.end(); ++it){
							glColor3f(0.0,1.0,0.0);
							(*it).dibujar();
						}
			glPopMatrix();
			verifEnemigos();
			verifColisiones();
		glPopMatrix();
	}
	else{
		if (gano==false){
			glPushMatrix();
				// Push dibujar letras fin del juego
				glPushMatrix();
					glTranslatef(-35.0f,0.0f,0.0f);
					glPushMatrix();
						glScalef(0.08f,0.06f,0.0f);
						for (i = 0; i < strlen(finJuego); i++)
						{
							glColor3f(1.0f,1.0f,0.0f);
							glutStrokeCharacter(GLUT_STROKE_ROMAN, finJuego[i]);
						}
					glPopMatrix();
					// Push de las letras del perdiste
					glTranslatef(15.0f,-10.0f,0.0f);
					glPushMatrix();
						glScalef(0.08f,0.06f,0.0f);
						for (i = 0; i < strlen(perdiste); i++)
						{
							glColor3f(1.0f,1.0f,0.0f);
							glutStrokeCharacter(GLUT_STROKE_ROMAN, perdiste[i]);
						}
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		}
		else{
			glPushMatrix();
				// Push para dibujar ganaste
				glPushMatrix();
					glTranslatef(-20.0f,0.0f,0.0f);
					glPushMatrix();
						glScalef(0.09f,0.06f,0.0f);
						for (i = 0; i < strlen(ganaste); i++)
						{
							glColor3f(1.0f,1.0f,0.0f);
							glutStrokeCharacter(GLUT_STROKE_ROMAN, ganaste[i]);
						}
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}

// funcion para mover automaticamente los bloques enemigos
void movEnemigos(int a){	
	for (int j = 0; j < 30; j++)
	{
		if ((total[j].getX()+total[j].getLargo()/2>=50 || total[j].getX()-total[j].getLargo()/2<=-50)&&total[j].getExiste()){
			vel=-vel;
			tiempoMovEnemigos = tiempoMovEnemigos*0.9;
			// se actualizan las componentes de y en 5 mas abajo de las originales
			for (int i = 0; i < 30; i++)
			{
				total[i].setXY(total[i].getX(),total[i].getY()-5.0);
			}
			render();
			glutTimerFunc(tiempoMovEnemigos,movEnemigos,0);
			break;
		}
	}
	// se actualizan las componentes de x segun la velocidad
	for (int i = 0; i < 30; i++)
	{
		total[i].setXY(total[i].getX()+vel,total[i].getY());
	}
	render();
	glutTimerFunc(tiempoMovEnemigos,movEnemigos,0);
}

void aparecerNave(int a){
	jugadores[0].setExiste(true);
}

// funcion que lleva el movimiento de la nave
void movNave(int a){
	float velocidad = 1.0;
	tiempo = tiempo;
	// se actualizan las componentes del eje x de la nave
	jugadores[0].setEnemigoXY(jugadores[0].getX()+velocidad,jugadores[0].getY());
	if (jugadores[0].getX()>60){
		jugadores[0].setEnemigoXY(-60.0,42.0);
		jugadores[0].setExiste(false);
		render();
		glutTimerFunc(tiempoNaveEnemiga*1000,aparecerNave,0);
		glutTimerFunc(tiempoNaveEnemiga*1000,movNave,0);
		return;
	}
	else{
		render();
		glutTimerFunc(tiempo,movNave,0);
	}
}

void invadersInit()
{
	// inicializacion de los bloques enemigos
	for (int i = 0; i < 30; i++)
	{
		bloque b = bloque(2.0,7.0);
		total[i] = b;
	}
	// inicializacion de los bloques defensa
	for (int i = 0; i < 24; i++)
	{
		bloque b = bloque(1.0,3.0);
		defensa[i] = b;
	}
	// variables para llevar la suma de las posiciones que deben tener los bloques
	float x=-35.0;
	float y=30.0;
	// actualizacion de los bloques enemigos
	for (int i = 0; i < 30; i++)
	{
		if ((i==1)||(i==3)||(i==11)||(i==15)||(i==19)||(i==28)){
			total[i].setXY(x,y);
			total[i].setMorado(true);
		}
		else{
			total[i].setXY(x,y);
		}
		x = x + 10.0;
		// para dibujar la siguiente linea de bloques enemigos de arriba hacia abajo
		if ((i==5)||(i==11)||(i==17)||(i==23)){
			y = y - 5.0;
			// para definir si va mas a la izquierda de la primera linea
			if ((i==11)||(i==23)){
				x = -35.0;
			}
			else{
				x = -40.0;
			}
		}
	}
	// reseteo x e y
	x = -38.0;
	y = -35.0;
	// actualizacion de los bloques defensa
	for (int i = 0; i < 24; i++)
	{
		defensa[i].setXY(x,y);
		// para definir la distancia que debe haber entre los conjuntos de bloques defensa
		if ((i==3)||(i==7)||(i==13)||(i==15)){
			x = x + 10.0;				
		}
		if ((i==19)||(i==21)){
			x = x + 20.0;
		}
		// distancia intermedia de los bloques defensa del medio
		if ((12<=i) && (i<18)){
			x = x + 10.0;
		}
		else{
			x = x + 5.0;
		}
		//actualizacion para dibujar los bloques defensa de abajo hacia arriba
		if ((i==11) || (i==17)){
			y = y + 3.0;
			if (i==11)
				x = -35.0;
			else
				x = -33.0;
		}
	}
	// inicializacion de los jugadores
	for (int i = 0; i < 2; i++)
	{
		nave n;
		if (i==0){
			n = nave(14.0,7.0);
			n.setExiste(false);
		}
		else{
			n = nave(10.0,5.0f);
		}
		jugadores[i] = n;
	}
	//actualizacion de las posiciones de los jugadores
	for (int i = 0; i < 2; i++)
	{
		if (i==0){
			//reseteo de x e y
			x=-60.0;
			y=42.0;
			jugadores[i].setEnemigoXY(x,y);
		}
		else{
			//reseteo de x e y
			x=0.0;
			y=-44.0;
			jugadores[i].setXY(x,y);
		}
	}
	// Manejo de los string por pantalla
	textoPuntaje();
}

void disparar(int a){
	for (std::list<bala>::iterator it=balasbuenas.begin(); it != balasbuenas.end(); ++it){
		(*it).setXY((*it).getX(),(*it).getY()+1);
	}
	render();
	for (std::list<bala>::iterator it=balasmalas.begin(); it != balasmalas.end(); ++it){
		(*it).setXY((*it).getX(),(*it).getY()-0.2);
	}
	glutTimerFunc(tiempoDisparos,disparar,0);
}

void crearBalaMala(int a)
{
	esfera = bala(0.5);
	// se le asigna a la esfera la posicion del jugador
	int i = rand()%30;
	int j = 0;
	while(!total[i].getExiste()){
		i = rand()%30;
		j++;
		if (j>=30)
			break; 
	}
	esfera.setXY(total[i].getX(),total[i].getY());
	balasmalas.push_back(esfera);
	glutTimerFunc(tiempoDispEnemigos*1000,crearBalaMala,0);
}

int main (int argc, char** argv) 
{
	srand(time(NULL));
	invadersInit();
 	// inicializacion del arreglo que lleva las teclas especiales
	for (int i = 0; i < 246; i++)
	{
		keySpecialStates[i] = false;
	}
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(800,600);

	glutCreateWindow("Space Invaders");

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);

	glutKeyboardFunc(teclaPresionada);
	glutKeyboardUpFunc(teclaLiberada);

	glutSpecialFunc(keySpecial); // GLUT usa el metodo "keySpecial" para la presion de las teclas especiales  
	glutSpecialUpFunc(keySpecialUp); // GLUT usa el metodo "keySpecialUp" para los eventos especiales de la tecla de arriba  

	// timer para la nave enemiga
	glutTimerFunc(tiempoNaveEnemiga*1000,aparecerNave,0);
	glutTimerFunc(tiempoNaveEnemiga*1000,movNave,0);
	glutTimerFunc(tiempoMovEnemigos,movEnemigos,0);
	glutTimerFunc(tiempoDisparos,disparar,0);
	glutTimerFunc(tiempoDispEnemigos*1000,crearBalaMala,0);
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glutMainLoop();

	return 0;
}