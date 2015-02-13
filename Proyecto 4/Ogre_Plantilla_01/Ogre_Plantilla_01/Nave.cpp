#include "Nave.h"

Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam){
	camera = cam;
	mSceneMgr = sm;
	lastMove = 0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	nodoNave = mSceneMgr->createSceneNode("Tie_Fighter");
	nodoNave->setPosition(0.0,0.0,0.0); 
	Ogre::SceneNode* nodoMedio = mSceneMgr->createSceneNode("medio");
	Ogre::SceneNode* nodoAlaDer = mSceneMgr->createSceneNode("alaDer");

	Ogre::Entity* entMedio = mSceneMgr->createEntity("uv_sphere.mesh");
	entMedio->setCastShadows(true);
	
	Ogre::ManualObject* alaIzq = crearAla("alaIzq", mSceneMgr);

	entMedio->setMaterialName("Nave_text");

	nodoMedio->attachObject(entMedio);	
	nodoMedio->setScale(2.0,2.0,2.0);
	nodoMedio->translate(0.0,-(5*10.0),(5*40.0));
 
	Ogre::ManualObject* alaDer = crearAla("alaDer", mSceneMgr);

	nodoAlaDer->attachObject(alaDer);
	nodoAlaDer->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(180.0)));
	nodoAlaDer->translate(0.0,0.0,(5*80.0));
	
	nodoNave->attachObject(alaIzq);
	nodoNave->addChild(nodoMedio);
	nodoNave->addChild(nodoAlaDer);

	nodoNave->setPosition(0.0,0.0,0.0); 
	nodoNave->setScale(0.9f,0.9f,0.9f);
	nodoNave->attachObject(camera);


	Ogre::Vector3 escala(2.0f,2.0f,2.0f);
	Ogre::Light* light = mSceneMgr->createLight("luz");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	light->setDirection(Ogre::Vector3(0.0,0.0,-1.0));
	light->setDirection(Ogre::Vector3(0.0,0.0,0.0));
	nodoNave->attachObject(light);
}

Ogre::ManualObject* Nave::crearAla(Ogre::String nombre, Ogre::SceneManager* sm){
	mSceneMgr = sm;

	// create ManualObject
	Ogre::ManualObject* manual = mSceneMgr->createManualObject(nombre);
	// specify the material (by name) and rendering type
	manual->begin("Nave_text", RenderOperation::OT_TRIANGLE_LIST);
	// primer triangulo del cuadrado en x,z arriba
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), 0, (5*40.0));
	manual->textureCoord(0,0);
	manual->position(0, (5*20.0), 0);
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en x,z arriba
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), 0, (5*50.0));
	manual->textureCoord(1,0);
	manual->position(-(5*80.0), 0, (5*40.0));
	manual->textureCoord(0,0);

	// primer triangulo del cuadrado en x,z abajo
	manual->position(0, -(5*40.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(0, -(5*40.0), 0);
	manual->textureCoord(0,0);
	manual->position(-(5*80.0), 0, (5*40.0));
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en x,z abajo
	manual->position(0, -(5*40.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), 0, (5*40.0));
	manual->textureCoord(1,0);
	manual->position(-(5*80.0), 0, (5*50.0));
	manual->textureCoord(0,0);

	// primer triangulo del cuadrado en x,y atras
	manual->position(0, (5*20.0), 0);
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), 0, (5*40.0));
	manual->textureCoord(0,0);
	manual->position(-(5*80.0), -(5*10.0), (5*40.0));
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en x,y atras
	manual->position(0, (5*20.0), 0);
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), -(5*10.0), (5*40.0));
	manual->textureCoord(1,0);
	manual->position(0, -(5*40.0), 0);
	manual->textureCoord(0,0);

	// primer triangulo del cuadrado en x,y adelante
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), -(5*10.0), (5*50.0));
	manual->textureCoord(0,0);
	manual->position(-(5*80.0), 0, (5*50.0));
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en x,y adelante
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(0, -(5*40.0), (5*80.0));
	manual->textureCoord(1,0);
	manual->position(-(5*80.0), -(5*10.0), (5*50.0));
	manual->textureCoord(0,0);

	// primer triangulo del cuadrado en y,z izquierda
	manual->position(-(5*80.0), (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), -(5*20.0), 0);
	//manual->position(-(5*80.0), (5*20.0), 0);
	manual->textureCoord(0,0);
	manual->position(-(5*80.0), (5*20.0), 0);
