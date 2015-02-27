#include <stdlib.h>
#include <conio.h>

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "glsl.h"


// assimp include files. These three are usually needed.
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// the global Assimp scene object
const aiScene* scene = NULL;
GLuint scene_list = 0;
aiVector3D scene_min, scene_max, scene_center;

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)


using namespace std;

cwc::glShaderManager SM;
cwc::glShader *shader;

GLfloat posLX;
GLfloat posLZ;

GLfloat bias;
GLfloat eta;
GLfloat Kfr;
GLfloat refraccion;
GLfloat m;
GLfloat sharpness;
GLfloat roughness;
GLfloat intSpec;
GLfloat intDiff;

bool fresnel;
bool cook;

char mensaje_fresnel[20];
char mensaje_difuso[20];
char mensaje_especular[20];

void changeViewport(int w, int h) {
	
	float aspectratio;

	if (h==0)
		h=1;

	
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(30, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode (GL_MODELVIEW);

}

void init_surface() {

	
	
}

void init(){
	
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
   
   shader = SM.loadfromFile("lambertPhong.vert","lambertPhong.frag"); // load (and compile, link) from file
	if (shader==0)
			std::cout << "Error Loading, compiling or linking shader\n";
	
	posLX = 10.0;
	posLZ = 10.0;

	bias = 0.0;
	eta = 0.0;
	Kfr = 0.0;

	fresnel = false;
	strcpy(mensaje_fresnel,"DESACTIVADO");

	refraccion = 1.0;
	m = 0.0;

	sharpness = 0.0;
	roughness = 0.1;

	cook = false;
	strcpy(mensaje_difuso,"BIAS");
	strcpy(mensaje_especular,"GLOSSY SHARP");

	intSpec = 0.0;
	intDiff = 0.0;
}


void Keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
	case '1':
		cook = false;
		strcpy(mensaje_especular,"GLOSSY SHARP");
		break;
	case '2':
		cook = true;
		strcpy(mensaje_especular,"COOK-TORRENCE");
		break;
	case '3':
		fresnel = true;
		strcpy(mensaje_fresnel,"ACTIVADO");
		break;
	case '4':
		fresnel = false;
		strcpy(mensaje_fresnel,"DESACTIVADO");
		break;
	case 'q':
		refraccion += 0.15;
		break;
    case 'w':
		if (refraccion > 1.001){
			refraccion -= 0.15;
		}
		break;
	case 'a':
		m += 0.01;
		break;
	case 'm':
		if (m > 0.001){
			m -= 0.01;
		}
		break;
	case 'e':
		if (sharpness < 0.999) {
			sharpness += 0.02;
		}
		break;
	case 'r':
		if (sharpness > 0.001){
			sharpness -= 0.02;
		}
		break;
	case 'd':
		roughness += 0.02;
		break;
	case 'f':
		if (roughness > 0.1001){
			roughness -= 0.02;
		}
		break;
	case 'u':
		eta += 0.02;
		break;
	case 'i':
		if (eta > 0.001){
			eta -= 0.02;
		}
		break;
	case 'j':
		Kfr += 0.1;
		break;
	case 'k':
		if (Kfr > 0.01){
			Kfr -= 0.1;
		}
		break;
	case 'z':
		bias += 0.1;
		break;
	case 'x':
		bias -= 0.1;
		break;
	case 'c':
		intSpec += 0.1;
		break;
	case 'v':
		if (intSpec > 0.11){
			intSpec -= 0.1;
		}
		break;
	case 'b':
		intDiff += 0.1;
		break;
	case 'n':
		if (intDiff > 0.01){
			intDiff -= 0.1;
		}
		break;
	case 27:
		exit (0);
		break;
  }

  system("cls");
  cout<<"Valores de las variables"<<endl
	  <<"-----------------------------------------"<<endl<<endl
	  <<"SPECULAR ACTIVO = "<<mensaje_especular<<endl
	  <<"DIFFUSE ACTIVO = "<<mensaje_difuso<<endl
	  <<"FRESNEL "<<mensaje_fresnel<<endl
	  <<"======================================================="<<endl
	  <<"Diffuse Variables"<<endl
	  <<"BiasDiff: bias = "<<bias<<endl
	  <<"Intensidad Difusa: intDiff = "<<intDiff<<endl
	  <<"======================================================="<<endl
	  <<"Specular Variables"<<endl
	  <<"Cook-Torrance: m = "<<m<<", indexR = "<<refraccion<<endl
	  <<"GlossySharp: shaperness = "<<sharpness<<", roughness = "<<roughness<<endl
	  <<"Intensidad Especular: intSpec = "<<intSpec<<endl
	  <<"======================================================="<<endl
	  <<"Fresnel"<<endl
	  <<"eta = "<<eta<<", Kfr = "<<Kfr<<endl
	  <<"-----------------------------------------"<<endl;

  glutPostRedisplay();
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
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

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
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

