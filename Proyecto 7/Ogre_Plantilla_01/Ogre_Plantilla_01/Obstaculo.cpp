#include "stdafx.h"

Obstaculo::Obstaculo( Ogre::String nombre, int tipo, Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	_sceneManager = sm;
	const char *tipos[2];
	tipos[0] = "poly01.mesh";
	tipos[1] = "poly02.mesh";

	Ogre::Vector3 scale = Ogre::Vector3(3.5);


	nodoObstaculo = _sceneManager->createSceneNode("Obstaculo"+nombre);
	_sceneManager->getRootSceneNode()->addChild(nodoObstaculo);
	Ogre::Entity* entObstaculo = _sceneManager->createEntity(tipos[tipo]);
	entObstaculo->setMaterialName("mat01");
	nodoObstaculo->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	nodoObstaculo->attachObject(entObstaculo);
	nodoObstaculo->setPosition(x,y,z); 
	nodoObstaculo->setScale(scale);
}
