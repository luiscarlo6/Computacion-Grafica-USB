#include "Nave.h"

Nave::Nave(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y){

	mSceneMgr = sm;

	nodoNave = mSceneMgr->createSceneNode(nombre);

	Ogre::SceneNode* nodoMedio = mSceneMgr->createSceneNode(nombre+"medio");
	Ogre::SceneNode* nodoAlaDer = mSceneMgr->createSceneNode(nombre+"alaDer");

	Ogre::Entity* entMedio = mSceneMgr->createEntity("uv_sphere.mesh");
	
	Ogre::ManualObject* alaIzq = crearAla(nombre+"alaIzq", mSceneMgr);

	entMedio->setMaterialName("Nave_text");

	nodoMedio->attachObject(entMedio);	
	nodoMedio->setScale(2.0,2.0,2.0);
	nodoMedio->translate(0.0,-(5*10.0),(5*40.0));
 
	Ogre::ManualObject* alaDer = crearAla(nombre+"alaDer", mSceneMgr);

	nodoAlaDer->attachObject(alaDer);
	nodoAlaDer->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(180.0)));
	nodoAlaDer->translate(0.0,0.0,(5*80.0));
	
	nodoNave->attachObject(alaIzq);
	nodoNave->addChild(nodoMedio);
	nodoNave->addChild(nodoAlaDer);

	nodoNave->setPosition(x,-60,y); 
	nodoNave->setScale(0.9f,0.9f,0.9f);
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