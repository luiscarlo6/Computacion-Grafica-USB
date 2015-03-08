#include "stdafx.h"

Nave::Nave(Ogre::SceneManager* sm, Ogre::Camera* cam){
	camera = cam;
	mSceneMgr = sm;
	lastMove = 0;
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
	nodoNave->rotate(Ogre::Quaternion(Ogre::Radian(Ogre::Degree(180.0)),Ogre::Vector3(0.0,1.0,0.0)));

	Ogre::Vector3 escala(2.0f,2.0f,2.0f);
	Ogre::Light* light = mSceneMgr->createLight("luz");
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDiffuseColour(Ogre::ColourValue(1.0f,1.0f,1.0f));
	light->setDirection(Ogre::Vector3(0.0,0.0,-1.0));
	light->setDirection(Ogre::Vector3(0.0,0.0,0.0));
	nodoNave->attachObject(light);
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