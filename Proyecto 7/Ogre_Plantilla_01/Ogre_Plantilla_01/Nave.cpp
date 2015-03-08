#include "stdafx.h"

Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam){
	camera = cam;
	mSceneMgr = sm;
	lastMove = 0;
	speed = 20.0;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	nodoNave = mSceneMgr->createSceneNode("Nave");
	mSceneMgr->getRootSceneNode()->addChild(nodoNave);
	Ogre::Entity* entNave = mSceneMgr->createEntity("RZR-002.mesh");
	entNave->setMaterialName("RZR-002");
	nodoNave->attachObject(entNave);	
	nodoNave->setPosition(0.0,0.0,0.0); 
	nodoNave->setScale(20.0f,20.0f,20.0f);

	Ogre::Vector3 escala(2.0f,2.0f,2.0f);
	Ogre::Light* light = mSceneMgr->createLight("luz");
	light->setType(Ogre::Light::LT_POINT);
	light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	light->setDirection(Ogre::Vector3(0.0,-1.0,0.0));
	light->setDirection(Ogre::Vector3(0.0,0.0,0.0));
	nodoNave->attachObject(light);
	nodoNave->attachObject(camera);

}


void Nave::moverDerecha(){
	x-=speed;
	nodoNave->translate(-speed,0.0,0.0);
}


void Nave::moverIzquierda(){
	x=speed;
	nodoNave->translate(speed,0.0,0.0);
}


void Nave::moverAdelante(){
	z+=speed;
	nodoNave->translate(0.0,0.0,speed);
}


void Nave::moverAtras(){
	z-=speed;
	nodoNave->translate(0.0,0.0,-speed);
}

void Nave::moverArriba(){
	y+=speed;
	nodoNave->translate(0.0,speed,0.0);
}

void Nave::moverAbajo(){
	y-=speed;
	nodoNave->translate(0.0,-speed,0.0);
}


