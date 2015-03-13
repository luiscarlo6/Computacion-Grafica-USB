#include "stdafx.h"

Banderin::Banderin( Ogre::String nombre , Ogre::SceneManager* sm , float _x , float _y , float _z){

	x = _x;
	y = _y;
	z = _z;
	_sceneManager = sm;
	Ogre::Vector3 scale = Ogre::Vector3(3.5);

	nodoBanderin = _sceneManager->createSceneNode("Banderin"+nombre);
	Ogre::SceneNode* nodoSuperiorIzq = _sceneManager->createSceneNode(nombre+"superiorIzq");
	Ogre::SceneNode* nodoBandera = _sceneManager->createSceneNode(nombre+"bandera");
	Ogre::SceneNode* nodoSuperiorDer = _sceneManager->createSceneNode(nombre+"superiorDer");
	Ogre::SceneNode* nodoBaseDer = _sceneManager->createSceneNode(nombre+"baseDer");
	
	Ogre::Entity* entBanderin = _sceneManager->createEntity("usb_cilindro.mesh");
	Ogre::Entity* entSuperiorIzq = _sceneManager->createEntity("poly10.mesh");
	Ogre::Entity* entBandera = _sceneManager->createEntity("usb_planocurvo.mesh");
	Ogre::Entity* entSuperiorDer = _sceneManager->createEntity("poly10.mesh");
	Ogre::Entity* entBaseDer = _sceneManager->createEntity("usb_cilindro.mesh");
	
	entBanderin->setMaterialName("banderin");
	entSuperiorIzq->setMaterialName("superior");
	entBandera->setMaterialName("bandera");
	entSuperiorDer->setMaterialName("superior");
	entBaseDer->setMaterialName("banderin");
	
	nodoSuperiorIzq->attachObject(entSuperiorIzq);
	nodoSuperiorIzq->setScale(0.03,0.008,0.06);
	nodoSuperiorIzq->translate(2.2,7.2,0.0);
	nodoSuperiorIzq->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(180.0)));

	nodoBandera->attachObject(entBandera);
	nodoBandera->setScale(1.2,4.10,1.0);
	nodoBandera->translate(-2.2,7.2,0.0);
	nodoBandera->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));

	nodoSuperiorDer->attachObject(entSuperiorDer);
	nodoSuperiorDer->setScale(0.03,0.008,0.06);
	nodoSuperiorDer->translate(-152.2,7.2,0.0);

	nodoBaseDer->attachObject(entBaseDer);
	nodoBaseDer->translate(-150.0,0.0,0.0);

	nodoBanderin->attachObject(entBanderin);
	nodoBanderin->addChild(nodoSuperiorIzq);
	nodoBanderin->addChild(nodoBandera);
	nodoBanderin->addChild(nodoSuperiorDer);
	nodoBanderin->addChild(nodoBaseDer);
	
	nodoBanderin->setPosition(x,y,z);
	nodoBanderin->setScale(15.0,140.0,15.0);
}
