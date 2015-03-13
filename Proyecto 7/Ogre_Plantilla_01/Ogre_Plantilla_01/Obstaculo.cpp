#include "stdafx.h"

Obstaculo::Obstaculo(Ogre::String nombre, Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	_sceneManager = sm;

	nodoObstaculo = _sceneManager->createSceneNode("Obstaculo"+nombre);
	Ogre::SceneNode* nodoMedio = _sceneManager->createSceneNode(nombre+"medio");
	Ogre::SceneNode* nodoSuperior = _sceneManager->createSceneNode(nombre+"superior");
	
	Ogre::Entity* entObstaculo = _sceneManager->createEntity("poly17.mesh");
	Ogre::Entity* entMedio = _sceneManager->createEntity("poly15.mesh");
	Ogre::Entity* entSuperior= _sceneManager->createEntity("uv_sphere.mesh");
	
	entObstaculo->setMaterialName("obstaculo");
	entMedio->setMaterialName("cadena");
	entSuperior->setMaterialName("mina");
	
	nodoMedio->attachObject(entMedio);
	nodoMedio->setScale(1.0,2.0,1.0);
	nodoMedio->translate(0.0,120.0,0.0);

	nodoSuperior->attachObject(entSuperior);
	nodoSuperior->setScale(2.0,0.3,2.0);
	nodoSuperior->translate(0.0,250.0,0.0);

	nodoObstaculo->attachObject(entObstaculo);
	nodoObstaculo->addChild(nodoMedio);
	nodoObstaculo->addChild(nodoSuperior);
	
	nodoObstaculo->setPosition(x,y,z);
	nodoObstaculo->setScale(1.0,10.0,1.0);

}
