#include "Nave.h"

Nave::Nave(Ogre::String nombre, Ogre::SceneManager* sm, Ogre::Real x, Ogre::Real y){

	mSceneMgr = sm;

	nodoNave = mSceneMgr->createSceneNode(nombre);
	Ogre::Entity* entNave = mSceneMgr->createEntity("RZR-002.mesh");
	nodoNave->attachObject(entNave);	
	nodoNave->setPosition(x,-60,y); 
	nodoNave->setScale(50.0f,50.0f,50.0f);
}