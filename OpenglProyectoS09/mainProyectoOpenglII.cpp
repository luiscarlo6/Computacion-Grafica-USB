// Cubica

#include <stdlib.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>


// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

static GLuint texPiso;
int iheightPiso, iwidthPiso;
unsigned char* Piso = NULL;

static GLuint texConejo;
int iheightConejo, iwidthConejo;
unsigned char* Conejo = NULL;

static GLuint texColumna;
int iheightColumna, iwidthColumna;
unsigned char* Columna = NULL;

static GLuint texCubeMap[6];
int heightCubeMap[6], widthCubeMap[6];
unsigned char* CubeMap[6];

// the global Assimp scene object
const aiScene* scene01 = NULL;
const aiScene* scene02 = NULL;
const aiScene* scene03 = NULL;

GLfloat lightAmbient[] =  {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightDiffuse[] =  {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat lightSpecular[] = {0.1, 0.1, 0.1, 1.0 };
GLfloat lightPosition[] = {0.0f, 200.0f, 0.0f, 1.0f};
GLfloat lightDirection[] = {0.0f,-1.0f, 0.0f};

GLfloat lightCutoff = 50.0f;
GLfloat lightExponent = 25.0f;

//todas las textutras
GLfloat shininess = 70.0f;
GLfloat ambiental[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat specular[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};

// texturas del conejo
GLfloat c_shininess = 70.0f;
GLfloat c_ambiental[] = {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat c_specular[] = {0.2f, 0.2f, 0.2f, 1.0f};
GLfloat c_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};

GLuint texPosX, texNegX, texPosY, texNegY, texPosZ, texNegZ;

GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

int pulsaciones = 0;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

using namespace std;

#define DEF_floorGridScale	1.0
#define DEF_floorGridXSteps	10.0
#define DEF_floorGridZSteps	10.0

#include "glm.h"

void changeViewport(int w, int h) {
	
	float aspectratio;

	if (h==0)
		h=1;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 3000.0);
   glMatrixMode (GL_MODELVIEW);

}

void init(){
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);  
	glGenTextures(1, &texPiso);
   	glBindTexture(GL_TEXTURE_2D, texPiso);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	Piso = glmReadPPM("texAO_plano.ppm", &iwidthPiso, &iheightPiso);

   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidthPiso, iheightPiso, 0, GL_RGB, GL_UNSIGNED_BYTE, Piso);

	glGenTextures(1, &texConejo);
   	glBindTexture(GL_TEXTURE_2D, texConejo);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	Conejo = glmReadPPM("texAO_bunny.ppm", &iwidthConejo, &iheightConejo);

   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidthConejo, iheightConejo, 0, GL_RGB, GL_UNSIGNED_BYTE, Conejo);

	glGenTextures(1, &texColumna);
   	glBindTexture(GL_TEXTURE_2D, texColumna);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	Columna = glmReadPPM("texAO_columna.ppm", &iwidthColumna, &iheightColumna);

   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidthColumna, iheightColumna, 0, GL_RGB, GL_UNSIGNED_BYTE, Columna);

	//glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
    glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);
    glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_REFLECTION_MAP);

	CubeMap[0] = glmReadPPM("posx.ppm",&widthCubeMap[0],&heightCubeMap[0]);
	CubeMap[1] = glmReadPPM("negx.ppm",&widthCubeMap[1],&heightCubeMap[1]);
	CubeMap[2] = glmReadPPM("posy.ppm",&widthCubeMap[2],&heightCubeMap[2]);
	CubeMap[3] = glmReadPPM("negy.ppm",&widthCubeMap[3],&heightCubeMap[3]);
	CubeMap[4] = glmReadPPM("posz.ppm",&widthCubeMap[4],&heightCubeMap[4]);
	CubeMap[5] = glmReadPPM("negz.ppm",&widthCubeMap[5],&heightCubeMap[5]);

	glGenTextures(1,&texPosX);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X,texPosX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,widthCubeMap[0],heightCubeMap[0],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[0]);

	glGenTextures(1,&texNegX);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,texNegX);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,widthCubeMap[1],heightCubeMap[1],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[1]);

	glGenTextures(1,&texPosY);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,texPosY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,widthCubeMap[2],heightCubeMap[2],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[2]);

	glGenTextures(1,&texNegY);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,texNegY);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,widthCubeMap[3],heightCubeMap[3],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[3]);

	glGenTextures(1,&texPosZ);
	glBindTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,texPosZ);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,widthCubeMap[4],heightCubeMap[4],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[4]);

	glGenTextures(1,&texNegZ);
	glBindTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,texNegZ);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,widthCubeMap[5],heightCubeMap[5],1,GL_RGB,GL_UNSIGNED_BYTE,CubeMap[5]);

	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_REPEAT);
    // Sets the texture's max/min filters
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}


