#include "Torreta.h"

Torreta::Torreta(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y){

	mSceneMgr = sm;

	nodoTorreta = mSceneMgr->createSceneNode(nombre);
	Ogre::Entity* entTorreta = mSceneMgr->createEntity("usb_cilindro02.mesh");
	nodoTorreta->attachObject(entTorreta);	
	nodoTorreta->setPosition(x,-60,y); 
	nodoTorreta->setScale(50.0f,50.0f,50.0f);
}