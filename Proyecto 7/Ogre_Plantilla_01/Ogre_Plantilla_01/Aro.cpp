#include "stdafx.h"

Aro::Aro( Ogre::String nombre , Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	_sceneManager = sm;
	Ogre::Vector3 scale = Ogre::Vector3(3.5);

	nodoAro = _sceneManager->createSceneNode("Aro"+nombre);
	_sceneManager->getRootSceneNode()->addChild(nodoAro);
	Ogre::Entity* entAro = _sceneManager->createEntity("poly04.mesh");
	entAro->setMaterialName("mat01");
	nodoAro->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(90.0)),Ogre::Vector3(1.0,0.0,0.0)));
	nodoAro->attachObject(entAro);
	nodoAro->setPosition(x,y,z); 
	nodoAro->setScale(scale);
}