void cargar_materiales(int idx) {

	// Material Piso
	if (idx == 0){	
		glBindTexture( GL_TEXTURE_2D, texPiso );
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiental);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	
	}

	// Material Columna
	if (idx == 1){		
		glBindTexture( GL_TEXTURE_2D, texColumna );

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambiental);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	// Material Conejo
	if (idx == 2){
		glBindTexture( GL_TEXTURE_2D, texConejo );
		glMaterialfv(GL_FRONT, GL_AMBIENT, c_ambiental);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, c_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, c_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, c_shininess);
	}

}

void recursive_render (const aiScene *sc, const aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		
		const aiMesh* mesh = scene01->mMeshes[nd->mMeshes[n]];

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				
				if(mesh->mNormals != NULL) 
					glNormal3fv(&mesh->mNormals[index].x);
				
				if (mesh->HasTextureCoords(0)) 
					glTexCoord2f(mesh->mTextureCoords[0][index].x, 1-mesh->mTextureCoords[0][index].y);
				
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		glEnable(GL_TEXTURE_2D);
		cargar_materiales(n);
		recursive_render(sc, nd->mChildren[n]);
		glDisable(GL_TEXTURE_2D);
	}

	glPopMatrix();
}


void Keyboard(unsigned char key, int x, int y)
{
  int i;
  switch (key)
  {
	case 'q':
		lightCutoff+=2.0f;
		break;
    case 'w':
		lightCutoff-=2.0f;
		break;
	case 'a':
		lightExponent+=2.0f;
		break;
	case 's':
		lightExponent-=2.0f;
		break;
	case 'z':
		for (i=0;i<3;i++){
			ambiental[i]+=0.1;
			c_ambiental[i]+=0.1;
		}
		break;
	case 'x':
		for (i=0;i<3;i++){
			ambiental[i]-=0.1;
			c_ambiental[i]-=0.1;
		}
		break;
	case 'e':
		lightPosition[0] += 1.0f;
		break;
	case 'd':
		lightPosition[0] -= 1.0f;
		break;
	case 'r':
		lightPosition[2] += 1.0f;
		break;
	case 'f':
		lightPosition[2] -= 1.0f;
		break;
	case 'b':
		for (i=0;i<3;i++){
			lightAmbient[i]+=0.1;
			lightDiffuse[i]+=0.1;
			lightSpecular[i]+=0.1;
		}
		break;
	case 'n':
		for (i=0;i<3;i++){
			lightAmbient[i]-=0.1;
			lightDiffuse[i]-=0.1;
			lightSpecular[i]-=0.1;
		}
		break;
	case 't':
		c_diffuse[0]+=0.05;
		break;
	case 'g':
		c_diffuse[0]-=0.05;
		break;
	case 'y':
		c_diffuse[1]+=0.05;
		break;
	case 'h':
		c_diffuse[1]-=0.05;
		break;
	case 'u':
		c_diffuse[2]+=0.05;
		break;
	case 'j':
		c_diffuse[2]-=0.05;
		break;
	case '1':
		lightDiffuse[0]=1.0f;
		lightDiffuse[1]=1.0f;
		lightDiffuse[2]=1.0f;
		break;
	case '2':
		//verde
		lightDiffuse[0]=0.0f;
		lightDiffuse[1]=1.0f;
		lightDiffuse[2]=0.0f;
		break;
	case '3':
		//azul
		lightDiffuse[0]=0.0f;
		lightDiffuse[1]=0.0f;
		lightDiffuse[2]=0.61f;
		break;
	case '4':
		//morado
		lightDiffuse[0]=1.0f;
		lightDiffuse[1]=0.0f;
		lightDiffuse[2]=1.0f;
		break;
	case '5':
		//naranja
		lightDiffuse[0]=1.0f;
		lightDiffuse[1]=0.5f;
		lightDiffuse[2]=0.0f;
		break;
	case 27:             
		exit (0);
		break;
  }

  scene_list = 0;
  glutPostRedisplay();
}