//	manual->position(-(5*80.0), -(5*20.0), 0);
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en y,z izquierda
	manual->position(-(5*80.0), (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(-(5*80.0), -(5*20.0), (5*80.0));
//	manual->position(-(5*80.0), -(5*20.0), 0);
	manual->textureCoord(1,0);
	manual->position(-(5*80.0), -(5*20.0), 0);
//	manual->position(-(5*80.0), -(5*20.0), (5*80.0));
	manual->textureCoord(0,0);

	// primer triangulo del cuadrado en y,z derecha
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(0, -(5*40.0), 0);
	manual->textureCoord(0,0);
	manual->position(0, (5*20.0), 0);
	manual->textureCoord(0,1);

	// segundo triangulo del cuadrado en y,z derecha
	manual->position(0, (5*20.0), (5*80.0));
	manual->textureCoord(1,1);
	manual->position(0, -(5*40.0), (5*80.0));
	manual->textureCoord(1,0);
	manual->position(0, -(5*40.0), 0);
	manual->textureCoord(0,0);

	// tell Ogre, your definition has finished
	manual->end();

	return manual;
}


void Nave::moverDerecha(){
	if (x<1600 || z<-18700){	
		x+=10.0;
		nodoNave->translate(10.0,0.0,0.0);
		//camera->move(Ogre::Vector3(10.0,0.0,0.0));
		if (lastMove!=1){
			lastMove++;
			nodoNave->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-10.0)),Ogre::Vector3(0.0,0.0,1.0)));
			camera->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(10.0)),Ogre::Vector3(0.0,0.0,1.0)));
		}
	}
}


void Nave::moverIzquierda(){
	if ((x>-1600 || z<-18700)){
		x-=10.0;
		nodoNave->translate(-10.0,0.0,0.0);
		//camera->move(Ogre::Vector3(-10.0,0.0,0.0));
		if (lastMove!=-1){
			lastMove--;
			nodoNave->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(10.0)),Ogre::Vector3(0.0,0.0,1.0)));
			camera->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-10.0)),Ogre::Vector3(0.0,0.0,1.0)));
		}
	}
}


void Nave::moverAdelante(){
	if (z>-23400){
		z-=10.0;
		nodoNave->translate(0.0,0.0,-10.0);
		//camera->move(Ogre::Vector3(0.0,0.0,-10.0));
	}
}

void Nave::moverArriba(){
	y+=10.0;
	nodoNave->translate(0.0,10.0,0.0);
	//camera->move(Ogre::Vector3(0.0,10.0,0.0));
}

void Nave::moverAbajo(){
	if (y>-1000){
		y-=10.0;
		nodoNave->translate(0.0,-10.0,0.0);
		//camera->move(Ogre::Vector3(0.0,-10.0,0.0));
	}
}

void Nave::rotarDerecha(){

	//nodoNave->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(-1.0)));
	nodoNave->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(-1.0)),Ogre::Vector3(0.0,1.0,0.0)));
	//camera->move(Ogre::Vector3(2000.0*cos(-1.0),300.0,2000.0*sin(-1.0))+ nodoNave->getPosition());
}

void Nave::rotarIzquierda(){

	nodoNave->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(1.0)));
	//camera->move(Ogre::Vector3(2000.0*cos(1.0),300.0,2000.0*sin(1.0))+ nodoNave->getPosition());

}

void Nave::arreglar(){
	//nodoNave->setOrientation(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));
	//camera->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(0.0)),Ogre::Vector3(0.0,0.0,1.0)));
}

void Nave::moverAtras(){
	//if (z>-23400){
		z+=10.0;
		nodoNave->translate(0.0,0.0,10.0);
		//camera->move(Ogre::Vector3(0.0,0.0,-10.0));
	//}
}