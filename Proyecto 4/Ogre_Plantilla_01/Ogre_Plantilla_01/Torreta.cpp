#include "Torreta.h"

Torreta::Torreta(Ogre::String _nombre, Ogre::SceneManager* sm, Ogre::Real _x, Ogre::Real _z, Ogre::Real _r){

	mSceneMgr = sm;
	nombre = _nombre;
	x = _x;
	z = _z;
	rotacion = _r;

	nodoTorreta = mSceneMgr->createSceneNode(nombre);
	Ogre::SceneNode* nodoSuperior = mSceneMgr->createSceneNode(nombre+"superior");
	Ogre::SceneNode* nodoArma = mSceneMgr->createSceneNode(nombre+"arma");

	Ogre::Entity* entTorreta = mSceneMgr->createEntity("usb_cilindro02.mesh");
	Ogre::Entity* entSuperior = mSceneMgr->createEntity("uv_sphere.mesh");
	Ogre::Entity* entArma = mSceneMgr->createEntity("usb_cilindro.mesh");

	entTorreta->setMaterialName("Torreta_text");
	entSuperior->setMaterialName("Torreta_text1");
	entArma->setMaterialName("Torreta_text1");
	
	nodoSuperior->attachObject(entSuperior);	
	nodoSuperior->setScale(0.05,0.05,0.05);
	nodoSuperior->translate(0.0,10.0,0.0);

	nodoArma->attachObject(entArma);
	nodoArma->setScale(0.3,0.3,0.3);
	nodoArma->translate(6.0,10.0,0.0);
	nodoArma->rotate(Ogre::Vector3(0.0,0.0,1.0),Ogre::Radian(Ogre::Degree(90.0)));

	nodoTorreta->attachObject(entTorreta);	
	nodoTorreta->addChild(nodoSuperior);
	nodoTorreta->addChild(nodoArma);
	nodoTorreta->rotate(Ogre::Vector3(0.0,1.0,0.0),Ogre::Radian(Ogre::Degree(rotacion)));
	nodoTorreta->setPosition(x,-60,z); 
	nodoTorreta->setScale(50.0f,50.0f,50.0f);
}