void DibujarObjetos3D() {

   	
   	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
   	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
   	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
   	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
	glLightfv (GL_LIGHT0, GL_SPECULAR, lightSpecular);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lightCutoff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lightExponent);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiffuse1);
}

void render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity ();                       
	gluLookAt (0, 80, 250, 0.0, 15.0, 0.0, 0.0, 1.0, 0.0);

	//Suaviza las lineas
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );	
	
	
	DibujarObjetos3D();
	glPushMatrix();
	glEnable(GL_NORMALIZE);
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.		
	    recursive_render(scene01, scene01->mRootNode);
	    glEndList();
	}
	glCallList(scene_list);
	
	
	glPopMatrix();
	


	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glutSwapBuffers();
}

void animacion(int value) {
	
	glutTimerFunc(10,animacion,1);
    glutPostRedisplay();
	
}

void get_bounding_box_for_node (const aiNode* nd, 
	aiVector3D* min, 
	aiVector3D* max, 
	aiMatrix4x4* trafo
){
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	
		prev = *trafo;
		aiMultiplyMatrix4(trafo,&nd->mTransformation);

		for (; n < nd->mNumMeshes; ++n) {
			const aiMesh* mesh = scene01->mMeshes[nd->mMeshes[n]];
				for (t = 0; t < mesh->mNumVertices; ++t) {

				aiVector3D tmp = mesh->mVertices[t];
				aiTransformVecByMatrix4(&tmp,trafo);

				min->x = aisgl_min(min->x,tmp.x);
				min->y = aisgl_min(min->y,tmp.y);
				min->z = aisgl_min(min->z,tmp.z);

				max->x = aisgl_max(max->x,tmp.x);
				max->y = aisgl_max(max->y,tmp.y);
				max->z = aisgl_max(max->z,tmp.z);
			}
		}

		for (n = 0; n < nd->mNumChildren; ++n) {
			get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
		}
		*trafo = prev;
	

}

void get_bounding_box (aiVector3D* min, aiVector3D* max)
{
	aiMatrix4x4 trafo;

	
		aiIdentityMatrix4(&trafo);
	
		min->x = min->y = min->z =  1e10f;
		max->x = max->y = max->z = -1e10f;
		get_bounding_box_for_node(scene01->mRootNode,min,max,&trafo);


}

int loadasset (const char* path)
{
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.
	
		
		scene01 = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

		if (scene01) {
			get_bounding_box(&scene_min,&scene_max);
			scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
			scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
			scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
			return 0;
		}


	return 1;
}

int main (int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowSize(960,540);

	glutCreateWindow("Test Opengl");


	aiLogStream stream;
	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It remains active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	// ... same procedure, but this stream now writes the
	// log messages to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);

	// the model name can be specified on the command line. If none
	// is specified, we try to locate one of the more expressive test 
	// models from the repository (/models-nonbsd may be missing in 
	// some distributions so we need a fallback from /models!).
	//if( 0 != loadasset( argc >= 2 ? argv[1] : "dragon_vrip_res2.ply")) {
	//	if( argc != 1 || (0 != loadasset( "dragon_vrip_res2.ply") && 0 != loadasset( "dragon_vrip_res2.ply"))) { 
	//		return -1;
	//	}
	//}

	if (loadasset( "escenario.obj") != 0) {
		return -1;
	}




	init ();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc (Keyboard);
	


	glutMainLoop();
	return 0;

}