void render(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat zExtent, xExtent, xLocal, zLocal;
    int loopX, loopZ;

	glLoadIdentity ();                       
	gluLookAt (10.0, 3.0, 5.0, 0.0, 1.5, 0.0, 0.0, 1.0, 0.0);
	

	// Luz y material
	GLfloat mat_diffuse[] = { 1.0, 0.7, 0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 0.5, 0.5, 1.0 };
	GLfloat mat_ambient[] = { 0.1, 0.1 ,0.1, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	

    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_specular[] = { 0.8, 0.8, 0.8, 1.0 };
	//GLfloat light_position[] = { posLX, 10.0, posLZ, 1.0 };
	GLfloat light_position[] = { 10.0, 10.0, 10.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);   


	//Suaviza las lineas
	glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_LINE_SMOOTH );	
	
	glPushMatrix();

	if (shader) {
		shader->begin();
		shader->setUniform1f("bias", bias);
		shader->setUniform1f("fresnel",fresnel);
		shader->setUniform1f("eta",eta);
		shader->setUniform1f("Kfr", Kfr);
		shader->setUniform1f("cook",cook);
		shader->setUniform1f("refraccion",refraccion);
		shader->setUniform1f("m",m);
		shader->setUniform1f("sharpness",sharpness);
		shader->setUniform1f("roughness",roughness);
		shader->setUniform1f("intSpec",intSpec);
		shader->setUniform1f("intDiff",intDiff);
	}


	// COdigo para el mesh
	glEnable(GL_NORMALIZE);
	glTranslatef(0.0, -2.0, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	glScalef(30.0, 30.0, 30.0);
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}
	glCallList(scene_list);
	
	glPopMatrix();
	
	
	glPushMatrix();
	glTranslatef(5.2, 3.25, 0.0);
	glutSolidSphere(0.4f,30,30);
	glPopMatrix();
	 

	if (shader) shader->end();

	
	

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);

	glutSwapBuffers();
}

void animacion(int value) {
	
	glutTimerFunc(10,animacion,1);
    glutPostRedisplay();
	
}

void get_bounding_box_for_node (const aiNode* nd, 	aiVector3D* min, 	aiVector3D* max, 	aiMatrix4x4* trafo){
	aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
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

void get_bounding_box (aiVector3D* min, aiVector3D* max){
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);
	
	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
}

int loadasset (const char* path){
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.
	scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene) {
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


	// Codigo para cargar la geometria usando ASSIMP

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
	if( 0 != loadasset( argc >= 2 ? argv[1] : "dragon_vrip_res2.ply")) {
		if( argc != 1 || (0 != loadasset( "dragon_vrip_res2.ply") && 0 != loadasset( "dragon_vrip_res2.ply"))) { 
			return -1;
		}
	}




	init ();

	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc (Keyboard);
	
	glutMainLoop();
	return 0;

}
